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
//---------------------------------------------------------------------------
//  NiLines inline functions

//---------------------------------------------------------------------------
inline NiBool* NiLines::GetFlags()
{
    NiLinesData* pkData = NiSmartPointerCast(NiLinesData, m_spModelData);
    return pkData->GetFlags();
}
//---------------------------------------------------------------------------
inline const NiBool* NiLines::GetFlags() const
{
    NiLinesData* pkData = NiSmartPointerCast(NiLinesData, m_spModelData);
    return pkData->GetFlags();
}
//---------------------------------------------------------------------------
