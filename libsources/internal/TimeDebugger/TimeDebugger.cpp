﻿#include "TimeDebugger.h"

#define GET_NOW std::chrono::system_clock::now()

namespace debugTool
{
    namespace internal
    {
        void TimeDebugger::Start()
        {
            start = GET_NOW;
        }

        void TimeDebugger::Stop()
        {
            auto end = GET_NOW;
            elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        std::ostream &TimeDebugger::operator<<(std::ostream &os)
        {
            os << elapsedMs << "ms";

            return os;
        }
    }
}