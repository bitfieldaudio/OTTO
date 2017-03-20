#pragma once
#include <iomanip>
#include <string>
#include <plog/Util.h>

namespace plog
{
    class CsvFormatter
    {
    public:
        static util::nstring header()
        {
            return PLOG_NSTR("Date;Time;Severity;TID;This;Function;Message\n");
        }

        static util::nstring format(const Record& record)
        {
            tm t;
            util::localtime_s(&t, &record.getTime().time);

            util::nstringstream ss;
            ss << t.tm_year + 1900 << "/" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << "/" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << ";";
            ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << ":" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << ":" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << "." << std::setfill(PLOG_NSTR('0')) << std::setw(3) << record.getTime().millitm << ";";
            ss << severityToString(record.getSeverity()) << ";";
            ss << record.getTid() << ";";
            ss << record.getObject() << ";";
            ss << record.getFunc() << "@" << record.getLine() << ";";

            util::nstring message = record.getMessage();

            if (message.size() > kMaxMessageSize)
            {
                message.resize(kMaxMessageSize);
                message.append(PLOG_NSTR("..."));
            }

            util::nstringstream split(message);
            util::nstring token;

            while (!split.eof())
            {
                std::getline(split, token, PLOG_NSTR('"'));
                ss << "\"" << token << "\"";
            }

            ss << "\n";

            return ss.str();
        }

        static const size_t kMaxMessageSize = 32000;
    };
}
