#include <burndown/parser.hpp>
#include <burndown/fileio.hpp>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ltc
{
    namespace bd
    {
        void parse_csp(const std::string& filename)
        {
            File csp_file(filename);
            const auto csp_txt = csp_file.read_text();
            if (csp_txt.size() < 3)
                throw std::runtime_error("File is empty: " + filename);

            const auto end_it = csp_txt.end() - 3;
            auto it = csp_txt.begin();
            // Look for <++
            auto linenum{ 1 };
            while (it <= end_it)
            {
                if (*it == '\n')
                    ++linenum;

                if (*it == '<')
                {
                    if (*(++it) == '+' && *(++it) == '+')
                    {
                        // Begin codeblock
                        const auto start_cb = ++it;
                        const auto start_cb_line = linenum;
                        auto end_cb = csp_txt.end();
                        while (it != end_it)
                        {
                            if (*it == '\n')
                                ++linenum;
                            else if (*it == '+')
                            {
                                if (*(++it) == '+' && *(++it) == '>')
                                {
                                    // End codeblock
                                    end_cb = it - 3;
                                    //std::cout << "Found codeblock at line " << linenum << '\n';
                                    std::string code{ reinterpret_cast<const char*>(&(*start_cb)), static_cast<size_t>(end_cb - start_cb) };
                                    std::cout << code << '\n';
                                    break;
                                }
                                else continue;
                            }
                            ++it;
                        }
                        if (end_cb == csp_txt.end())
                            throw std::runtime_error("Codeblock on line " + std::to_string(start_cb_line) + " not terminated.");
                    }
                    else continue;
                }
                ++it;
            }
        }
    }
}