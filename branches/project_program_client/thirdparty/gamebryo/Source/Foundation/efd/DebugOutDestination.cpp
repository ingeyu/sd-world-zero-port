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

#include "efdPCH.h"

#include <stdio.h>
#include <stdarg.h>
#include <efd/DebugOutDestination.h>
#include <efd/ILogger.h>


using namespace efd;
//-------------------------------------------------------------------------------------------------
EE_IMPLEMENT_CONCRETE_CLASS_INFO(DebugOutDestination);

//-------------------------------------------------------------------------------------------------
DebugOutDestination::DebugOutDestination( const efd::utf8string& name,
                                          efd::Bool decorateMessage /*= false*/,
                                          efd::Bool fileInfoWithMsg /*= false*/,
                                          efd::Bool fileInfoWithAssert /*= true*/ )
    : ILogDestination(name)
    , m_decorateMessage( decorateMessage )
    , m_fileWithMsg(fileInfoWithMsg)
    , m_fileWithAssert(fileInfoWithAssert)
{
}

//-------------------------------------------------------------------------------------------------
DebugOutDestination::~DebugOutDestination()
{
}

//-------------------------------------------------------------------------------------------------
efd::Bool DebugOutDestination::OnInit()
{
    return true;
}

//-------------------------------------------------------------------------------------------------
void DebugOutDestination::BeginLog(
    efd::Bool assert,
    const char* timeStampMachine,
    efd::TimeType timeStampGame,
    const char* module,
    const char* level,
    const char* file,
    efd::SInt32 line)
{
    // Only do anything in non-shipping modes since this style of printing is a violation of
    // the TCR conditions on most platforms.
#if !defined(EE_EFD_CONFIG_SHIPPING)
    char buffer[2048];

    if ( m_decorateMessage )
    {
        // |time|level|module|||msg|
        if ((!assert && !m_fileWithMsg) || (assert && !m_fileWithAssert))
        {
            efd::Snprintf(
                buffer, EE_ARRAYSIZEOF(buffer), EE_TRUNCATE,
                "%s|%s|%s|||",
                timeStampMachine,
                level,
                module);
        }
        else // |time|level|module|file|line|msg|
        {
            efd::Snprintf(
                buffer, EE_ARRAYSIZEOF(buffer), EE_TRUNCATE,
                "%s|%s|%s|%s|%d|",
                timeStampMachine,
                level,
                module,
                file,
                line);
        }
    }
    else
    {
        efd::Snprintf(
            buffer, EE_ARRAYSIZEOF(buffer), EE_TRUNCATE,
            "%s\t",
            timeStampMachine);
    }

    EE_DO_OUTPUT_DEBUG_STRING( buffer );

#else
    EE_UNUSED_ARG( assert );
    EE_UNUSED_ARG( timeStampMachine );
    EE_UNUSED_ARG( module );
    EE_UNUSED_ARG( level );
    EE_UNUSED_ARG( file );
    EE_UNUSED_ARG( line );
#endif
    EE_UNUSED_ARG(timeStampGame);
}

//-------------------------------------------------------------------------------------------------
void DebugOutDestination::ContinueLog(const char* pMsg)
{
#if !defined(EE_EFD_CONFIG_SHIPPING)
    EE_DO_OUTPUT_DEBUG_STRING( pMsg );
#else
    EE_UNUSED_ARG( pMsg );
#endif
}

//-------------------------------------------------------------------------------------------------
void DebugOutDestination::EndLog()
{
#if !defined(EE_EFD_CONFIG_SHIPPING)
    if ( m_decorateMessage )
    {
        EE_DO_OUTPUT_DEBUG_STRING( "|\n" );
    }
    else
    {
        EE_DO_OUTPUT_DEBUG_STRING( "\n" );
    }
#endif
}

//-------------------------------------------------------------------------------------------------
void DebugOutDestination::Flush()
{
}
