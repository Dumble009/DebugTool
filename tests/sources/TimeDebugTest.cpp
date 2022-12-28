#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "string.h"
#include "Debugger.h"

#define DEBUGGER_NAME1 "Debugger1"
#define DEBUGGER_NAME2 "Debugger2"

void CheckResult(const std::string &result, const std::string &debuggerName, int expectedResultTimeMs, int tolerantAbsErrorMs)
{
    // 出力のフォーマットは "DebuggerName : xxxms"msの桁数は値の大きさに応じて変わる
    // デバッガ名が期待通りになっているかの確認
    int cmpRes = strncmp(result.c_str(), debuggerName.c_str(), debuggerName.size());

    ASSERT_EQ(cmpRes, 0) << ":" << result << ":" << debuggerName << std::endl;

    int resultTime = 0; // resultの中から経過時刻の数値を抜き出す

    int idx = (int)debuggerName.size() + 3; // スペース、コロン、スペース文の3文字を詰める

    while (idx < (int)result.size())
    {
        char c = result[idx];
        if (c < '0' && c > '9')
        {
            break;
        }
        resultTime = resultTime * 10 + (int)(c - '0');

        idx++;
    }

    int diff = std::abs(expectedResultTimeMs - resultTime);

    ASSERT_TRUE(diff < tolerantAbsErrorMs);

    // 末尾の文字列が "ms"になっているかどうか

    std::string remain = result.substr(idx);

    cmpRes = strcmp(remain.c_str(), "ms");

    ASSERT_EQ(cmpRes, 0) << ":" << remain << std::endl;
}

TEST(TimerDebugTest, BasicAssertions)
{
    using namespace std::chrono_literals; // 秒数をsで表記できるようにする
    debugTool::Debugger::Start(DEBUGGER_NAME1,
                               debugTool::DebugType::TIME | debugTool::DebugType::TIME); // パイプを用いた複数表記が出来る事の確認

    std::this_thread::sleep_for(0.1s); // 0.1秒待機

    debugTool::Debugger::Start(DEBUGGER_NAME2, debugTool::DebugType::TIME);

    std::this_thread::sleep_for(0.2s); // 0.2秒待機

    auto output1 = debugTool::Debugger::Stop(DEBUGGER_NAME1);
    auto output2 = debugTool::Debugger::Stop(DEBUGGER_NAME2);

    std::cout << output1 << std::endl; // 期待される出力は "Debugger1 : 300ms"

    CheckResult(output1, DEBUGGER_NAME1, 300, 30);

    std::cout << output2 << std::endl; // 期待される出力は "Debugger2 : 200ms"

    CheckResult(output2, DEBUGGER_NAME2, 200, 20);
}