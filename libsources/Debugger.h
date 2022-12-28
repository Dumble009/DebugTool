#pragma once
#include <string>

namespace debugTool
{
    class Debugger
    {
    public:
        // debuggerNameに対応するデバッガを起動する。
        static void Start(const std::string &debuggerName);

        // debuggerNameに対応するデバッガを停止し、結果を出力する。
        static std::string Stop(const std::string &debuggerName);
    };
}