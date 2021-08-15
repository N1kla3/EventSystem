//
// Created by Nicola on 15.08.2021.
//

#include "DelegateHandle.h"

bool DelegateHandle::operator==(const DelegateHandle& rhs) const { return m_Id == rhs.m_Id; }
bool DelegateHandle::operator!=(const DelegateHandle& rhs) const { return !(rhs == *this); }
bool DelegateHandle::operator<(const DelegateHandle& rhs) const { return m_Id < rhs.m_Id; }
bool DelegateHandle::operator>(const DelegateHandle& rhs) const { return rhs < *this; }
bool DelegateHandle::operator<=(const DelegateHandle& rhs) const { return !(rhs < *this); }
bool DelegateHandle::operator>=(const DelegateHandle& rhs) const { return !(*this < rhs); }

DelegateHandle::DelegateHandle()
{
    m_Id = GenerateID(this);
}

uint16_t DelegateHandle::GenerateID(DelegateHandle* inHandle)
{
    return reinterpret_cast<uint32_t>(inHandle);
}
