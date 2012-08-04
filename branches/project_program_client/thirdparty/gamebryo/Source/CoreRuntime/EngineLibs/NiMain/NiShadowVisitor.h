// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NISHADOWVISITOR_H
#define NISHADOWVISITOR_H

#include "NiObject.h"
#include "NiAVObject.h"

class NiShadowGenerator;
class NiNode;

class NIMAIN_ENTRY NiShadowVisitor : public NiMemObject
{
    NiDeclareRTTI;
public:

    // Empty destructor
    virtual ~NiShadowVisitor();

    virtual void PopulateCasterList(NiShadowGenerator* pkGenerator, 
        NiAVObjectRawList& kCasterList);

    virtual void PopulateReceiverList(NiShadowGenerator* pkGenerator, 
        NiAVObjectRawList& kCasterList);

protected:
    void AdditiveListHelper(NiNode* pkNode, NiAVObjectRawList* pkObjList);
    void SubtractiveListHelper(NiNode* pkNode, NiAVObjectRawList* pkObjList);

    virtual bool ShouldProcessNodeChildren(NiNode* pkNode) = 0;
};

#endif // NISHADOWVISITOR_H