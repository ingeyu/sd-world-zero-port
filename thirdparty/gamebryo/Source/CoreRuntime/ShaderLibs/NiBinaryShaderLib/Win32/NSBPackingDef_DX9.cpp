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
// Precompiled Header
#include "NiBinaryShaderLibPCH.h"

//---------------------------------------------------------------------------
#include "NSBPackingDef.h"
#include "NSBUtility.h"
#include <NiD3DUtility.h>
#include <NiDX9Renderer.h>

//---------------------------------------------------------------------------
NiShaderDeclaration* NSBPackingDef::GetShaderDeclaration(
    NiShader::Platform)
{
    // Determine the stream count, and the max entry count
    unsigned int uiStreamCount = 0;
    unsigned int uiMaxStreamEntryCount = 0;

    GetStreamInfo(uiStreamCount, uiMaxStreamEntryCount);

    NiShaderDeclaration* pkShaderDecl =
        NiShaderDeclaration::Create(uiMaxStreamEntryCount, uiStreamCount);

    if (pkShaderDecl)
    {
        unsigned int uiEntry = 0;
        unsigned int uiStream = 0xFFFFFFFF;

        NSBPDEntry* pkEntry = GetFirstEntry();
        while (pkEntry)
        {
            // Add the entry to the shader declaration
            NiShaderDeclaration::ShaderParameterType eType;

            eType = ConvertPackingDefType(pkEntry->GetType());

            NIASSERT((unsigned int)eType != 0xffffffff);

            if (uiStream != pkEntry->GetStream())
            {
                uiStream = pkEntry->GetStream();
                uiEntry = 0;
            }

            if (pkEntry->GetUsage() == NiShaderDeclaration::SPUSAGE_COUNT)
            {
                pkShaderDecl->SetEntry(uiEntry, 
                    (NiShaderDeclaration::ShaderParameter)
                    pkEntry->GetInput(), eType, pkEntry->GetStream());
            }
            else
            {
                pkShaderDecl->SetEntry(pkEntry->GetStream(), uiEntry, 
                    (NiShaderDeclaration::ShaderParameter)
                    pkEntry->GetInput(), eType, 
                    NiShaderDeclaration::UsageToString(pkEntry->GetUsage()), 
                    pkEntry->GetUsageIndex(), pkEntry->GetTesselator());
            }

            uiEntry++;
            pkEntry = GetNextEntry();
        }
    }

    return pkShaderDecl;
}
//---------------------------------------------------------------------------
NiShaderDeclaration::ShaderParameterType 
    NSBPackingDef::ConvertPackingDefType(NiD3DPackingDefType eType)
{
#ifdef NIDEBUG
    NiRenderer* pkRenderer = NiRenderer::GetRenderer();
#endif
    NIASSERT(pkRenderer);
    NIASSERT(NiIsKindOf(NiDX9Renderer, pkRenderer));
    switch (eType)
    {
    case NID3DPDT_FLOAT1:
        return NiShaderDeclaration::SPTYPE_FLOAT1;
    case NID3DPDT_FLOAT2:
        return NiShaderDeclaration::SPTYPE_FLOAT2;
    case NID3DPDT_FLOAT3:
        return NiShaderDeclaration::SPTYPE_FLOAT3;
    case NID3DPDT_FLOAT4:
        return NiShaderDeclaration::SPTYPE_FLOAT4;
    case NID3DPDT_UBYTECOLOR:
        return NiShaderDeclaration::SPTYPE_UBYTECOLOR;
    case NID3DPDT_UBYTE4:
        return NiShaderDeclaration::SPTYPE_UBYTE4;
    case NID3DPDT_SHORT2:
        return NiShaderDeclaration::SPTYPE_SHORT2;
    case NID3DPDT_SHORT4:
        return NiShaderDeclaration::SPTYPE_SHORT4;
    case NID3DPDT_NORMUBYTE4:
        return NiShaderDeclaration::SPTYPE_NORMUBYTE4;
    case NID3DPDT_NORMSHORT2:
        return NiShaderDeclaration::SPTYPE_NORMSHORT2;
    case NID3DPDT_NORMSHORT4:
        return NiShaderDeclaration::SPTYPE_NORMSHORT4;
    case NID3DPDT_NORMUSHORT2:
        return NiShaderDeclaration::SPTYPE_NORMUSHORT2;
    case NID3DPDT_NORMUSHORT4:
        return NiShaderDeclaration::SPTYPE_NORMUSHORT4;
    case NID3DPDT_UDEC3:
        return NiShaderDeclaration::SPTYPE_UDEC3;
    case NID3DPDT_NORMDEC3:
        return NiShaderDeclaration::SPTYPE_NORMDEC3;
    case NID3DPDT_FLOAT16_2:
        return NiShaderDeclaration::SPTYPE_FLOAT16_2;
    case NID3DPDT_FLOAT16_4:
        return NiShaderDeclaration::SPTYPE_FLOAT16_4;
    default:
        return (NiShaderDeclaration::ShaderParameterType)0xffffffff;
    }
}
//---------------------------------------------------------------------------
