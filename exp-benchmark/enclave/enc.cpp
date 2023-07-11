// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <stdio.h>
#include <cmath>
#include <iostream>

#include "helloworld_t.h"

double exp_kernel() {
    double res = 0;
    for (double i = -100000; i < 100000; i += .0001) {
        res += std::exp(i);
    }
    return res;
}

void enclave_helloworld()
{
    exp_kernel();
}
