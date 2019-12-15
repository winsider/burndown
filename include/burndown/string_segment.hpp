#pragma once
#include <iostream>
#include <string.h>

namespace ltc
{
    namespace bd
    {
        class string_segment
        {
        public:
            string_segment()
            : m_ptr(nullptr), m_len(0)
            {}

            string_segment(const char * ptr, size_t len)
            : m_ptr(ptr), m_len(len)
            {}

            string_segment(const string_segment&) = default;
            string_segment(string_segment&&) = default;

            string_segment& operator=(const string_segment&) = default;
            string_segment& operator=(string_segment&&) = default;

            size_t find(const char * s) const
            {
                if (m_ptr)
                {
                    const auto p = strstr(m_ptr, s);
                    if (p)
                        return p - m_ptr;
                }
                return -1;
            }

            const char * data() const { return m_ptr; }
            size_t size() const { return m_len; }

            friend std::ostream& operator<< (std::ostream& stream, const string_segment& segment)
            {
                return stream.write(segment.m_ptr, segment.m_len);
            }

        private:
            const char * m_ptr;
            size_t m_len;
        };
    }
}