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

#pragma once
#ifndef NICRITICALSECTION_H
#define NICRITICALSECTION_H

#include "NiSystemLibType.h"
#include <efd/CriticalSection.h>
#include <efd/AtomicOperations.h>

#define NI_MULTITHREADED

#define NiCriticalSection efd::CriticalSection
#define NiFastCriticalSection efd::FastCriticalSection

#define NiAtomicIncrement efd::AtomicIncrement
#define NiAtomicDecrement efd::AtomicDecrement

#endif // #ifndef NICRITICALSECTION_H
