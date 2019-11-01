#include <burndown/template.hpp>
#include <burndown/fileio.hpp>
#include <burndown/parser.hpp>
#include <algorithm>
#include <iostream>

namespace ltc
{
    namespace bd
    {


        Template::Template(std::vector<char> file_data)
            : m_file_data(std::move(file_data))
        {
        }

        void Template::write_header()
        {

        }

        void Template::write_translation_unit()
        {
            int idx{ 0 };
            for (const auto& w : m_tunit_writers)
            {
                w(++idx);
            }
        }

        void Template::add_text(std::string_view txt)
        {
            m_tunit_writers.emplace_back([txt](int idx)
                {
                    std::cout << "write(\"" << txt << "\");\n";
                });
        }

        void Template::add_code(std::string_view code)
        {
            m_tunit_writers.emplace_back([code](int idx)
                {
                    std::cout << code << '\n';
                });
        }

        void Template::add_include(std::string_view include)
        {
            m_include_writers.emplace_back([include](int idx) 
                {
                    std::cout << include << '\n';
                });
        }
        
        Template::Ptr Template::from_file(const std::string& file_name)
        {
            File file(file_name);            
            auto file_data = file.read_text();
            return from_buffer(file_data);
        }

        Template::Ptr Template::from_buffer(std::vector<char> file_data)
        {
            const char * txt_start = file_data.data();
            const char* txt_end = txt_start + file_data.size();
            const auto sblocks = parse_csp_buffer(file_data);
            auto tmpl = std::unique_ptr<Template>(new Template(std::move(file_data)));

            const auto push_txt = [&tmpl](const char * begin, const char * end)
            {
                auto size = end - begin;
                if (size > 0)
                    tmpl->add_text(std::string_view(begin, size));
                return begin + size;
            };

            const auto push_code = [&tmpl](std::string_view code) 
            {
                if (code.find("#include") != std::string::npos)
                    tmpl->add_include(code);
                else
                    tmpl->add_code(code);
                return code.data() + code.size() + 3;
            };

            for (const std::string_view& block : sblocks)
            {
                txt_start = push_txt(txt_start, block.data() - 3);
                txt_start = push_code(block);
            }
            push_txt(txt_start, txt_end);

            return tmpl;
        }
    }
}
