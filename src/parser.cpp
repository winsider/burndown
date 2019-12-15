#include <burndown/parser.hpp>
#include <burndown/fileio.hpp>
#include <stdexcept>
#include <iostream>

namespace ltc
{
    namespace bd
    {
        std::vector<string_segment> parse_csp_buffer(const std::vector<char>& csp_txt)
        {
            std::vector<string_segment> cblks;

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
                                    end_cb = it - 2;
                                    if (end_cb - start_cb > 0)
                                        cblks.emplace_back(string_segment(&(*start_cb), end_cb - start_cb));
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

            return cblks;
        }

        void parse_csp_file(const std::string& filename)
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