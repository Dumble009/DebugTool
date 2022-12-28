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

            virtual std::ostream &operator<<(std::ostream &os) = 0;
        };
    }
}