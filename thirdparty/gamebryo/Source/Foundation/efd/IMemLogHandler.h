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
#ifndef EE_IMEMLOGHANDLER
#define EE_IMEMLOGHANDLER

#include <efd/UniversalTypes.h>
#include <efd/TimeType.h>
#include <efd/MemObject.h>
#include <efd/IBase.h>
#include <efd/MemTracker.h>

namespace efd
{
/**
Interface used to log all memory allocations and memory leaks.
*/
class EE_EFD_ENTRY IMemLogHandler : public efd::IBase
{
public:

    IMemLogHandler() {};

    /**
        Initializes any internal data structures that will be needed.
    
        @return True if the initialization was successful.
    */
    virtual efd::Bool OnInit() = 0;

    /**
        Shutdown all internal data structures.
    
        @return True if the shutdown was successful.
    */
    virtual efd::Bool OnShutdown() = 0;

    /// Returns true if the IMemLogHandler has been initialized.
    virtual efd::Bool IsInitialized() = 0;

    /// This method is responsible for logging an allocation event.
    virtual void LogAllocUnit(const AllocUnit *pkUnit,
        const char* pcPrefix = "",
        MemEventType eDeallocType = EE_MET_UNKNOWN,
        double fDeallocTime = -FLT_MAX,
        unsigned long ulDeallocThreadId = 0,
        size_t stSizeUnused = 0) const = 0;

    /// This method is responsible for logging a memory leak.
    virtual void LogAllocUnitLeak(const AllocUnit *pkUnit,
        const char* pcPrefix = "") const = 0;

    /**
        The method allows applications to set a mark between allocation events
        that can be used to help better track and organize all memory allocations.
    */
    virtual bool SetMarker(const char* pcMarkerType, 
        const char* pcClassifier, const char* pcString) = 0;

};

/**
A smart pointer (reference counting, self deleting pointer) for the
ILogDestination class
*/
typedef efd::SmartPointer<IMemLogHandler> IMemLogHandlerPtr;

}  // namespace efd

#endif // EE_IMEMLOGHANDLER
