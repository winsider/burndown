#pragma once
#include <memory>

namespace ltc
{
    namespace bd
    {
        class Command
        {
        public:
            //! Factory method
            static std::unique_ptr<Command> parse(int argc, char* argv[]);
        };


    }
}