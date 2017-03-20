#pragma once
#include <algorithm>
#include <plog/Util.h>
#include <plog/Converters/UTF8Converter.h>

namespace plog
{
    template<class Formatter, class Converter = UTF8Converter>
    class RollingFileAppender : public IAppender
    {
    public:
        RollingFileAppender(const util::nchar* fileName, size_t maxFileSize = 0, int maxFiles = 0)
            : m_fileSize()
            , m_maxFileSize((std::max)(static_cast<off_t>(maxFileSize), static_cast<off_t>(1000))) // set a lower limit for the maxFileSize
            , m_lastFileNumber((std::max)(maxFiles - 1, 0))
            , m_firstWrite(true)
        {
            util::splitFileName(fileName, m_fileNameNoExt, m_fileExt);
        }

#ifdef _WIN32
        RollingFileAppender(const char* fileName, size_t maxFileSize = 0, int maxFiles = 0)
            : m_fileSize()
            , m_maxFileSize((std::max)(static_cast<off_t>(maxFileSize), static_cast<off_t>(1000))) // set a lower limit for the maxFileSize
            , m_lastFileNumber((std::max)(maxFiles - 1, 0))
            , m_firstWrite(true)
        {
            util::splitFileName(util::toWide(fileName).c_str(), m_fileNameNoExt, m_fileExt);
        }
#endif

        virtual void write(const Record& record)
        {
            util::MutexLock lock(m_mutex);

            if (m_firstWrite)
            {
                openLogFile();
                m_firstWrite = false;
            }
            else if (m_lastFileNumber > 0 && m_fileSize > m_maxFileSize && -1 != m_fileSize)
            {
                rollLogFiles();
            }

            int bytesWritten = m_file.write(Converter::convert(Formatter::format(record)));

            if (bytesWritten > 0)
            {
                m_fileSize += bytesWritten;
            }
        }

    private:
        void rollLogFiles()
        {
            m_file.close();

            util::nstring lastFileName = buildFileName(m_lastFileNumber);
            util::File::unlink(lastFileName.c_str());

            for (int fileNumber = m_lastFileNumber - 1; fileNumber >= 0; --fileNumber)
            {
                util::nstring currentFileName = buildFileName(fileNumber);
                util::nstring nextFileName = buildFileName(fileNumber + 1);

                util::File::rename(currentFileName.c_str(), nextFileName.c_str());
            }

            openLogFile();
        }

        void openLogFile()
        {
            util::nstring fileName = buildFileName();
            m_fileSize = m_file.open(fileName.c_str());

            if (0 == m_fileSize)
            {
                int bytesWritten = m_file.write(Converter::header(Formatter::header()));

                if (bytesWritten > 0)
                {
                    m_fileSize += bytesWritten;
                }
            }
        }

        util::nstring buildFileName(int fileNumber = 0)
        {
            util::nstringstream ss;
            ss << m_fileNameNoExt;

            if (fileNumber > 0)
            {
                ss << '.' << fileNumber;
            }

            if (!m_fileExt.empty())
            {
                ss << '.' << m_fileExt;
            }

            return ss.str();
        }

    private:
        util::Mutex     m_mutex;
        util::File      m_file;
        off_t           m_fileSize;
        const off_t     m_maxFileSize;
        const int       m_lastFileNumber;
        util::nstring   m_fileExt;
        util::nstring   m_fileNameNoExt;
        bool            m_firstWrite;
    };
}
