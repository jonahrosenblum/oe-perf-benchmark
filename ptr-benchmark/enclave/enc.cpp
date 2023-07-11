// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <stdio.h>
#include <cmath>
#include <iostream>

#include "helloworld_t.h"

class Node {
public:
    int data;
    Node* next;
  
    // Default constructor
    Node()
    {
        data = 0;
        next = NULL;
    }
  
    // Parameterised Constructor
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
  
// Linked list class to
// implement a linked list.
class Linkedlist {
public:
    // Default constructor
    Linkedlist() { head = NULL; }
  
    // Function to insert a
    // node at the end of the
    // linked list.
    void insertNode(int);

    Node* head;
};
  
// Function to insert a new node.
void Linkedlist::insertNode(int data)
{
    // Create the new Node.
    Node* newNode = new Node(data);
  
    // Assign to head
    if (head == NULL) {
        head = newNode;
        return;
    }
  
    // Traverse till end of list
    Node* temp = head;
    while (temp->next != NULL) {
  
        // Update temp
        temp = temp->next;
    }
  
    // Insert at the last.
    temp->next = newNode;
}

double ptr_kernel() {
    Linkedlist list;
    for (int i = 0; i < 10000; i++) {
        list.insertNode((i ^ ((2 * i) + 1)) % 1000);
    }
    int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        Node* head = list.head;
        while(head) {
            sum = head->data ^ i;
            head = head->next;
        }
    }
    return sum;
}

void enclave_helloworld()
{
    ptr_kernel();
}
