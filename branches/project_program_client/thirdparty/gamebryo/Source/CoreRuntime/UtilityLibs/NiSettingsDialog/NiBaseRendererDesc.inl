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
inline NiBaseRendererDesc::NiBaseRendererDesc(
    NiRendererSettings* pkSettings) :
    m_pkSettings(pkSettings)
{
}
//---------------------------------------------------------------------------
inline void NiBaseRendererDesc::Activate()
{
    m_pkSettings->m_bD3D10Renderer = IsD3D10RendererDesc();
}
//---------------------------------------------------------------------------
inline bool NiBaseRendererDesc::IsActive()
{
    return m_pkSettings->m_bD3D10Renderer;
}
//---------------------------------------------------------------------------
inline bool NiBaseRendererDesc::GetDefaultVSync()
{
    return m_pkSettings->m_bVSync;
}
//---------------------------------------------------------------------------
inline void NiBaseRendererDesc::SelectVSync(bool bVSync)
{
    m_pkSettings->m_bVSync = bVSync;
}
//---------------------------------------------------------------------------
