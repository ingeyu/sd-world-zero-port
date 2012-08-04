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
#ifndef NICOMMONMATERIALLIBTYPE_H
#define NICOMMONMATERIALLIBTYPE_H

#ifdef NICOMMONMATERIAL_EXPORT
    // DLL library project uses this
    #define NICOMMONMATERIAL_ENTRY __declspec(dllexport)
#else
#ifdef NICOMMONMATERIAL_IMPORT
    // client of DLL uses this
    #define NICOMMONMATERIAL_ENTRY __declspec(dllimport)
#else
    // static library project uses this
    #define NICOMMONMATERIAL_ENTRY
#endif
#endif

// Disable warning C4251.  Template classes cannot be exported for the obvious
// reason that the code is not generated until an instance of the class is
// declared.  With this warning enabled, you get thousands of complaints about
// class data members that are of template type.  For example, a member such
// as 'NiTPrimitiveArray<NiAVObject*> m_array' generates the warning.
//
// When maintaining the DLL code itself, you might want to enable the warning
// to check for cases where you might have failed to put the
// NICOMMONMATERIAL_ENTRY after the class keyword.  In particular, nested 
// classes must have NICOMMONMATERIAL_ENTRY.  Also, friend functions must be 
// tagged with NICOMMONMATERIAL_ENTRY.

#ifdef WIN32
    #pragma warning( disable : 4251 )
#endif
                                      
#endif  //NICOMMONMATERIALLIBTYPE_H
