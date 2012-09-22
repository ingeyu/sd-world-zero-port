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

// Precompiled Header
#include "NiEntityPCH.h"

#include "NiShadowGeneratorComponent.h"
#include <NiPSSMShadowClickGenerator.h>
#include <NiPSSMConfiguration.h>
#include <NiNode.h>

NiFixedString NiShadowGeneratorComponent::ERR_SCENE_ROOT_POINTER_NOT_FOUND;
NiFixedString NiShadowGeneratorComponent
    ::ERR_SCENE_ROOT_POINTER_NOT_A_DYNAMIC_EFFECT;

NiFixedString NiShadowGeneratorComponent::SEMANTIC_SIZE_HINT;
NiFixedString NiShadowGeneratorComponent::SEMANTIC_SHADOW_TECHNIQUE;
NiFixedString NiShadowGeneratorComponent::SEMANTIC_DEPTH_BIAS;

NiFixedString NiShadowGeneratorComponent::ms_kClassName;
NiFixedString NiShadowGeneratorComponent::ms_kComponentName;

NiFixedString NiShadowGeneratorComponent::ms_kCastShadowsName;
NiFixedString NiShadowGeneratorComponent::ms_kStaticShadowsName;
NiFixedString NiShadowGeneratorComponent::ms_kSizeHintName;
NiFixedString NiShadowGeneratorComponent::ms_kStrictlyObserveSizeHintName;
NiFixedString NiShadowGeneratorComponent::ms_kUnaffectedCastersName;
NiFixedString NiShadowGeneratorComponent::ms_kUnaffectedReceiversName;
NiFixedString NiShadowGeneratorComponent::ms_kShadowTechniqueName;
NiFixedString NiShadowGeneratorComponent::ms_kRenderBackfacesName;
NiFixedString NiShadowGeneratorComponent::ms_kDepthBiasName;
NiFixedString NiShadowGeneratorComponent::ms_kUseDefaultDepthBiasName;
NiFixedString NiShadowGeneratorComponent::ms_kShadowGeneratorPointerName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMEnabledName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMNumSlicesName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSceneDependentFrustumsName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMShimmerSupressionName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSliceTransitionEnabledName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSliceTransitionSizeName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSliceTransitionScaleName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSliceLambdaName;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMCameraDistanceScaleFactor;

NiFixedString NiShadowGeneratorComponent::ms_kCastShadowsDescription;
NiFixedString NiShadowGeneratorComponent::ms_kStaticShadowsDescription;
NiFixedString NiShadowGeneratorComponent::ms_kSizeHintDescription;
NiFixedString NiShadowGeneratorComponent
    ::ms_kStrictlyObserveSizeHintDescription;
NiFixedString NiShadowGeneratorComponent::ms_kUnaffectedCastersDescription;
NiFixedString NiShadowGeneratorComponent::ms_kUnaffectedReceiversDescription;
NiFixedString NiShadowGeneratorComponent::ms_kShadowTechniqueDescription;
NiFixedString NiShadowGeneratorComponent::ms_kRenderBackfacesDescription;
NiFixedString NiShadowGeneratorComponent::ms_kDepthBiasDescription;
NiFixedString NiShadowGeneratorComponent::ms_kUseDefaultDepthBiasDescription;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMEnabledDescription;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMNumSlicesDescription;
NiFixedString NiShadowGeneratorComponent
    ::ms_kPSSMSceneDependentFrustumsDescription;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMShimmerSupressionDescription;
NiFixedString NiShadowGeneratorComponent
    ::ms_kPSSMSliceTransitionEnabledDescription;
NiFixedString NiShadowGeneratorComponent
    ::ms_kPSSMSliceTransitionSizeDescription;
NiFixedString NiShadowGeneratorComponent
    ::ms_kPSSMSliceTransitionScaleDescription;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMSliceLambdaDescription;
NiFixedString NiShadowGeneratorComponent::ms_kPSSMCameraDistanceScaleFactorDescription;

NiFixedString NiShadowGeneratorComponent::ms_kPSSMCategoryName;

NiFixedString NiShadowGeneratorComponent::ms_kSceneRootPointerName;

NiFixedString NiShadowGeneratorComponent::ms_kPSSMClickGeneratorName;

//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::_SDMInit()
{
    ERR_SCENE_ROOT_POINTER_NOT_FOUND = "Scene Root Pointer not found.";
    ERR_SCENE_ROOT_POINTER_NOT_A_DYNAMIC_EFFECT = "Scene Root Pointer not an "
        "NiDynamicEffect.";

    SEMANTIC_SIZE_HINT = "Shadow Map Size Hint";
    SEMANTIC_SHADOW_TECHNIQUE = "Shadow Map Technique";
    SEMANTIC_DEPTH_BIAS = "Shadow Map Depth Bias";

    ms_kClassName = "NiShadowGeneratorComponent";
    ms_kComponentName = "Shadow Generator";

    ms_kCastShadowsName = "Cast Shadows";
    ms_kStaticShadowsName = "Static Shadows";
    ms_kSizeHintName = "Size Hint";
    ms_kStrictlyObserveSizeHintName = "Strictly Observe Size Hint";
    ms_kUnaffectedCastersName = "Unaffected Casters";
    ms_kUnaffectedReceiversName = "Unaffected Receivers";
    ms_kShadowTechniqueName = "Shadow Technique";
    ms_kRenderBackfacesName = "Render Backfaces";
    ms_kDepthBiasName = "Depth Bias";
    ms_kUseDefaultDepthBiasName = "Use Default Depth Bias";
    ms_kShadowGeneratorPointerName = "Shadow Generator Pointer";
    ms_kPSSMEnabledName = "Enable PSSM";
    ms_kPSSMNumSlicesName = "Slice Count";
    ms_kPSSMSceneDependentFrustumsName = "Scene Dependent Frustums";
    ms_kPSSMShimmerSupressionName = "Suppress Shadowmap Shimmer";
    ms_kPSSMSliceTransitionEnabledName = "Slice Transitions";
    ms_kPSSMSliceTransitionSizeName = "Slice Transition Length";
    ms_kPSSMSliceTransitionScaleName = "Slice Transition Noise Granularity";
    ms_kPSSMSliceLambdaName = "Slice Distance Exponent Factor";
    ms_kPSSMCameraDistanceScaleFactor = "Camera Distance Scale Factor";

    ms_kCastShadowsDescription = "Whether or not the shadow generator casts "
        "shadows.";
    ms_kStaticShadowsDescription = "Whether or not the shadow generator will "
        "generate shadow maps each frame. A static generator will only "
        "generate shadow maps once.";
    ms_kSizeHintDescription = "A hint for the size of the shadow map. This "
        "value must be a nonzero power of two.";
    ms_kStrictlyObserveSizeHintDescription = "Indicates whether or not a new "
        "shadow map should be created if the requested size is not found. If "
        "this is false, the closest-sized shadow map found will be used if it "
        "exists.";
    ms_kUnaffectedCastersDescription = "A collection of entities that will "
        "not cast shadows from this shadow generator.";
    ms_kUnaffectedReceiversDescription = "A collection of entities that will "
        "not receive shadows from this shadow generator.";
    ms_kShadowTechniqueDescription = "The shadow technique to use when "
        "generating shadow maps.";
    ms_kRenderBackfacesDescription = "Whether or not the shadow generator "
        "will use backward-facing triangles instead of forward-facing "
        "triangles when generating shadow maps in order to reduce shadowing "
        "artifacts.";
    ms_kDepthBiasDescription = "A bias value used to offset the shadow map "
        "depth values from surfaces receiving shadows. Tweaking this value "
        "can help reduce shadowing artifacts.";
    ms_kUseDefaultDepthBiasDescription = "Whether or not to allow the "
        "shadowing system to set the depth bias to an appropriate default "
        "value. This value should be set to false if the depth bias is to be "
        "manually specified.";
    ms_kPSSMEnabledDescription = "Nominates that this generator should be used "
        "for PSSM shadowing. Note that only 1 generator can use PSSM at "
        "any one time - if multiple generators are nominated, the first one "
        "to be updated will be used.";
    ms_kPSSMNumSlicesDescription = "How many slices to split the view frustum "
        "into. One PSSM cell be be created for each slice. A value of 1 "
        "disables PSSM for this generator.";
    ms_kPSSMSceneDependentFrustumsDescription = "If enabled, each PSSM slice "
        "will attempt to shrink itself to best fit the affected casters and "
        "receivers within the split. This has additional CPU cost, and will "
        "give the best visual results when used with high resolution shadow "
        "maps.";
    ms_kPSSMShimmerSupressionDescription = "Quantize the shadow-map camera's "
        "movements so that they snap to the shadow maps pixels. This removes "
        "shadow shimmering when the view camera moves. It has no effect on "
        "any shimmering caused by movement of the casting light.";
    ms_kPSSMSliceTransitionEnabledDescription = "Enable smooth transitions "
        "between PSSM splits, using random noise.";
    ms_kPSSMSliceTransitionSizeDescription = "The distance, in world "
        "dimensions, of the transition from one slice to the next.";
    ms_kPSSMSliceTransitionScaleDescription = "The size of each noise pixel "
        "in a slice transition. A lower number will increase the size of each "
        "noise pixel.";
    ms_kPSSMSliceLambdaDescription = "Defines how much larger a given PSSM "
        "slice will be in comparison to the previous. A larger value will "
        "create a bigger difference in size; therefore biasing more shadowmap "
        "pixels to objects nearer to the visible camera.";
    ms_kPSSMCameraDistanceScaleFactorDescription = "Defines how far the "
        "shadow map camera will be placed from the scene. A larger scale factor "
        "helps to eliminate shadow clipping, but reduces shadow map precision.";

    ms_kPSSMCategoryName = "Parallel Split Shadow Mapping";

    ms_kSceneRootPointerName = "Scene Root Pointer";

    ms_kPSSMClickGeneratorName = "NiPSSMShadowClickGenerator";
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::_SDMShutdown()
{
    ERR_SCENE_ROOT_POINTER_NOT_FOUND = NULL;
    ERR_SCENE_ROOT_POINTER_NOT_A_DYNAMIC_EFFECT = NULL;

    SEMANTIC_SIZE_HINT = NULL;
    SEMANTIC_SHADOW_TECHNIQUE = NULL;
    SEMANTIC_DEPTH_BIAS = NULL;

    ms_kClassName = NULL;
    ms_kComponentName = NULL;

    ms_kCastShadowsName = NULL;
    ms_kStaticShadowsName = NULL;
    ms_kSizeHintName = NULL;
    ms_kStrictlyObserveSizeHintName = NULL;
    ms_kUnaffectedCastersName = NULL;
    ms_kUnaffectedReceiversName = NULL;
    ms_kShadowTechniqueName = NULL;
    ms_kRenderBackfacesName = NULL;
    ms_kDepthBiasName = NULL;
    ms_kUseDefaultDepthBiasName = NULL;
    ms_kShadowGeneratorPointerName = NULL;
    ms_kPSSMEnabledName = NULL;
    ms_kPSSMNumSlicesName = NULL;
    ms_kPSSMSceneDependentFrustumsName = NULL;
    ms_kPSSMShimmerSupressionName = NULL;
    ms_kPSSMSliceTransitionEnabledName = NULL;
    ms_kPSSMSliceTransitionSizeName = NULL;
    ms_kPSSMSliceTransitionScaleName = NULL;
    ms_kPSSMSliceLambdaName = NULL;
    ms_kPSSMCameraDistanceScaleFactor = NULL;

    ms_kCastShadowsDescription = NULL;
    ms_kStaticShadowsDescription = NULL;
    ms_kSizeHintDescription = NULL;
    ms_kStrictlyObserveSizeHintDescription = NULL;
    ms_kUnaffectedCastersDescription = NULL;
    ms_kUnaffectedReceiversDescription = NULL;
    ms_kShadowTechniqueDescription = NULL;
    ms_kRenderBackfacesDescription = NULL;
    ms_kDepthBiasDescription = NULL;
    ms_kUseDefaultDepthBiasDescription = NULL;
    ms_kPSSMEnabledDescription = NULL;
    ms_kPSSMNumSlicesDescription = NULL;
    ms_kPSSMSceneDependentFrustumsDescription = NULL;
    ms_kPSSMShimmerSupressionDescription = NULL;
    ms_kPSSMSliceTransitionEnabledDescription = NULL;
    ms_kPSSMSliceTransitionSizeDescription = NULL;
    ms_kPSSMSliceTransitionScaleDescription = NULL;
    ms_kPSSMSliceLambdaDescription = NULL;
    ms_kPSSMCameraDistanceScaleFactorDescription = NULL;

    ms_kPSSMCategoryName = NULL;

    ms_kSceneRootPointerName = NULL;

    ms_kPSSMClickGeneratorName = NULL;
}
//---------------------------------------------------------------------------
// NiEntityComponentInterface overrides.
//---------------------------------------------------------------------------
NiEntityComponentInterface* NiShadowGeneratorComponent::Clone(
    bool bInheritProperties)
{
    NiShadowGeneratorComponent* pkMasterComponent;
    if (bInheritProperties)
    {
        pkMasterComponent = this;
    }
    else
    {
        pkMasterComponent = m_spMasterComponent;
    }

    NiShadowGeneratorComponent* pkClone = NiNew NiShadowGeneratorComponent(
        m_kUnaffectedCasters.GetAllocatedSize(),
        m_kUnaffectedCasters.GetGrowBy(),
        m_kUnaffectedReceivers.GetAllocatedSize(),
        m_kUnaffectedReceivers.GetGrowBy(), pkMasterComponent);

    pkClone->m_uFlags = m_uFlags;
    pkClone->m_kShadowTechnique = m_kShadowTechnique;
    pkClone->m_fDepthBias = m_fDepthBias;
    pkClone->m_usSizeHint = m_usSizeHint;
    pkClone->m_bCastShadows = m_bCastShadows;
    pkClone->m_bStaticShadows = m_bStaticShadows;
    pkClone->m_bStrictlyObserveSizeHint = m_bStrictlyObserveSizeHint;
    pkClone->m_bRenderBackfaces = m_bRenderBackfaces;
    pkClone->m_bUseDefaultDepthBias = m_bUseDefaultDepthBias;
    pkClone->m_usPSSMNumSlices = m_usPSSMNumSlices;
    pkClone->m_bPSSMEnabled = m_bPSSMEnabled;
    pkClone->m_bPSSMSceneDependentFrustums = m_bPSSMSceneDependentFrustums;
    pkClone->m_bPSSMShimmerSuppression = m_bPSSMShimmerSuppression;
    pkClone->m_bPSSMSliceTransition = m_bPSSMSliceTransition;
    pkClone->m_fPSSMSliceTransitionSize = m_fPSSMSliceTransitionSize;
    pkClone->m_fPSSMSliceTransitionScale = m_fPSSMSliceTransitionScale;
    pkClone->m_fPSSMSliceLambda = m_fPSSMSliceLambda;
    pkClone->m_fPSSMCameraDistanceScaleFactor = m_fPSSMCameraDistanceScaleFactor;
    pkClone->SetPSSMPropertiesChanged(true);

    for (unsigned int ui = 0; ui < m_kUnaffectedCasters.GetSize(); ui++)
    {
        pkClone->m_kUnaffectedCasters.SetAt(ui,
            m_kUnaffectedCasters.GetAt(ui));
    }
    for (unsigned int ui = 0; ui < m_kUnaffectedReceivers.GetSize(); ui++)
    {
        pkClone->m_kUnaffectedReceivers.SetAt(ui,
            m_kUnaffectedReceivers.GetAt(ui));
    }

    return pkClone;
}
//---------------------------------------------------------------------------
NiEntityComponentInterface* NiShadowGeneratorComponent::GetMasterComponent()
    const
{
    return m_spMasterComponent;
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::SetMasterComponent(
    NiEntityComponentInterface* pkMasterComponent)
{
    if (pkMasterComponent)
    {
        NIASSERT(pkMasterComponent->GetClassName() == GetClassName());
        m_spMasterComponent = (NiShadowGeneratorComponent*) pkMasterComponent;
    }
    else
    {
        NiTObjectSet<NiFixedString> kPropertyNames(10);
        GetPropertyNames(kPropertyNames);
        unsigned int uiSize = kPropertyNames.GetSize();
        for (unsigned int ui = 0; ui < uiSize; ui++)
        {
            bool bMadeUnique;
            NIVERIFY(MakePropertyUnique(kPropertyNames.GetAt(ui),
                bMadeUnique));
        }
        m_spMasterComponent = NULL;
    }
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::GetDependentPropertyNames(
    NiTObjectSet<NiFixedString>& kDependentPropertyNames)
{
    kDependentPropertyNames.Add(ms_kSceneRootPointerName);
}
//---------------------------------------------------------------------------
// NiEntityPropertyInterface overrides.
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetTemplateID(const NiUniqueID&)
{
    // Not supported for custom components.
    return false;
}
//---------------------------------------------------------------------------
NiUniqueID NiShadowGeneratorComponent::GetTemplateID()
{
    static const NiUniqueID kUniqueID = 
        NiUniqueID(0xc1,0xb1,0x29,0x8f,0x1b,0xd7,0xe0,0x41,0xae,0x58,0x54,0x85,
        0x4b,0x06,0x9e,0x33);
    return kUniqueID;
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::AddReference()
{
    this->IncRefCount();
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::RemoveReference()
{
    this->DecRefCount();
}
//---------------------------------------------------------------------------
NiFixedString NiShadowGeneratorComponent::GetClassName() const
{
    return ms_kClassName;
}
//---------------------------------------------------------------------------
NiFixedString NiShadowGeneratorComponent::GetName() const
{
    return ms_kComponentName;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetName(const NiFixedString&)
{
    // This component does not allow its name to be set.
    return false;
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::Update(
    NiEntityPropertyInterface* pkParentEntity, float,
    NiEntityErrorInterface* pkErrors, NiExternalAssetManager*)
{
    NIASSERT(pkErrors);

    // Get dynamic effect from dependent property.
    NiObject* pkObject = NULL;
    if (!pkParentEntity->GetPropertyData(ms_kSceneRootPointerName, pkObject))
    {
        pkErrors->ReportError(ERR_SCENE_ROOT_POINTER_NOT_FOUND, NULL,
            pkParentEntity->GetName(), ms_kSceneRootPointerName);
    }
    NiDynamicEffect* pkDynamicEffect = NiDynamicCast(NiDynamicEffect,
        pkObject);
    if (!pkDynamicEffect)
    {
        // Only report an error if the object exists and is not a dynamic
        // effect. If the object does not exist, do not report an error, since
        // the object may exist in a future frame.
        if (pkObject)
        {
            pkErrors->ReportError(ERR_SCENE_ROOT_POINTER_NOT_A_DYNAMIC_EFFECT,
                NULL, pkParentEntity->GetName(), ms_kSceneRootPointerName);
        }
        return;
    }

    // If the dynamic effect has changed since the last frame, destroy the
    // shadow generator.
    if (m_spLastDynamicEffect != pkDynamicEffect)
    {
        ClearShadowGenerator();
        m_spLastDynamicEffect = pkDynamicEffect;
    }

    // If any of these properties have changed in the master component,
    // destroy the shadow generator.
    if (GetCastShadows() != m_bCastShadows ||
        GetSizeHint() != m_usSizeHint ||
        GetStrictlyObserveSizeHint() != m_bStrictlyObserveSizeHint)
    {
        ClearShadowGenerator();
    }

    // Create shadow generator if it is active and the shadow manager has been
    // initialized. If the shadow manager does not exist, do not create the
    // shadow generator.
    if (!m_spShadowGenerator && GetCastShadows() &&
        NiShadowManager::GetShadowManager())
    {
        // Create the shadow generator.
        CreateShadowGenerator(pkDynamicEffect);

        // Enable the setting of shadow generator properties.
        SetShadowGeneratorPropertiesChanged(true);
        SetUnaffectedCastersChanged(true);
        SetUnaffectedReceiversChanged(true);
    }

    bool bMarkDirty = false;
    if (m_spShadowGenerator)
    {
        // Set the properties of the shadow generator.
        if (ShouldUpdateShadowGeneratorProperties())
        {
            // Set the static flag on the shadow generator.
            m_spShadowGenerator->SetStatic(GetStaticShadows());

            // Set the size hint on the shadow generator.
            m_spShadowGenerator->SetSizeHint(GetSizeHint());

            // Set the strictly observe size hint flag on the shadow generator.
            m_spShadowGenerator->SetStrictlyObserveSizeHint(
                GetStrictlyObserveSizeHint());

            // Set the shadow technique on the shadow generator.
            m_spShadowGenerator->SetShadowTechnique(GetShadowTechnique());

            // Set the render backfaces flag.
            m_spShadowGenerator->SetRenderBackfaces(GetRenderBackfaces());

            // Check whether or not the default depth bias should be used.
            if (GetUseDefaultDepthBias())
            {
                // If using the default depth bias, set the depth bias to its
                // default value.
                m_spShadowGenerator->SetDepthBiasToDefault();
            }
            else
            {
                // If not using the default depth bias, set the depth bias
                // directly.
                m_spShadowGenerator->SetDepthBias(GetDepthBias());
            }

            // Set the PSSM properties
            if (m_spConfiguration == NULL)
                m_spConfiguration = NiNew NiPSSMConfiguration();

            NiPSSMShadowClickGenerator* pkPSSMClickGenerator = 
                NiDynamicCast(NiPSSMShadowClickGenerator, 
                NiShadowManager::GetShadowManager()->GetActiveShadowClickGenerator());

            // Note that even if we don't have a click generator, we
            // will still keep a valid configuration. It just won't
            // do anything.
            if (pkPSSMClickGenerator)
            {
                pkPSSMClickGenerator->BindConfiguration(
                    m_spShadowGenerator, m_spConfiguration);
            }

            m_spConfiguration->SetNumSlices(
                (NiUInt8)GetPSSMNumSlices());
            m_spConfiguration->SetSceneDependentFrustumsEnabled(
                GetPSSMSceneDependentFrustums());
            m_spConfiguration->SetSubTexelOffsetEnabled(
                GetPSSMShimmerSuppression());
            m_spConfiguration->SetSliceTransitionEnabled(
                GetPSSMSliceTransition());
            m_spConfiguration->SetSliceTransitionSize(
                GetPSSMSliceTransitionSize());
            m_spConfiguration->SetSliceTransitionNoiseScale(
                GetPSSMSliceTransitionScale());
            m_spConfiguration->SetSliceLambda(
                GetPSSMSliceLambda());
            m_spConfiguration->SetCameraDistanceScaleFactor(
                GetPSSMCameraDistanceScaleFactor());

            // Are we the active generator?
            const NiShadowGenerator* pkActiveGenerator = 
                NiPSSMShadowClickGenerator::GetActiveGenerator();

            if (GetPSSMEnabled() && pkActiveGenerator == NULL)
            {
                NiPSSMShadowClickGenerator::SetActiveGenerator(
                    m_spShadowGenerator);
            }
            else if (!GetPSSMEnabled() && 
                pkActiveGenerator == m_spShadowGenerator)
            {
                NiPSSMShadowClickGenerator::SetActiveGenerator(NULL);
            }

            RefreshCachedShadowGeneratorProperties();
            SetShadowGeneratorPropertiesChanged(false);
            SetPSSMPropertiesChanged(false);

            bMarkDirty = true;
        }

        // Update unaffected casters.
        if (GetUnaffectedCastersChanged())
        {
            // Clear all old casters.
            m_spShadowGenerator->DetachAllUnaffectedCasterNodes();

            // Add casters to shadow generator.
            bool bAllSuccessful = true;
            for (unsigned int ui = 0; ui < m_kUnaffectedCasters.GetSize();
                ui++)
            {
                NiEntityInterface* pkEntity = m_kUnaffectedCasters.GetAt(ui);
                if (!pkEntity)
                {
                    continue;
                }

                unsigned int uiCount;
                if (!pkEntity->GetElementCount(ms_kSceneRootPointerName,
                    uiCount))
                {
                    continue;
                }

                for (unsigned int uiIndex = 0; uiIndex < uiCount; uiIndex++)
                {
                    NiObject* pkSceneRoot;
                    NIVERIFY(pkEntity->GetPropertyData(
                        ms_kSceneRootPointerName, pkSceneRoot, uiIndex));

                    if (!pkSceneRoot)
                    {
                        bAllSuccessful = false;
                    }

                    NiNode* pkNode = NiDynamicCast(NiNode, pkSceneRoot);
                    if (pkNode)
                    {
                        m_spShadowGenerator->AttachUnaffectedCasterNode(
                            pkNode);
                    }
                }
            }

            if (bAllSuccessful)
            {
                SetUnaffectedCastersChanged(false);
            }

            bMarkDirty = true;
        }

        // Update unaffected receivers.
        if (GetUnaffectedReceiversChanged())
        {
            // Clear all old unaffected receivers.
            m_spShadowGenerator->DetachAllUnaffectedReceiverNodes();

            // Add unaffected receivers to shadow generator.
            bool bAllSuccessful = true;
            for (unsigned int ui = 0; ui < m_kUnaffectedReceivers.GetSize();
                ui++)
            {
                NiEntityInterface* pkEntity = m_kUnaffectedReceivers.GetAt(ui);
                if (!pkEntity)
                {
                    continue;
                }

                unsigned int uiCount;
                if (!pkEntity->GetElementCount(ms_kSceneRootPointerName,
                    uiCount))
                {
                    continue;
                }

                for (unsigned int uiIndex = 0; uiIndex < uiCount; uiIndex++)
                {
                    NiObject* pkSceneRoot;
                    NIVERIFY(pkEntity->GetPropertyData(
                        ms_kSceneRootPointerName, pkSceneRoot, uiIndex));

                    if (!pkSceneRoot)
                    {
                        bAllSuccessful = false;
                    }

                    NiNode* pkNode = NiDynamicCast(NiNode, pkSceneRoot);
                    if (pkNode)
                    {
                        m_spShadowGenerator->AttachUnaffectedReceiverNode(
                            pkNode);
                    }
                }
            }

            if (bAllSuccessful)
            {
                SetUnaffectedReceiversChanged(false);
            }

            bMarkDirty = true;
        }

        // Mark the shadow generator render views as dirty to force
        // regeneration of the shadow maps.
        if (bMarkDirty)
        {
            m_spShadowGenerator->SetRenderViewsDirty(true);
        }
    }
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::BuildVisibleSet(NiEntityRenderingContext*,
    NiEntityErrorInterface*)
{
    // This component has no work to do during BuildVisibleSet.
}
//---------------------------------------------------------------------------
void NiShadowGeneratorComponent::GetPropertyNames(
    NiTObjectSet<NiFixedString>& kPropertyNames) const
{
    kPropertyNames.Add(ms_kCastShadowsName);
    kPropertyNames.Add(ms_kStaticShadowsName);
    kPropertyNames.Add(ms_kSizeHintName);
    kPropertyNames.Add(ms_kStrictlyObserveSizeHintName);
    kPropertyNames.Add(ms_kUnaffectedCastersName);
    kPropertyNames.Add(ms_kUnaffectedReceiversName);
    kPropertyNames.Add(ms_kShadowTechniqueName);
    kPropertyNames.Add(ms_kRenderBackfacesName);
    kPropertyNames.Add(ms_kDepthBiasName);
    kPropertyNames.Add(ms_kUseDefaultDepthBiasName);
    kPropertyNames.Add(ms_kShadowGeneratorPointerName);
    kPropertyNames.Add(ms_kPSSMEnabledName);
    kPropertyNames.Add(ms_kPSSMNumSlicesName);
    kPropertyNames.Add(ms_kPSSMSceneDependentFrustumsName);
    kPropertyNames.Add(ms_kPSSMShimmerSupressionName);
    kPropertyNames.Add(ms_kPSSMSliceTransitionEnabledName);
    kPropertyNames.Add(ms_kPSSMSliceTransitionSizeName);
    kPropertyNames.Add(ms_kPSSMSliceTransitionScaleName);
    kPropertyNames.Add(ms_kPSSMSliceLambdaName);
    kPropertyNames.Add(ms_kPSSMCameraDistanceScaleFactor);
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::CanResetProperty(
    const NiFixedString& kPropertyName, bool& bCanReset) const
{
    if (kPropertyName == ms_kCastShadowsName)
    {
        bCanReset = (m_spMasterComponent && GetCastShadowsUnique());
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        bCanReset = (m_spMasterComponent && GetStaticShadowsUnique());
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        bCanReset = (m_spMasterComponent && GetSizeHintUnique());
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        bCanReset = (m_spMasterComponent &&
            GetStrictlyObserveSizeHintUnique());
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        bCanReset = (m_spMasterComponent && GetShadowTechniqueUnique());
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        bCanReset = (m_spMasterComponent && GetRenderBackfacesUnique());
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        bCanReset = (m_spMasterComponent && GetDepthBiasUnique());
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        bCanReset = (m_spMasterComponent && GetUseDefaultDepthBiasUnique());
    }    
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMEnabledUnique());
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMNumSlicesUnique());
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        bCanReset = (m_spMasterComponent && 
            GetPSSMSceneDependentFrustumsUnique());
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMShimmerSuppressionUnique());
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMSliceTransitionUnique());
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMSliceTransitionSizeUnique());
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        bCanReset = (m_spMasterComponent && 
            GetPSSMSliceTransitionScaleUnique());
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        bCanReset = (m_spMasterComponent && GetPSSMSliceLambdaUnique());
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bCanReset = (m_spMasterComponent && GetPSSMCameraDistanceScaleUnique());
    }  
    else if(kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowGeneratorPointerName)
    {
        bCanReset = false;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::ResetProperty(
    const NiFixedString& kPropertyName)
{
    bool bCanReset;
    if (!CanResetProperty(kPropertyName, bCanReset) || !bCanReset)
    {
        return false;
    }

    NIASSERT(m_spMasterComponent);

    if (kPropertyName == ms_kCastShadowsName)
    {
        SetCastShadowsUnique(false);
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        SetStaticShadowsUnique(false);
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        SetSizeHintUnique(false);
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        SetStrictlyObserveSizeHintUnique(false);
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        SetShadowTechniqueUnique(false);
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        SetRenderBackfacesUnique(false);
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        SetDepthBiasUnique(false);
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        SetUseDefaultDepthBiasUnique(false);
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        SetPSSMEnabledUnique(false);
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        SetPSSMNumSlicesUnique(false);
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        SetPSSMSceneDependentFrustumsUnique(false);
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        SetPSSMShimmerSuppressionUnique(false);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        SetPSSMSliceTransitionUnique(false);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        SetPSSMSliceTransitionSizeUnique(false);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        SetPSSMSliceTransitionScaleUnique(false);
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        SetPSSMSliceLambdaUnique(false);
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        SetPSSMCameraDistanceScaleUnique(false);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::MakePropertyUnique(
    const NiFixedString& kPropertyName, bool& bMadeUnique)
{
    bool bCanReset;
    if (!CanResetProperty(kPropertyName, bCanReset))
    {
        return false;
    }

    if (!bCanReset && m_spMasterComponent)
    {
        if (kPropertyName == ms_kCastShadowsName)
        {
            SetCastShadowsUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kStaticShadowsName)
        {
            SetStaticShadowsUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kSizeHintName)
        {
            SetSizeHintUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
        {
            SetStrictlyObserveSizeHintUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kShadowTechniqueName)
        {
            SetShadowTechniqueUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kRenderBackfacesName)
        {
            SetRenderBackfacesUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kDepthBiasName)
        {
            SetDepthBiasUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kUseDefaultDepthBiasName)
        {
            SetUseDefaultDepthBiasUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMEnabledName)
        {
            SetPSSMEnabledUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMNumSlicesName)
        {
            SetPSSMNumSlicesUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
        {
            SetPSSMSceneDependentFrustumsUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMShimmerSupressionName)
        {
            SetPSSMShimmerSuppressionUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
        {
            SetPSSMSliceTransitionUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
        {
            SetPSSMSliceTransitionSizeUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
        {
            SetPSSMSliceTransitionScaleUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMSliceLambdaName)
        {
            SetPSSMSliceLambdaUnique(true);
            bMadeUnique = true;
        }
        else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
        {
            SetPSSMCameraDistanceScaleUnique(true);
            bMadeUnique = true;
        }        
        else
        {
            bMadeUnique = false;
        }
    }
    else
    {
        bMadeUnique = false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetDisplayName(
    const NiFixedString& kPropertyName, NiFixedString& kDisplayName) const
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor
        )
    {
        kDisplayName = kPropertyName;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        kDisplayName = NULL;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetDisplayName(
    const NiFixedString&, const NiFixedString&)
{
    // This component does not allow the display name to be set.
    return false;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPrimitiveType(
    const NiFixedString& kPropertyName, NiFixedString& kPrimitiveType) const
{
    if (kPropertyName == ms_kCastShadowsName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        kPrimitiveType = PT_USHORT;
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName)
    {
        kPrimitiveType = PT_ENTITYPOINTER;
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        kPrimitiveType = PT_ENTITYPOINTER;
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        kPrimitiveType = PT_STRING;
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        kPrimitiveType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        kPrimitiveType = PT_NIOBJECTPOINTER;
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        kPrimitiveType = PT_USHORT;
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        kPrimitiveType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        kPrimitiveType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        kPrimitiveType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        kPrimitiveType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        kPrimitiveType = PT_FLOAT;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPrimitiveType(
    const NiFixedString&, const NiFixedString&)
{
    // This component does not allow the primitive type to be set.
    return false;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetSemanticType(
    const NiFixedString& kPropertyName, NiFixedString& kSemanticType) const
{
    if (kPropertyName == ms_kCastShadowsName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        kSemanticType = SEMANTIC_SIZE_HINT;
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName)
    {
        kSemanticType = PT_ENTITYPOINTER;
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        kSemanticType = PT_ENTITYPOINTER;
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        kSemanticType = SEMANTIC_SHADOW_TECHNIQUE;
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        kSemanticType = SEMANTIC_DEPTH_BIAS;
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        kSemanticType = PT_NIOBJECTPOINTER;
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        kSemanticType = PT_USHORT;
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        kSemanticType = PT_BOOL;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        kSemanticType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        kSemanticType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        kSemanticType = PT_FLOAT;
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        kSemanticType = PT_FLOAT;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetSemanticType(const NiFixedString&,
    const NiFixedString&)
{
    // This component does not allow the semantic type to be set.
    return false;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetDescription(
    const NiFixedString& kPropertyName, NiFixedString& kDescription) const
{
    if (kPropertyName == ms_kCastShadowsName)
    {
        kDescription = ms_kCastShadowsDescription;
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        kDescription = ms_kStaticShadowsDescription;
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        kDescription = ms_kSizeHintDescription;
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        kDescription = ms_kStrictlyObserveSizeHintDescription;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName)
    {
        kDescription = ms_kUnaffectedCastersDescription;
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        kDescription = ms_kUnaffectedReceiversDescription;
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        kDescription = ms_kShadowTechniqueDescription;
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        kDescription = ms_kRenderBackfacesDescription;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        kDescription = ms_kDepthBiasDescription;
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        kDescription = ms_kUseDefaultDepthBiasDescription;
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        kDescription = ms_kPSSMEnabledDescription;
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        kDescription = ms_kPSSMNumSlicesDescription;
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        kDescription = ms_kPSSMSceneDependentFrustumsDescription;
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        kDescription = ms_kPSSMShimmerSupressionDescription;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        kDescription = ms_kPSSMSliceTransitionEnabledDescription;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        kDescription = ms_kPSSMSliceTransitionSizeDescription;
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        kDescription = ms_kPSSMSliceTransitionScaleDescription;
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        kDescription = ms_kPSSMSliceLambdaDescription;
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        kDescription = ms_kPSSMCameraDistanceScaleFactorDescription;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        // This is a hidden property, so no description is provided.
        kDescription = NULL;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetDescription(
    const NiFixedString&, const NiFixedString&)
{
    // This component does not allow the description to be set.
    return false;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetCategory(
    const NiFixedString& kPropertyName, NiFixedString& kCategory) const
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kShadowGeneratorPointerName)
    {
        kCategory = ms_kComponentName;
    }
    else if (kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        kCategory = ms_kPSSMCategoryName;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsPropertyReadOnly(
    const NiFixedString& kPropertyName, bool& bIsReadOnly)
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bIsReadOnly = false;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        bIsReadOnly = GetUseDefaultDepthBias();
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        bIsReadOnly = true;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsPropertyUnique(
    const NiFixedString& kPropertyName, bool& bIsUnique)
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        if (m_spMasterComponent)
        {
            NIVERIFY(CanResetProperty(kPropertyName, bIsUnique));
        }
        else
        {
            bIsUnique = true;
        }
    }
    else if (kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowGeneratorPointerName)
    {
        bIsUnique = true;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsPropertySerializable(
    const NiFixedString& kPropertyName, bool& bIsSerializable)
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bool bIsUnique;
        NIVERIFY(IsPropertyUnique(kPropertyName, bIsUnique));

        bool bIsReadOnly;
        NIVERIFY(IsPropertyReadOnly(kPropertyName, bIsReadOnly));

        bIsSerializable = bIsUnique && !bIsReadOnly;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        bIsSerializable = false;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsPropertyInheritable(
    const NiFixedString& kPropertyName, bool& bIsInheritable)
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bIsInheritable = true;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowGeneratorPointerName)
    {
        bIsInheritable = false;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsExternalAssetPath(
    const NiFixedString& kPropertyName, unsigned int,
    bool& bIsExternalAssetPath) const
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kShadowGeneratorPointerName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bIsExternalAssetPath = false;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetElementCount(
    const NiFixedString& kPropertyName, unsigned int& uiCount) const
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kShadowGeneratorPointerName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        uiCount = 1;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName)
    {
        uiCount = m_kUnaffectedCasters.GetSize();
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        uiCount = m_kUnaffectedReceivers.GetSize();
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetElementCount(
    const NiFixedString& kPropertyName, unsigned int uiCount, bool& bCountSet)
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kShadowGeneratorPointerName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bCountSet = false;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName)
    {
        const unsigned int uiOrigCount = m_kUnaffectedCasters.GetSize();
        for (unsigned int ui = uiCount; ui < uiOrigCount; ui++)
        {
            SetPropertyData(kPropertyName, (NiEntityInterface*) NULL, ui);
        }
        m_kUnaffectedCasters.SetSize(uiCount);
        bCountSet = true;
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        const unsigned int uiOrigCount = m_kUnaffectedReceivers.GetSize();
        for (unsigned int ui = uiCount; ui < uiOrigCount; ui++)
        {
            SetPropertyData(kPropertyName, (NiEntityInterface*) NULL, ui);
        }
        m_kUnaffectedReceivers.SetSize(uiCount);
        bCountSet = true;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::IsCollection(
    const NiFixedString& kPropertyName, bool& bIsCollection) const
{
    if (kPropertyName == ms_kCastShadowsName ||
        kPropertyName == ms_kStaticShadowsName ||
        kPropertyName == ms_kSizeHintName ||
        kPropertyName == ms_kStrictlyObserveSizeHintName ||
        kPropertyName == ms_kShadowTechniqueName ||
        kPropertyName == ms_kRenderBackfacesName ||
        kPropertyName == ms_kDepthBiasName ||
        kPropertyName == ms_kUseDefaultDepthBiasName ||
        kPropertyName == ms_kShadowGeneratorPointerName ||
        kPropertyName == ms_kPSSMEnabledName ||
        kPropertyName == ms_kPSSMNumSlicesName ||
        kPropertyName == ms_kPSSMSceneDependentFrustumsName ||
        kPropertyName == ms_kPSSMShimmerSupressionName ||
        kPropertyName == ms_kPSSMSliceTransitionEnabledName ||
        kPropertyName == ms_kPSSMSliceTransitionSizeName ||
        kPropertyName == ms_kPSSMSliceTransitionScaleName ||
        kPropertyName == ms_kPSSMSliceLambdaName ||
        kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        bIsCollection = false;
    }
    else if (kPropertyName == ms_kUnaffectedCastersName ||
        kPropertyName == ms_kUnaffectedReceiversName)
    {
        bIsCollection = true;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, float& fData, unsigned int uiIndex)
    const
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        fData = GetDepthBias();
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        fData = GetPSSMSliceTransitionSize();
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        fData = GetPSSMSliceTransitionScale();
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        fData = GetPSSMSliceLambda();
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        fData = GetPSSMCameraDistanceScaleFactor();
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPropertyData(
    const NiFixedString& kPropertyName, float fData, unsigned int uiIndex)
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kDepthBiasName)
    {
        SetDepthBias(fData);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionSizeName)
    {
        SetPSSMSliceTransitionSize(fData);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionScaleName)
    {
        SetPSSMSliceTransitionScale(fData);
    }
    else if (kPropertyName == ms_kPSSMSliceLambdaName)
    {
        SetPSSMSliceLambda(fData);
    }
    else if (kPropertyName == ms_kPSSMCameraDistanceScaleFactor)
    {
        SetPSSMCameraDistanceScaleFactor(fData);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, bool& bData, unsigned int uiIndex)
    const
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kCastShadowsName)
    {
        bData = GetCastShadows();
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        bData = GetStaticShadows();
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        bData = GetStrictlyObserveSizeHint();
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        bData = GetRenderBackfaces();
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        bData = GetUseDefaultDepthBias();
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        bData = GetPSSMEnabled();
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        bData = GetPSSMSceneDependentFrustums();
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        bData = GetPSSMShimmerSuppression();
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        bData = GetPSSMSliceTransition();
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPropertyData(
    const NiFixedString& kPropertyName, bool bData, unsigned int uiIndex)
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kCastShadowsName)
    {
        SetCastShadows(bData);
    }
    else if (kPropertyName == ms_kStaticShadowsName)
    {
        SetStaticShadows(bData);
    }
    else if (kPropertyName == ms_kStrictlyObserveSizeHintName)
    {
        SetStrictlyObserveSizeHint(bData);
    }
    else if (kPropertyName == ms_kRenderBackfacesName)
    {
        SetRenderBackfaces(bData);
    }
    else if (kPropertyName == ms_kUseDefaultDepthBiasName)
    {
        SetUseDefaultDepthBias(bData);
    }
    else if (kPropertyName == ms_kPSSMEnabledName)
    {
        SetPSSMEnabled(bData);
    }
    else if (kPropertyName == ms_kPSSMSceneDependentFrustumsName)
    {
        SetPSSMSceneDependentFrustums(bData);
    }
    else if (kPropertyName == ms_kPSSMShimmerSupressionName)
    {
        SetPSSMShimmerSupression(bData);
    }
    else if (kPropertyName == ms_kPSSMSliceTransitionEnabledName)
    {
        SetPSSMSliceTransition(bData);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, unsigned short& usData,
    unsigned int uiIndex) const
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        usData = GetSizeHint();
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        usData = GetPSSMNumSlices();
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPropertyData(
    const NiFixedString& kPropertyName, unsigned short usData,
    unsigned int uiIndex)
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kSizeHintName)
    {
        SetSizeHint(usData);
    }
    else if (kPropertyName == ms_kPSSMNumSlicesName)
    {
        SetPSSMNumSlices(usData);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, NiFixedString& kData,
    unsigned int uiIndex) const
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        kData = GetShadowTechnique();
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPropertyData(
    const NiFixedString& kPropertyName, const NiFixedString& kData,
    unsigned int uiIndex)
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kShadowTechniqueName)
    {
        SetShadowTechnique(kData);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, NiObject*& pkData,
    unsigned int uiIndex) const
{
    if (uiIndex != 0)
    {
        return false;
    }
    else if (kPropertyName == ms_kShadowGeneratorPointerName)
    {
        pkData = m_spShadowGenerator;
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::GetPropertyData(
    const NiFixedString& kPropertyName, NiEntityInterface*& pkData,
    unsigned int uiIndex) const
{
    if (kPropertyName == ms_kUnaffectedCastersName)
    {
        if (uiIndex < GetUnaffectedCasterCount())
        {
            pkData = GetUnaffectedCasterAt(uiIndex);
        }
        else
        {
            pkData = NULL;
        }
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        if (uiIndex < GetUnaffectedReceiverCount())
        {
            pkData = GetUnaffectedReceiverAt(uiIndex);
        }
        else
        {
            pkData = NULL;
        }
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
NiBool NiShadowGeneratorComponent::SetPropertyData(
    const NiFixedString& kPropertyName, NiEntityInterface* pkData,
    unsigned int uiIndex)
{
    if (kPropertyName == ms_kUnaffectedCastersName)
    {
        m_kUnaffectedCasters.SetAtGrow(uiIndex, pkData);
        m_kUnaffectedCasters.UpdateSize();
        SetUnaffectedCastersChanged(true);
    }
    else if (kPropertyName == ms_kUnaffectedReceiversName)
    {
        m_kUnaffectedReceivers.SetAtGrow(uiIndex, pkData);
        m_kUnaffectedReceivers.UpdateSize();
        SetUnaffectedReceiversChanged(true);
    }
    else
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------