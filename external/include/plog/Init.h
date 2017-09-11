#pragma once
#include <cstring>
#include <plog/Logger.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/RollingFileAppender.h>

namespace plog
{
    namespace
    {
        bool isCsv(const util::nchar* fileName)
        {
            const util::nchar* dot = util::findExtensionDot(fileName);
#ifdef _WIN32
            return dot && 0 == std::wcscmp(dot, L".csv");
#else
            return dot && 0 == std::strcmp(dot, ".csv");
#endif
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Empty initializer / one appender

    template<int instance>
    inline Logger<instance>& init(Severity maxSeverity = none, IAppender* appender = NULL)
    {
        static Logger<instance> logger(maxSeverity);
        return appender ? logger.addAppender(appender) : logger;
    }

    inline Logger<PLOG_DEFAULT_INSTANCE>& init(Severity maxSeverity = none, IAppender* appender = NULL)
    {
        return init<PLOG_DEFAULT_INSTANCE>(maxSeverity, appender);
    }

    //////////////////////////////////////////////////////////////////////////
    // RollingFileAppender with any Formatter

    template<class Formatter, int instance>
    inline Logger<instance>& init(Severity maxSeverity, const util::nchar* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        static RollingFileAppender<Formatter> rollingFileAppender(fileName, maxFileSize, maxFiles);
        return init<instance>(maxSeverity, &rollingFileAppender);
    }

    template<class Formatter>
    inline Logger<PLOG_DEFAULT_INSTANCE>& init(Severity maxSeverity, const util::nchar* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<Formatter, PLOG_DEFAULT_INSTANCE>(maxSeverity, fileName, maxFileSize, maxFiles);
    }

    //////////////////////////////////////////////////////////////////////////
    // RollingFileAppender with TXT/CSV chosen by file extension

    template<int instance>
    inline Logger<instance>& init(Severity maxSeverity, const util::nchar* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return isCsv(fileName) ? init<CsvFormatter, instance>(maxSeverity, fileName, maxFileSize, maxFiles) : init<TxtFormatter, instance>(maxSeverity, fileName, maxFileSize, maxFiles);
    }

    inline Logger<PLOG_DEFAULT_INSTANCE>& init(Severity maxSeverity, const util::nchar* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<PLOG_DEFAULT_INSTANCE>(maxSeverity, fileName, maxFileSize, maxFiles);
    }

    //////////////////////////////////////////////////////////////////////////
    // CHAR variants for Windows

#ifdef _WIN32
    template<class Formatter, int instance>
    inline Logger<instance>& init(Severity maxSeverity, const char* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<Formatter, instance>(maxSeverity, util::toWide(fileName).c_str(), maxFileSize, maxFiles);
    }

    template<class Formatter>
    inline Logger<PLOG_DEFAULT_INSTANCE>& init(Severity maxSeverity, const char* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<Formatter, PLOG_DEFAULT_INSTANCE>(maxSeverity, fileName, maxFileSize, maxFiles);
    }

    template<int instance>
    inline Logger<instance>& init(Severity maxSeverity, const char* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<instance>(maxSeverity, util::toWide(fileName).c_str(), maxFileSize, maxFiles);
    }

    inline Logger<PLOG_DEFAULT_INSTANCE>& init(Severity maxSeverity, const char* fileName, size_t maxFileSize = 0, int maxFiles = 0)
    {
        return init<PLOG_DEFAULT_INSTANCE>(maxSeverity, fileName, maxFileSize, maxFiles);
    }
#endif
}
