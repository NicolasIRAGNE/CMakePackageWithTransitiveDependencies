#include <LibA.h>
#include "LibB.h"
#include <iostream>
#include <nlohmann/json.hpp>

void    B::f()
{
    std::cout << "B::f()" << std::endl;
    A::f();
}