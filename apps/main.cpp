#include <iostream>
#include <burndown/parser.hpp>

using namespace ltc::bd;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cout << "Burndown\n";
    std::cout << "- zero cost abstraction web\n";
    try
    {
        std::string file_name("./../../docs/example.csp"); 
        parse_csp(file_name);
    }
    catch (std::runtime_error& err)
    {
        std::cerr << "EXCEPTION: " << err.what() << '\n';
    }
}