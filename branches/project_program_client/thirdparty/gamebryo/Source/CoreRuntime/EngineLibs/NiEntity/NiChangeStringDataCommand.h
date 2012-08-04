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
#ifndef NICHANGESTRINGDATACOMMAND_H
#define NICHANGESTRINGDATACOMMAND_H

#include "NiChangePropertyCommand.h"

class NIENTITY_ENTRY NiChangeStringDataCommand :
    public NiChangePropertyCommand
{
public:
    NiChangeStringDataCommand(
        NiEntityPropertyInterface* pkEntityPropertyInterface,
        const NiFixedString& kPropertyName, const NiFixedString& kData,
        unsigned int uiPropertyIndex = 0);

private:
    NiFixedString m_kNewData;
    NiFixedString m_kOldData;

protected:
    // NiChangePropertyCommand overrides.
    virtual NiBool StoreOldData();
    virtual NiBool SetNewData();
    virtual NiBool SetOldData();
};

NiSmartPointer(NiChangeStringDataCommand);

#endif // NICHANGESTRINGDATACOMMAND_H
