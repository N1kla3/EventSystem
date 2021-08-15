//
// Created by Nicola on 15.08.2021.
//
#pragma once

#include "Delegate.h"
#include "DelegateHandle.h"
#include <map>

template<typename ...Args>
class MultiCastDelegate
{
public:
    template<typename Object>
    DelegateHandle AddMemberFunction(Object* obj, std::function<void(Object&, Args...)> inFunction)
    {
        Delegate<Args...> delegate;
        delegate.AddMemberFunction(obj, inFunction);
        DelegateHandle handle;
        m_Delegates.insert(std::move(delegate));
        return handle;
    }

    DelegateHandle AddFunction(std::function<void(Args...)> inFunction)
    {
        Delegate<Args...> delegate;
        delegate.Add(inFunction);
        DelegateHandle handle;
        m_Delegates[handle] = delegate;
        return handle;
    }

    void RemoveAll() { m_Delegates.clear(); }

    bool RemoveFunction(const DelegateHandle& inHandle)
    {
        auto it = m_Delegates.find(inHandle);
        if (it != m_Delegates.end())
        {
            m_Delegates.erase(it);
            return true;
        }
        return false;
    }

    void Broadcast(Args ...args) const
    {
        for (auto [none, delegate] : m_Delegates)
        {
            delegate.Invoke(args...);
        }
    }

private:
    std::unordered_map<DelegateHandle, Delegate<Args...>> m_Delegates;
};
