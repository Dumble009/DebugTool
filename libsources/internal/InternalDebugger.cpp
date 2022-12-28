#include "InternalDebugger.h"
namespace debugTool
{
    namespace internal
    {
        // ostreamへの挿入オペレータ。ostreamが右辺に来るので、InternalDebuggerのメンバとしては定義できない。
        std::ostream &operator<<(std::ostream &os, const InternalDebugger &debugger)
        {
            debugger.ToStream(os);

            return os;
        }
    }
}