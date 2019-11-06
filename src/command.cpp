#include <burndown/command.hpp>
#include <boost/program_options.hpp>
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
                ("help", "produce help message")
                ("init", "initialize new project")
                ;
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            if (vm.count("help"))
            {
                std::cout << desc << '\n';
                return {};
            }

            return std::make_unique<Command>();
        }
    }
}