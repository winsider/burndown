#include <iostream>
#include <burndown/parser.hpp>

using namespace ltc::bd;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << "Burndown\n";
    std::cout << "- zero cost abstraction web\n";
    ParseCSP("test");    
}