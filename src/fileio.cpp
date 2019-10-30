#include <burndown/fileio.hpp>
#include <stdexcept>

namespace ltc
{
    namespace bd
    {
        Filestat::Filestat()
            : m_stat_buf{}
            , m_status(-1)
        {
            /* no op */
        }

        Filestat::Filestat(const std::string& filename)
        {
            init(filename);
            if (!valid())
                throw std::runtime_error("Failed to get file info for \"" + filename + "\". Status code: " + std::to_string(m_status));
        }

        Filestat::Filestat(const File& file)
        {
            init(file);
            if (!valid())
                throw std::runtime_error("Failed to get file info for file. Status code: " + std::to_string(m_status));
        }

        bool Filestat::init(const std::string& filename)
        {
            m_status = stat(filename.c_str(), &m_stat_buf);
            return valid();
        }

        bool Filestat::init(const File& file)
        {
            m_status = fstat(file.file_no(), &m_stat_buf);
            return valid();
        }

        bool Filestat::valid() const
        {
            return m_status == 0;
        }

        size_t Filestat::filesize() const
        { 
            return m_stat_buf.st_size;
        }

        File::File()
        {
        }

        File::File(const std::string& filename)
        {
            if (!open(filename))
                throw std::runtime_error("Failed to open file '" + filename + '\'');
        }

        bool File::open(const std::string& filename)
        {
            FILE* file;
            if (fopen_s(&file, filename.c_str(), "rb") != 0)
                return false;

            m_file = std::unique_ptr<FILE, file_deleter>(file);
            return true;
        }

        void File::close()
        {
            m_file.reset();
        }

        bool File::is_open() const
        {
            return !!m_file;
        }

        int File::file_no() const
        {
            return _fileno(m_file.get());
        }

        std::vector<char> File::read_text()
        {
            Filestat info(*this);
            auto size = info.filesize();
            std::vector<char> file_data;
            file_data.reserve(size);
            fseek(m_file.get(), 0, SEEK_SET);
            if (fread(file_data.data(), 1, size, m_file.get()) != size)
                throw std::runtime_error("Unexpected read error");

            return file_data;
        }
    }
}