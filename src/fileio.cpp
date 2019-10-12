#include <burndown/fileio.hpp>

namespace ltc
{
    namespace bd
    {
        Filestat::Filestat()
            : m_status(-1)
        {
            /* no op */
        }

        Filestat::Filestat(const std::string& filename)
        {
            init(filename);
            if (!valid())
                throw std::runtime_error("Failed to get file info for \"" + filename + "\". Status code: " + std::to_string(m_status));
        }

        bool Filestat::init(const std::string& filename)
        {
            m_status = stat(filename.c_str(), &m_stat_buf);
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
    }
}