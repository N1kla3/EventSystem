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
        m_Delegates.insert(std::pair<DelegateHandle, Delegate<Args...>>(handle, delegate));
        return handle;
    }

    DelegateHandle AddFunction(std::function<void(Args...)> inFunction)
    {
        DelegateHandle handle;
        m_Delegates.insert(std::pair<DelegateHandle, Delegate<Args...>>(handle, Delegate<Args...>()));
        m_Delegates[handle].Add(inFunction);
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
        for (auto& delegate : m_Delegates)
        {
            delegate.second.Invoke(args...);
        }
    }

private:
    std::map<DelegateHandle, Delegate<Args...>> m_Delegates;
};
