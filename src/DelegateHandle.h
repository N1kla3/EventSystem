//
// Created by Nicola on 15.08.2021.
//
#pragma once

#include <cstdint>

template<typename ...Args>
class MultiCastDelegate;

class DelegateHandle
{
public:

    DelegateHandle(const DelegateHandle& handle) = default;
    DelegateHandle(DelegateHandle&& handle) = default;
    DelegateHandle& operator=(const DelegateHandle& rhs) = default;
    bool operator==(const DelegateHandle& rhs) const;
    bool operator!=(const DelegateHandle& rhs) const;
    bool operator<(const DelegateHandle& rhs) const;
    bool operator>(const DelegateHandle& rhs) const;
    bool operator<=(const DelegateHandle& rhs) const;
    bool operator>=(const DelegateHandle& rhs) const;

    [[nodiscard]] bool IsValid() const
    {
       return m_Valid;
    }

private:
    DelegateHandle();

    uint64_t m_Id = 0;

    bool m_Valid = false;

    inline static uint64_t STATIC_ID = 0;

    static uint64_t GenerateID();

    template<typename ...Args>
    friend class MultiCastDelegate;
};

