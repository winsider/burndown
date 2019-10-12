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
        void ParseCSP(const std::string& filepath);        
    }
}