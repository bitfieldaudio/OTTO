#pragma once

namespace plog
{
    template <class Formatter>
    class EventLogAppender : public IAppender
    {
    public:
        EventLogAppender(const wchar_t* sourceName) : m_eventSource(::RegisterEventSourceW(NULL, sourceName))
        {
        }

        ~EventLogAppender()
        {
            ::DeregisterEventSource(m_eventSource);
        }

        virtual void write(const Record& record)
        {
            std::wstring str = Formatter::format(record);
            const wchar_t* logMessagePtr[] = { str.c_str() };

            ::ReportEventW(m_eventSource, logSeverityToType(record.getSeverity()), static_cast<WORD>(record.getSeverity()), 0, NULL, 1, 0, logMessagePtr, NULL);
        }

    private:
        static WORD logSeverityToType(plog::Severity severity)
        {
            switch (severity)
            {
            case plog::fatal:
            case plog::error:
                return EVENTLOG_ERROR_TYPE;

            case plog::warning:
                return EVENTLOG_WARNING_TYPE;

            case plog::info:
            case plog::debug:
            case plog::verbose:
            default:
                return EVENTLOG_INFORMATION_TYPE;
            }
        }

    private:
        HANDLE m_eventSource;
    };

    class EventLogAppenderRegistry
    {
    public:
        static bool add(const wchar_t* sourceName, const wchar_t* logName = L"Application")
        {
            std::wstring logKeyName;
            std::wstring sourceKeyName;
            getKeyNames(sourceName, logName, sourceKeyName, logKeyName);

            HKEY sourceKey;
            if (NO_ERROR != ::RegCreateKeyExW(HKEY_LOCAL_MACHINE, sourceKeyName.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &sourceKey, NULL))
            {
                return false;
            }

            const DWORD kTypesSupported = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;
            ::RegSetValueExW(sourceKey, L"TypesSupported", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&kTypesSupported), sizeof(DWORD));

            const wchar_t kEventMessageFile[] = L"%windir%\\Microsoft.NET\\Framework\\v4.0.30319\\EventLogMessages.dll;%windir%\\Microsoft.NET\\Framework\\v2.0.50727\\EventLogMessages.dll";
            ::RegSetValueExW(sourceKey, L"EventMessageFile", 0, REG_EXPAND_SZ, reinterpret_cast<const BYTE*>(kEventMessageFile), static_cast<DWORD>(::wcslen(kEventMessageFile) * sizeof(wchar_t)));

            ::RegCloseKey(sourceKey);
            return true;
        }

        static bool exists(const wchar_t* sourceName, const wchar_t* logName = L"Application")
        {
            std::wstring logKeyName;
            std::wstring sourceKeyName;
            getKeyNames(sourceName, logName, sourceKeyName, logKeyName);

            HKEY sourceKey;
            if (NO_ERROR != ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, sourceKeyName.c_str(), 0, KEY_READ, &sourceKey))
            {
                return false;
            }

            ::RegCloseKey(sourceKey);
            return true;
        }

        static void remove(const wchar_t* sourceName, const wchar_t* logName = L"Application")
        {
            std::wstring logKeyName;
            std::wstring sourceKeyName;
            getKeyNames(sourceName, logName, sourceKeyName, logKeyName);

            ::RegDeleteKeyW(HKEY_LOCAL_MACHINE, sourceKeyName.c_str());
            ::RegDeleteKeyW(HKEY_LOCAL_MACHINE, logKeyName.c_str());
        }

    private:
        static void getKeyNames(const wchar_t* sourceName, const wchar_t* logName, std::wstring& sourceKeyName, std::wstring& logKeyName)
        {
            const std::wstring kPrefix = L"SYSTEM\\CurrentControlSet\\Services\\EventLog\\";
            logKeyName = kPrefix + logName;
            sourceKeyName = logKeyName + L"\\" + sourceName;
        }
    };
}
