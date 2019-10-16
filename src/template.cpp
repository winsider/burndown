#include <burndown/template.hpp>
#include <burndown/fileio.hpp>

namespace ltc
{
    namespace bd
    {
        class Template_block
        {
        public:
            Template_block() = default;
            ~Template_block() = default;

            virtual void write_include()
            {
                // NO-OP
            }

            virtual void write_code()
            {
                // NO-OP
            }

            virtual void write_text_ref()
            {
                // NO-OP
            }

            virtual void write_text_def()
            {
                // NO-OP
            }

        private:
            std::string_view m_text;
        };

        class Include_block : public Template_block
        {
        public:
            void write_include() override
            {
                // TODO: Write include
            }
        };

        class Code_block : public Template_block
        {
        public:
            void write_code() override
            {
                // TODO: Write code
            }
        };

        class Text_block : public Template_block
        {
        public:
            void write_text_ref() override
            {
                // TODO: Write header
            }

            void write_text_def() override
            {
                // TODO: Write definition
            }
        };

        Template::Template(std::vector<char> file_data)
            : m_file_data(std::move(file_data))
        {
        }

        Template::~Template()
        {

        }

        void Template::write_header()
        {

        }

        void Template::write_translation_unit()
        {

        }
        /* 
        Template::Ptr Template::from_file(const std::string& file_name)
        {
            Filestat s(file_name);            
            std::vector<char> file_data;
            file_data.resize(s.filesize());

        }

        Template::Ptr Template::from_buffer(std::vector<char> file_data)
        {

        }
        */
    }
}
