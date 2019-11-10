#include <burndown/command.hpp>
#include <boost/program_options.hpp>
#include <sass/context.h>
#include <iostream>

namespace ltc
{
    namespace bd
    {
        namespace po = boost::program_options;

        std::unique_ptr<Command> Command::parse(int argc, char* argv[])
        {
            po::options_description desc("Allowed options");
            desc.add_options()
                ("help,h", "produce help message")
                ("init", "initialize new project")
                ("version,v", "print version string")
                ;
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            
            if (vm.count("help"))
            {
                std::cout << desc << '\n';
                return {};
            }

            if (vm.count("version"))
            {
                std::cout << "Burndown version 0.0.1\n";
                std::cout << "Libsass version " << libsass_version() << '\n';
                return {};
            }
            
            
            return std::make_unique<Command>();
        }
    }
}