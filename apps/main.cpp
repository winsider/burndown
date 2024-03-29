#include <iostream>
#include <burndown/command.hpp>
#include <burndown/template.hpp>

using namespace ltc::bd;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    try
    {
        auto cmd = Command::parse(argc, argv);
        if (cmd)
        {
            std::string file_name("./../../docs/example.csp");
            auto tmpl = Template::from_file(file_name);
            tmpl->write_translation_unit();
        }
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << "EXCEPTION: " << err.what() << '\n';
    }
}