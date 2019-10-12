#pragma once
#include <sys/stat.h> 
#include <string>
#include <vector>
#include <memory>

namespace ltc
{
    namespace bd
    {
        /**
         * Utility class for querying file properties
         */ 
        class Filestat
        {
        public:
            /// Default constructor
            Filestat();

            /**
             * Initialize with file data
             * \param filename Path and name for file 
             */
            Filestat(const std::string& filename);

            /**
             * Initialize with file data
             * \param filename Path and name for file
             * \return true if file data was retrieved
             */
            bool init(const std::string& filename);

            /**
             * Check if Filestat has valid file data
             * \return true if valid
             */
            bool valid() const;

            /**
             * Size of the file in bytes
             * \return file size in bytes
             */
            size_t filesize() const;

        private:
            struct stat m_stat_buf;
            int m_status;
        };

        /**
         * Wrapper for std c file io
         */
        class File
        {
        public:
            File();
            File(const std::string& filename);            
            bool open(const std::string& filename);
            void close();
            bool is_open() const;
            std::vector<char> read_text();

        private:
            struct file_deleter { void operator()(FILE* f) { std::fclose(f); }};
            std::unique_ptr<FILE*, file_deleter> m_file;
        };
    }
}
