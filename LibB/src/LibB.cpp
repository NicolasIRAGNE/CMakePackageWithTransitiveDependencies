#include <LibA.h>
#include "LibB.h"
#include <iostream>

void    B::f()
{
    std::cout << "B::f()" << std::endl;
    A::f();
}