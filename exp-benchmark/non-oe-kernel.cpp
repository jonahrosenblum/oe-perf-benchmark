
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <cmath>

double exp_kernel() {
    double res = 0;
    for (double i = -100000; i < 100000; i += .0001) {
        res += std::exp(i);
    }
    return res;
}

int main(int argc, const char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    exp_kernel();
    auto stop = std::chrono::high_resolution_clock::now();
       
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Duration of non oe exp kernel " << duration.count() << std::endl;
    
    return 0;
}
