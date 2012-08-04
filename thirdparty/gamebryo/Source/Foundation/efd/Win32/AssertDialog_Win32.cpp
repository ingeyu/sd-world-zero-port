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

#include <efd/AssertDialog.h>
#include <efd/Helpers.h>
#include <windows.h>
#include <stdio.h>
#include <efd/utf8string.h>

using namespace efd;

//-------------------------------------------------------------------------------------------------
SInt8 efd::DisplayAssertDialog(
    const char* pFile,
    efd::SInt32 line,
    const char* pFunction,
    const char* pPred,
    const char* pMsg,
    const char* pStack,
    efd::Bool isAVerify)
{
    const char* pszTitle = isAVerify ? "Verify Failed" : "Assert Failed";

    utf8string buffer;
    buffer.reserve(1024);

    if ( pPred && pPred != pMsg )
    {
        buffer.append( "Predicate: " );
        buffer.append( pPred );
        buffer.append( "\n" );
    }
    buffer.append( "Message: " );
    buffer.append( pMsg );

    if ( pFile )
    {
        buffer.sprintf_append( "\nLocation: %s(%d)\n", pFile, line );

        if (pFunction)
        {
            buffer.sprintf_append( "\nFunction: %s\n", pFunction);
        }
    }

    if ( pStack )
    {
        buffer.append( "\nStackTrace:\n" );
        buffer.append( pStack );
        buffer.append( "\n" );
    }

    if ( isAVerify )
    {
        buffer.append( "\nYes to debug, No to ignore once." );
    }
    else
    {
        buffer.append( "\nYes to debug, No to ignore once, Cancel to ignore always." );
    }

    // Display the message box
    // Don't show the cancel button (ignore for the rest of the execution) option if it is a
    // verify message since that does not work in that case
    int msgboxID = MessageBox(
        NULL,
        buffer.c_str(),
        pszTitle,
        MB_ICONEXCLAMATION | (isAVerify ? MB_YESNO : MB_YESNOCANCEL));

    // Check the return value and let the helpers know how to handle the assert
    switch (msgboxID)
    {
    default:
    case IDYES:
        return AssertHelper::kDebugAbort;
    case IDNO:
        return AssertHelper::kIgnoreOnce;
    case IDCANCEL:
        return AssertHelper::kIgnore;
    }
}

//-------------------------------------------------------------------------------------------------
