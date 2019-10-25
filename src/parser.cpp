#include <burndown/parser.hpp>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ltc
{
    namespace bd
    {
        long FileSize(const std::string& filename)
        {
            struct stat stat_buf;
            auto rc = stat(filename.c_str(), &stat_buf);
            return rc == 0 ? stat_buf.st_size : -1;
        }

        std::vector<uint8_t> ReadFile(const std::string& filename)
        {
            const auto filesize = FileSize(filename);
            auto handle = fopen(filename.c_str(), "r+b");
            if (handle == nullptr)
                throw std::runtime_error("Failed to open file: " + filename);
            std::vector<uint8_t> filebytes;
            filebytes.resize(filesize);
            auto readbytes = static_cast<long>(fread(filebytes.data(), 1, filesize, handle));
            fclose(handle);
            if (readbytes != filesize)
                throw std::runtime_error("Error reading file: " + filename);
            return filebytes;
        }

        void CompileCsp(const std::string& filename)
        {
            const auto filebytes = ReadFile(filename);
            if (filebytes.size() < 3)
                throw std::runtime_error("File is empty: " + filename);

            const auto end_it = filebytes.end() - 3;
            auto it = filebytes.begin();
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
                        auto end_cb = filebytes.end();
                        while (it != end_it)
                        {
                            if (*it == '\n')
                                ++linenum;

                            if (*it == '+')
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
                        if (end_cb == filebytes.end())
                            throw std::runtime_error("Codeblock on line " + std::to_string(start_cb_line) + " not terminated.");
                    }
                    else continue;
                }
                ++it;
            }
        }
    }
}