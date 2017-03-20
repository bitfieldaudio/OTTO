#pragma once
#include <iomanip>
#include <plog/Util.h>

namespace plog
{
    class FuncMessageFormatter
    {
    public:
        static util::nstring header()
        {
            return util::nstring();
        }

        static util::nstring format(const Record& record)
        {
            util::nstringstream ss;
            ss << record.getFunc() << "@" << record.getLine() << ": ";
            ss << record.getMessage() << "\n";

            return ss.str();
        }
    };
}
