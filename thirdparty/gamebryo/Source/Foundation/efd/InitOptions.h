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
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_INITOPTIONS_H
#define EE_INITOPTIONS_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/IAllocator.h>

namespace efd
{

class SpursInstance;

/**
    A platform-independent class designed to encapsulate any arguments to
    EE_INIT. In addition, this class contains the user created Allocator object
    and any additional system level services that may be overridden by the
    user.
*/
class EE_EFD_ENTRY InitOptions
{
public:

    /**
        Create an options instance that represents the system defaults. The
        following list is the default environment created by the init options.
    */
    InitOptions();

    /// Destroys the init options.
    ~InitOptions();
private:

#if defined (EE_PLATFORM_PS3)
public:
    bool GetInitSpuPrintServer() const;
    void SetInitSpuPrintServer(bool initSpuPrintServer);

    /// Returns the SpursInstance object that will be passed to the SpursManager.
    /// If NULL, an instance with suitable defaults will be created instead.
    SpursInstance* GetSpursInstance() const;

    /// Set a SpursInstance to be used to initialize the SpursManager.  The manager will take
    /// ownership of the SpursInstance (but may or may not own the underlying CellSpurs object).
    /// @return The previous instance will be returned.
    SpursInstance* SetSpursInstance(SpursInstance* pInstance);
private:
    SpursInstance* m_pSpursInstance;
    bool m_initSpuPrintServer;
#endif
};

} // end namespace efd

#endif
