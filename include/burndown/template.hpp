#pragma once

#include <vector>
#include <string>
#include <memory>

namespace ltc
{
    namespace bd
    {

        class Template
        {
        public:
            using Ptr = std::unique_ptr<Template>;
            ~Template();

            void write_header();
            void write_translation_unit();

            static Ptr from_file(const std::string& file_name);
            static Ptr from_buffer(std::vector<char> file_data);

        private:
            Template(std::vector<char> file_data);
            std::vector<char> m_file_data; 
        };


    }
}