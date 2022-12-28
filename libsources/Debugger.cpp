#include "Debugger.h"

namespace debugTool
{
    void Debugger::Start(const std::string &debuggerName, int type)
    {
    }

    std::string Debugger::Stop(const std::string &debuggerName)
    {
        return "Debugger Stopped : " + debuggerName;
    }
}