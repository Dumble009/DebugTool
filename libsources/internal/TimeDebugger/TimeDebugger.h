#pragma once
#include <chrono>
#include "../InternalDebugger.h"

namespace debugTool
{
    namespace internal
    {
        class TimeDebugger : public InternalDebugger
        {
        private:
            // 計測開始時点を保持するための変数
            std::chrono::system_clock::time_point start;

            // 計測開始時点から終了時点までの経過時間(ミリ秒)を保持するための変数
            int elapsedMs;

        public:
            void Start() override;
            void Stop() override;
            void ToStream(std::ostream &os) const override;
        };
    }
}