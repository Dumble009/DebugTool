#include "Debugger.h"
#include "internal/InternalDebugger.h"
#include "internal/TimeDebugger/TimeDebugger.h"
#include <exception>
#include <map>
#include <vector>
#include <sstream>

namespace debugTool
{
    // debugTool名前空間の中で名称が衝突しないようにネームスペースで隠しておく
    namespace debuggerImplement
    {
        using DebuggerList = std::vector<internal::InternalDebugger *>;
        using DebuggerTable = std::map<std::string, DebuggerList>;
        DebuggerTable debuggers = DebuggerTable();
    }

    using namespace debuggerImplement;

    bool IsDebuggerTableContainsKey(const DebuggerTable &table, const std::string &key)
    {
        return table.find(key) != table.end(); // tableがkeyを含んでいる場合はend以外のイテレータが返される。
    }

    // idxに対応する型のInternalDebuggerの派生クラスのオブジェクトをヒープに作成して、そのポインタを返す
    internal::InternalDebugger *GetInternalDebuggerPtr(int idx)
    {
        if (idx == 0)
        {
            return new internal::TimeDebugger;
        }

        throw std::invalid_argument("invalid type was passes.");
    }

    void Debugger::Start(const std::string &debuggerName, int type)
    {
        // debuggerNameがすでに使われている場合は例外を投げる
        if (IsDebuggerTableContainsKey(debuggers, debuggerName))
        {
            throw std::invalid_argument("debuggerName is already used.");
        }

        debuggers[debuggerName] = DebuggerList();

        for (int i = 0; i < 32; i++)
        {
            // typeのi番目のビットが1になっていたら
            if ((type & (1 << i)) != 0)
            {
                debuggers[debuggerName].push_back(GetInternalDebuggerPtr(i));
            }
        }

        // 出来るだけ公平を期すために、一度全てのデバッガを作成してから後で一斉に起動する。

        for (auto debugger : debuggers[debuggerName])
        {
            debugger->Start();
        }
    }

    std::string Debugger::Stop(const std::string &debuggerName)
    {
        // 公平を期すために、全てのデバッガを停止してから後でまとめて出力をもらう。
        for (auto debugger : debuggers[debuggerName])
        {
            debugger->Stop();
        }

        std::ostringstream ss;
        ss << debuggerName;

        constexpr char partition[] = " : ";
        for (auto debugger : debuggers[debuggerName])
        {
            ss << partition << (*debugger);
        }

        // 作成したデバッガ群を全て削除し、同じdebuggerNameを再度使えるようにする
        int debuggerCount = (int)debuggers[debuggerName].size();
        // 各デバッガオブジェクトはヒープに作られているのでdeleteする必要がある
        for (int i = 0; i < debuggerCount; i++)
        {
            delete debuggers[debuggerName][i];
        }
        // 全てのデバッガオブジェクトを削除したら、debuggersからdebuggerNameのエントリを削除して再利用できるようにする。
        debuggers.erase(debuggerName);

        return ss.str();
    }
}
