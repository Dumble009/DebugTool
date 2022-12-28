#pragma once
#include <iostream>

namespace debugTool
{
    namespace internal
    {
        class InternalDebugger
        {
        public:
            virtual void Start() = 0;
            virtual void Stop() = 0;

            // ostreamへ出力する内容を派生クラスごとに変えるために必要
            virtual void ToStream(std::ostream &os) const = 0;
            friend std::ostream &operator<<(std::ostream &os, const InternalDebugger &debugger);
        };
    }
}