#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "Debugger.h"

TEST(TimerDebugTest, BasicAssertions)
{
    using namespace std::chrono_literals; // 秒数をsで表記できるようにする
    std::this_thread::sleep_for(1s);
}