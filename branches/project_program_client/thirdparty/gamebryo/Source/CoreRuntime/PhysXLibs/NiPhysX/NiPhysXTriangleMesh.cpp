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


#include "NiPhysXPCH.h"

#include <efd/utf8string.h>
#include <efdPhysX/PhysXSDKManager.h>

#include "NiPhysX.h"

using namespace efdPhysX;

//---------------------------------------------------------------------------
NxTriangleMesh* NiPhysXTriangleMesh::Create(const NiFixedString& kFilename)
{
    NiFixedString kFinalName = kFilename;
    NiStandardizeFilePath(kFinalName);
    NiPhysXMeshDesc::ConvertFilenameToPlatformSpecific(kFinalName, kFinalName);

    PhysXSDKManager* pkManager = PhysXSDKManager::GetManager();

    efd::utf8string kMeshName = (const efd::Char*)kFinalName;
    NxTriangleMesh* pkResult = pkManager->GetTriangleMesh(kMeshName);
    
    if (pkResult)
        return pkResult;

    NiPhysXFileStream* pkStream =
        NiNew NiPhysXFileStream(kFinalName, NiFile::READ_ONLY);
    if (!pkStream->Ready())
    {
        size_t stSize = strlen((const char *)kFinalName) + 256;
        char* pcMsg = (char*)NiMalloc(sizeof(char) * stSize);
        NiSprintf(pcMsg, stSize,
            "NiPhysXTriangleMesh::CreateMesh cannot open file %s\n",
            (const efd::Char*)kFinalName);
        NiOutputDebugString(pcMsg);
        NiFree(pcMsg);
        NiDelete pkStream;
        return 0;
    }

    pkManager->WaitSDKLock();
    pkResult = pkManager->m_pPhysXSDK->createTriangleMesh(*pkStream);
    pkManager->ReleaseSDKLock();

    if (!pkResult)
    {
        size_t stSize = strlen((const char *)kFinalName) + 256;
        char* pcMsg = (char*)NiMalloc(sizeof(char) * stSize);
        NiSprintf(pcMsg, stSize,
            "NiPhysXTriangleMesh::CreateMesh mesh creation failed for file %s\n",
            (const efd::Char*)kFinalName);
        NiOutputDebugString(pcMsg);
        NiFree(pcMsg);
        NiDelete pkStream;
        return 0;
    }

    pkManager->SetTriangleMesh(kMeshName, pkResult);

    NiDelete pkStream;

    return pkResult;
}
//---------------------------------------------------------------------------
NxTriangleMesh* NiPhysXTriangleMesh::Create(NiPhysXMemStream& kStream,
    const NiFixedString& kName)
{
    PhysXSDKManager* pkManager = PhysXSDKManager::GetManager();

    efd::utf8string kMeshName = (const efd::Char*)kName;
    NxTriangleMesh* pkResult = pkManager->GetTriangleMesh(kMeshName);
    
    if (pkResult)
        return pkResult;

    pkManager->WaitSDKLock();
    pkResult = pkManager->m_pPhysXSDK->createTriangleMesh(kStream);
    pkManager->ReleaseSDKLock();

    if (!pkResult)
    {
        size_t stSize = strlen((const char *)kName) + 256;
        char* pcMsg = (char*)NiMalloc(sizeof(char) * stSize);
        NiSprintf(pcMsg, stSize,
            "NiPhysXTriangleMesh::CreateMesh mesh creation failed for mesh %s\n",
            (const efd::Char*)kName);
        NiOutputDebugString(pcMsg);
        NiFree(pcMsg);
        return 0;
    }

    pkManager->SetTriangleMesh(kMeshName, pkResult);

    return pkResult;
}
//---------------------------------------------------------------------------
