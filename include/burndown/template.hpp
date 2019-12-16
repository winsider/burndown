#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <burndown/string_segment.hpp>

namespace ltc
{
    namespace bd
    {

        class Template
        {
        public:
            using Ptr = std::unique_ptr<Template>;
            ~Template() = default;

            void write_header();
            void write_translation_unit();

            static Ptr from_file(const std::string& file_name);
            static Ptr from_buffer(std::vector<char> file_data);

        private:
            Template(std::vector<char> file_data);

            void add_text(string_segment txt);
            void add_code(string_segment code);
            void add_include(string_segment inc);

            using Writer = std::function<void(int idx)>;            
            std::vector<char> m_file_data; 
            std::vector<string_segment> m_blocks;
            std::vector<Writer> m_include_writers;
            std::vector<Writer> m_header_decl_writers;
            std::vector<Writer> m_tunit_decl_writers;
            std::vector<Writer> m_tunit_writers;
        };


    }
}