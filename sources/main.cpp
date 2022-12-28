#include <iostream>
#include "Debugger.h"

int main(void)
{
    std::cout << "test code start!" << std::endl;
    debugTool::Debugger::Start("Debugger1");
    std::cout << debugTool::Debugger::Stop("Debugger1") << std::endl;

    std::cout << "test code finish!" << std::endl;

    return 0;
}