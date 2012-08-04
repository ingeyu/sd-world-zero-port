// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

// Precompiled Header
#include "NiEntityPCH.h"

#include "NiResetPoint2DataCommand.h"

//---------------------------------------------------------------------------
NiResetPoint2DataCommand::NiResetPoint2DataCommand(
    NiEntityPropertyInterface* pkEntityPropertyInterface,
    const NiFixedString& kPropertyName) : NiChangePropertyCommand(
    pkEntityPropertyInterface, kPropertyName, 0), m_pkOldData(NULL)
{
    NiFixedString kPrimitiveType;
    NIVERIFY(m_spEntityPropertyInterface->GetPrimitiveType(
        m_kPropertyName, kPrimitiveType));
    NIASSERT(kPrimitiveType == NiEntityPropertyInterface::PT_POINT2);
}
//---------------------------------------------------------------------------
NiResetPoint2DataCommand::~NiResetPoint2DataCommand()
{
    NiDelete[] m_pkOldData;
}
//---------------------------------------------------------------------------
// NiChangePropertyCommand overrides.
//---------------------------------------------------------------------------
NiBool NiResetPoint2DataCommand::StoreOldData()
{
    NiBool bSuccess = m_spEntityPropertyInterface->GetElementCount(
        m_kPropertyName, m_uiOldDataCount);
    if (!bSuccess)
    {
        return false;
    }

    if (!m_pkOldData)
    {
        m_pkOldData = NiNew NiPoint2[m_uiOldDataCount];
    }

    for (unsigned int ui = 0; ui < m_uiOldDataCount; ui++)
    {
        if (!m_spEntityPropertyInterface->GetPropertyData(m_kPropertyName,
            m_pkOldData[ui], ui))
        {
            return false;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiResetPoint2DataCommand::SetNewData()
{
    return m_spEntityPropertyInterface->ResetProperty(m_kPropertyName);
}
//---------------------------------------------------------------------------
NiBool NiResetPoint2DataCommand::SetOldData()
{
    for (unsigned int ui = 0; ui < m_uiOldDataCount; ui++)
    {
        if (!m_spEntityPropertyInterface->SetPropertyData(m_kPropertyName,
            m_pkOldData[ui], ui))
        {
            return false;
        }
    }
    
    return true;
}
//---------------------------------------------------------------------------
