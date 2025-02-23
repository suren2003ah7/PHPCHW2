#include "factorial.h"

double factorial(double n)
{
    if (n == 0.0)
        return 1.0;
    return factorial(n - 1.0) * n;
}