#pragma once

#include <vector>
#include <string>

namespace ltc
{
    namespace bd
    {
        class Template_block
        {
        public:
            
        private:
            std::string::iterator str;
            std::string::size_t len;
        };

        class Include_block : public Template_block
        {

        };
        
        class Code_block : public Template_block
        {

        };

        class Text_block : public Template_block
        {

        };

        class Template
        {
        public:

        private:
            std::vector<char> m_file_data; 
            std::vector<Template_block> m_blocks;
        };
    }
}