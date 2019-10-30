#pragma once
#include <string>

namespace ltc
{
    namespace bd
    {
        /**
         * Parse csp file.
         * \param filepath Full path and name to csp file
         */
        void parse_csp(const std::string& filepath);        
    }
}