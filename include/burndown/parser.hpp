#pragma once
#include <string>
#include <vector>
#include <burndown/string_segment.hpp>

namespace ltc
{
    namespace bd
    {
        /**
         * Parse buffer with csp template data
         *
         * \param csp_txt Buffer with CSP data
         */
        std::vector<string_segment> parse_csp_buffer(const std::vector<char>& csp_txt);

        /**
         * Parse csp file.
         * \param filepath Full path and name to csp file
         */
        void parse_csp_file(const std::string& filepath);        
    }
}