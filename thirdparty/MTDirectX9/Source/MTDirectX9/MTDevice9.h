//*************************************************************************************************
// ����:	���߳���Ⱦ����,���D3D9ԭ�к�����ִ��
//---------------------------------------------------------
// ����:		
// ����:		2013-03-08
// ����޸�:	
//*************************************************************************************************
#ifndef MTDEVICE9_HEAD_FILE
#define MTDEVICE9_HEAD_FILE

#include "MTHeader.h"
#include "MTRenderThread.h"

//-------------------------------------------------------------------------------------------------
// D3D���Ŀ���20��Interface:
//  IDirect3D9					���ֺ�������(*)
//	IDirect3D9Ex				���ֺ�������(*)
//	IDirect3DBaseTexture9		���ֺ�������
//	IDirect3DCubeTexture9		���ֺ�������
//	IDirect3DDevice9			���ֺ�������
//	IDirect3DDevice9Ex
//	IDirect3DIndexBuffer9		���ֺ�������
//	IDirect3DPixelShader9
//	IDirect3DQuery9
//	IDirect3DResource9
//	IDirect3DStateBlock9		���ֺ�������
//	IDirect3DSurface9			���ֺ�������
//	IDirect3DSwapChain9			���ֺ�������
//	IDirect3DSwapChain9Ex
//	IDirect3DTexture9			���ֺ�������
//	IDirect3DVertexBuffer9		���ֺ�������
//	IDirect3DVertexDeclaration9	���ֺ�������
//	IDirect3DVertexShader9
//	IDirect3DVolume9			���ֺ�������
//	IDirect3DVolumeTexture9		���ֺ�������
//
// D3D Effect����6��Interface:
//	ID3DXBaseEffect
//	ID3DXEffect
//	ID3DXEffectCompiler
//	ID3DXEffectPool
//	ID3DXEffectStateManager
//	ID3DXInclude
//
// D3DX��:
//
// PIX��:
//
//-------------------------------------------------------------------------------------------------
// IDirect3DDevice9
ULONG	(STDMETHODCALLTYPE MT_Device_Release)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_BeginScene)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_BeginStateBlock)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_Clear)(IDirect3DDevice9* pThis, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
HRESULT	(STDMETHODCALLTYPE MT_ColorFill)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color);
HRESULT	(STDMETHODCALLTYPE MT_CreateAdditionalSwapChain)(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain);
HRESULT	(STDMETHODCALLTYPE MT_CreateCubeTexture)(IDirect3DDevice9* pThis, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateDepthStencilSurface)(IDirect3DDevice9* pThis, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateIndexBuffer)(IDirect3DDevice9* pThis, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateOffscreenPlainSurface)(IDirect3DDevice9* pThis, UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreatePixelShader)(IDirect3DDevice9* pThis, CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader);
HRESULT	(STDMETHODCALLTYPE MT_CreateQuery)(IDirect3DDevice9* pThis, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);
HRESULT	(STDMETHODCALLTYPE MT_CreateRenderTarget)(IDirect3DDevice9* pThis, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateStateBlock)(IDirect3DDevice9* pThis, D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB);
HRESULT	(STDMETHODCALLTYPE MT_CreateTexture)(IDirect3DDevice9* pThis, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateVertexBuffer)(IDirect3DDevice9* pThis, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_CreateVertexDeclaration)(IDirect3DDevice9* pThis, CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl);
HRESULT	(STDMETHODCALLTYPE MT_CreateVertexShader)(IDirect3DDevice9* pThis, CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader);
HRESULT	(STDMETHODCALLTYPE MT_CreateVolumeTexture)(IDirect3DDevice9* pThis, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle);
HRESULT	(STDMETHODCALLTYPE MT_DeletePatch)(IDirect3DDevice9* pThis, UINT Handle);
HRESULT	(STDMETHODCALLTYPE MT_DrawIndexedPrimitive)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
HRESULT	(STDMETHODCALLTYPE MT_DrawIndexedPrimitiveUP)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
HRESULT	(STDMETHODCALLTYPE MT_DrawPrimitive)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
HRESULT	(STDMETHODCALLTYPE MT_DrawPrimitiveUP)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
HRESULT	(STDMETHODCALLTYPE MT_DrawRectPatch)(IDirect3DDevice9* pThis, UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo);
HRESULT	(STDMETHODCALLTYPE MT_DrawTriPatch)(IDirect3DDevice9* pThis, UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo);
HRESULT	(STDMETHODCALLTYPE MT_EndScene)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_EndStateBlock)(IDirect3DDevice9* pThis, IDirect3DStateBlock9** ppSB);
HRESULT	(STDMETHODCALLTYPE MT_EvictManagedResources)(IDirect3DDevice9* pThis);
//HRESULT (STDMETHODCALLTYPE MT_GetAvailableTextureMem(IDirect3DDevice9* pThis));
HRESULT	(STDMETHODCALLTYPE MT_GetBackBuffer)(IDirect3DDevice9* pThis, UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
HRESULT	(STDMETHODCALLTYPE MT_GetClipPlane)(IDirect3DDevice9* pThis, DWORD Index, float* pPlane);
HRESULT	(STDMETHODCALLTYPE MT_GetClipStatus)(IDirect3DDevice9* pThis, D3DCLIPSTATUS9* pClipStatus);
//HRESULT (STDMETHODCALLTYPE MT_GetCreationParameters)(IDirect3DDevice9* pThis, D3DDEVICE_CREATION_PARAMETERS* pParameters);
HRESULT	(STDMETHODCALLTYPE MT_GetCurrentTexturePalette)(IDirect3DDevice9* pThis, UINT *PaletteNumber);
HRESULT	(STDMETHODCALLTYPE MT_GetDepthStencilSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9** ppZStencilSurface);
//HRESULT (STDMETHODCALLTYPE MT_GetDeviceCaps)(IDirect3DDevice9* pThis, D3DCAPS9* pCaps);
//HRESULT (STDMETHODCALLTYPE MT_GetDirect3D)(IDirect3DDevice9* pThis, IDirect3D9** ppD3D9);
//HRESULT (STDMETHODCALLTYPE MT_GetDisplayMode)(IDirect3DDevice9* pThis, UINT iSwapChain, D3DDISPLAYMODE* pMode);
HRESULT	(STDMETHODCALLTYPE MT_GetFrontBufferData)(IDirect3DDevice9* pThis, UINT iSwapChain, IDirect3DSurface9* pDestSurface);
HRESULT	(STDMETHODCALLTYPE MT_GetFVF)(IDirect3DDevice9* pThis, DWORD* pFVF);
void	(STDMETHODCALLTYPE MT_GetGammaRamp)(IDirect3DDevice9* pThis, UINT iSwapChain, D3DGAMMARAMP* pRamp);
HRESULT	(STDMETHODCALLTYPE MT_GetIndices)(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9** ppIndexData);
HRESULT	(STDMETHODCALLTYPE MT_GetLight)(IDirect3DDevice9* pThis, DWORD Index,D3DLIGHT9*);
HRESULT	(STDMETHODCALLTYPE MT_GetLightEnable)(IDirect3DDevice9* pThis, DWORD Index, BOOL* pEnable);
HRESULT	(STDMETHODCALLTYPE MT_GetMaterial)(IDirect3DDevice9* pThis, D3DMATERIAL9* pMaterial);
float	(STDMETHODCALLTYPE MT_GetNPatchMode)(IDirect3DDevice9* pThis);
UINT	(STDMETHODCALLTYPE MT_GetNumberOfSwapChains)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_GetPaletteEntries)(IDirect3DDevice9* pThis, UINT PaletteNumber, PALETTEENTRY* pEntries);
HRESULT	(STDMETHODCALLTYPE MT_GetPixelShader)(IDirect3DDevice9* pThis, IDirect3DPixelShader9** ppShader);
HRESULT	(STDMETHODCALLTYPE MT_GetPixelShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister, BOOL* pConstantData, UINT BoolCount);
HRESULT	(STDMETHODCALLTYPE MT_GetPixelShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister, float* pConstantData, UINT Vector4fCount);
HRESULT	(STDMETHODCALLTYPE MT_GetPixelShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister, int* pConstantData, UINT Vector4iCount);
HRESULT	(STDMETHODCALLTYPE MT_GetRasterStatus)(IDirect3DDevice9* pThis, UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus);
HRESULT	(STDMETHODCALLTYPE MT_GetRenderState)(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State, DWORD* pValue);
HRESULT	(STDMETHODCALLTYPE MT_GetRenderTarget)(IDirect3DDevice9* pThis, DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget);
HRESULT	(STDMETHODCALLTYPE MT_GetRenderTargetData)(IDirect3DDevice9* pThis, IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface);
HRESULT	(STDMETHODCALLTYPE MT_GetSamplerState)(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue);
HRESULT	(STDMETHODCALLTYPE MT_GetScissorRect)(IDirect3DDevice9* pThis, RECT* pRect);
BOOL	(STDMETHODCALLTYPE MT_GetSoftwareVertexProcessing)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_GetStreamSource)(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride);
HRESULT	(STDMETHODCALLTYPE MT_GetStreamSourceFreq)(IDirect3DDevice9* pThis, UINT StreamNumber,UINT* pSetting);
HRESULT	(STDMETHODCALLTYPE MT_GetSwapChain)(IDirect3DDevice9* pThis, UINT iSwapChain,IDirect3DSwapChain9** pSwapChain);
HRESULT	(STDMETHODCALLTYPE MT_GetTexture)(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9** ppTexture);
HRESULT	(STDMETHODCALLTYPE MT_GetTextureStageState)(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue);
HRESULT	(STDMETHODCALLTYPE MT_GetTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
HRESULT	(STDMETHODCALLTYPE MT_GetVertexDeclaration)(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9** ppDecl);
HRESULT	(STDMETHODCALLTYPE MT_GetVertexShader)(IDirect3DDevice9* pThis, IDirect3DVertexShader9** ppShader);
HRESULT	(STDMETHODCALLTYPE MT_GetVertexShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
HRESULT	(STDMETHODCALLTYPE MT_GetVertexShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,float* pConstantData,UINT Vector4fCount);
HRESULT	(STDMETHODCALLTYPE MT_GetVertexShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,int* pConstantData,UINT Vector4iCount);
HRESULT	(STDMETHODCALLTYPE MT_GetViewport)(IDirect3DDevice9* pThis, D3DVIEWPORT9* pViewport);
HRESULT	(STDMETHODCALLTYPE MT_LightEnable)(IDirect3DDevice9* pThis, DWORD Index,BOOL Enable);
HRESULT	(STDMETHODCALLTYPE MT_MultiplyTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
HRESULT	(STDMETHODCALLTYPE MT_Present)(IDirect3DDevice9* pThis, CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
HRESULT	(STDMETHODCALLTYPE MT_ProcessVertices)(IDirect3DDevice9* pThis, UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags);
HRESULT	(STDMETHODCALLTYPE MT_Reset)(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters);
HRESULT	(STDMETHODCALLTYPE MT_SetClipPlane)(IDirect3DDevice9* pThis, DWORD Index,CONST float* pPlane);
HRESULT	(STDMETHODCALLTYPE MT_SetClipStatus)(IDirect3DDevice9* pThis, CONST D3DCLIPSTATUS9* pClipStatus);
HRESULT	(STDMETHODCALLTYPE MT_SetCurrentTexturePalette)(IDirect3DDevice9* pThis, UINT PaletteNumber);
HRESULT	(STDMETHODCALLTYPE MT_SetCursorProperties)(IDirect3DDevice9* pThis, UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap);
void	(STDMETHODCALLTYPE MT_SetCursorPosition)(IDirect3DDevice9* pThis, int X,int Y,DWORD Flags);
HRESULT	(STDMETHODCALLTYPE MT_SetDepthStencilSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9* pNewZStencil);
HRESULT	(STDMETHODCALLTYPE MT_SetDialogBoxMode)(IDirect3DDevice9* pThis, BOOL bEnableDialogs);
HRESULT	(STDMETHODCALLTYPE MT_SetFVF)(IDirect3DDevice9* pThis, DWORD FVF);
void	(STDMETHODCALLTYPE MT_SetGammaRamp)(IDirect3DDevice9* pThis, UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp);
HRESULT	(STDMETHODCALLTYPE MT_SetIndices)(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9* pIndexData);
HRESULT	(STDMETHODCALLTYPE MT_SetLight)(IDirect3DDevice9* pThis, DWORD Index,CONST D3DLIGHT9*);
HRESULT	(STDMETHODCALLTYPE MT_SetMaterial)(IDirect3DDevice9* pThis, CONST D3DMATERIAL9* pMaterial);
HRESULT	(STDMETHODCALLTYPE MT_SetNPatchMode)(IDirect3DDevice9* pThis, float nSegments);
HRESULT	(STDMETHODCALLTYPE MT_SetPaletteEntries)(IDirect3DDevice9* pThis, UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
HRESULT	(STDMETHODCALLTYPE MT_SetPixelShader)(IDirect3DDevice9* pThis, IDirect3DPixelShader9* pShader);
HRESULT	(STDMETHODCALLTYPE MT_SetPixelShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
HRESULT	(STDMETHODCALLTYPE MT_SetPixelShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
HRESULT	(STDMETHODCALLTYPE MT_SetPixelShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
HRESULT	(STDMETHODCALLTYPE MT_SetRenderState)(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State,DWORD Value);
HRESULT	(STDMETHODCALLTYPE MT_SetRenderTarget)(IDirect3DDevice9* pThis, DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget);
HRESULT	(STDMETHODCALLTYPE MT_SetSamplerState)(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
HRESULT	(STDMETHODCALLTYPE MT_SetScissorRect)(IDirect3DDevice9* pThis, CONST RECT* pRect);
HRESULT	(STDMETHODCALLTYPE MT_SetSoftwareVertexProcessing)(IDirect3DDevice9* pThis, BOOL bSoftware);
HRESULT	(STDMETHODCALLTYPE MT_SetStreamSource)(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
HRESULT	(STDMETHODCALLTYPE MT_SetStreamSourceFreq)(IDirect3DDevice9* pThis, UINT StreamNumber,UINT Setting);
HRESULT	(STDMETHODCALLTYPE MT_SetTexture)(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9* pTexture);
HRESULT	(STDMETHODCALLTYPE MT_SetTextureStageState)(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value);
HRESULT	(STDMETHODCALLTYPE MT_SetTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
HRESULT	(STDMETHODCALLTYPE MT_SetVertexDeclaration)(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9* pDecl);
HRESULT	(STDMETHODCALLTYPE MT_SetVertexShader)(IDirect3DDevice9* pThis, IDirect3DVertexShader9* pShader);
HRESULT	(STDMETHODCALLTYPE MT_SetVertexShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
HRESULT	(STDMETHODCALLTYPE MT_SetVertexShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
HRESULT	(STDMETHODCALLTYPE MT_SetVertexShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
HRESULT	(STDMETHODCALLTYPE MT_SetViewport)(IDirect3DDevice9* pThis, CONST D3DVIEWPORT9* pViewport);
BOOL	(STDMETHODCALLTYPE MT_ShowCursor)(IDirect3DDevice9* pThis, BOOL bShow);
HRESULT	(STDMETHODCALLTYPE MT_StretchRect)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);
HRESULT	(STDMETHODCALLTYPE MT_TestCooperativeLevel)(IDirect3DDevice9* pThis);
HRESULT	(STDMETHODCALLTYPE MT_UpdateSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint);
HRESULT	(STDMETHODCALLTYPE MT_UpdateTexture)(IDirect3DDevice9* pThis, IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture);
HRESULT	(STDMETHODCALLTYPE MT_ValidateDevice)(IDirect3DDevice9* pThis, DWORD* pNumPasses);

// IDirect3DSwapChain9
HRESULT	STDMETHODCALLTYPE MT_SwapChain_Present(IDirect3DSwapChain9*	pSwapChain,CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags);

// IDirect3DSurface9
//HRESULT	STDMETHODCALLTYPE MT_Surface_LockRect(IDirect3DSurface9* pSurface, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
//HRESULT	STDMETHODCALLTYPE MT_Surface_UnlockRect(IDirect3DSurface9* pSurface);
ULONG	STDMETHODCALLTYPE MT_Surface_Release(IDirect3DSurface9* pThis);

HRESULT	STDMETHODCALLTYPE MT_CubeSurface_LockRect(IDirect3DSurface9* pSurface, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_CubeSurface_UnlockRect(IDirect3DSurface9* pSurface);
//ULONG	STDMETHODCALLTYPE MT_CubeSurface_Release(IDirect3DSurface9* pThis);

// IDirect3DBaseTexture9
HRESULT	STDMETHODCALLTYPE MT_BaseTexture_SetAutoGenFilterType(IDirect3DBaseTexture9*	pTex,D3DTEXTUREFILTERTYPE FilterType);
HRESULT	STDMETHODCALLTYPE MT_BaseTexture_GenerateMipSubLevels(IDirect3DBaseTexture9*	pTex);

// IDirect3DTexture9
HRESULT	STDMETHODCALLTYPE MT_Texture_LockRect(IDirect3DTexture9*	pTex,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_Texture_UnlockRect(IDirect3DTexture9*	pTex,UINT Level);
HRESULT	STDMETHODCALLTYPE MT_Texture_AddDirtyRect(IDirect3DTexture9*	pTex,CONST RECT* pDirtyRect);

// IDirect3DCubeTexture9
HRESULT	STDMETHODCALLTYPE MT_CubeTexture_LockRect(IDirect3DCubeTexture9*	pTex,D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_CubeTexture_UnlockRect(IDirect3DCubeTexture9*	pTex,D3DCUBEMAP_FACES FaceType,UINT Level);
HRESULT	STDMETHODCALLTYPE MT_CubeTexture_AddDirtyRect(IDirect3DCubeTexture9*	pTex,D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect);

// IDirect3DVolumeTexture9
HRESULT	STDMETHODCALLTYPE MT_VolumeTexture_LockBox(IDirect3DVolumeTexture9*	pVolumeTex, UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_VolumeTexture_UnlockBox(IDirect3DVolumeTexture9*	pVolumeTex, UINT Level);
HRESULT	STDMETHODCALLTYPE MT_VolumeTexture_AddDirtyBox(IDirect3DVolumeTexture9*	pVolumeTex, CONST D3DBOX* pDirtyBox);

// IDirect3DVolume9
HRESULT STDMETHODCALLTYPE MT_Volume_LockBox(IDirect3DVolume9*	pVolume,D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
HRESULT STDMETHODCALLTYPE MT_Volume_UnlockBox(IDirect3DVolume9*	pVolume);
ULONG	STDMETHODCALLTYPE MT_Volume_Release(IDirect3DVolume9* pThis);

// IDirect3DVertexBuffer
HRESULT	STDMETHODCALLTYPE MT_VertexBuffer_Lock(IDirect3DVertexBuffer9*	pVB,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_VertexBuffer_Unlock(IDirect3DVertexBuffer9* pVB);
ULONG	STDMETHODCALLTYPE MT_VertexBuffer_Release(IDirect3DVertexBuffer9* pThis);

// IDirect3DIndexBuffer
HRESULT	STDMETHODCALLTYPE MT_IndexBuffer_Lock(IDirect3DIndexBuffer9*	pIB,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
HRESULT	STDMETHODCALLTYPE MT_IndexBuffer_Unlock(IDirect3DIndexBuffer9*	pIB);
ULONG	STDMETHODCALLTYPE MT_IndexBuffer_Release(IDirect3DIndexBuffer9* pThis);

// IDirect3DVertexDeclaration
ULONG	STDMETHODCALLTYPE MT_VertexDeclaration_Release(IDirect3DVertexDeclaration9* pThis);

// IDirect3DStateBlock9
HRESULT	STDMETHODCALLTYPE MT_StateBlock_Apply(IDirect3DStateBlock9* pStateBlock);
HRESULT	STDMETHODCALLTYPE MT_StateBlock_Capture(IDirect3DStateBlock9* pStateBlock);
//ULONG	STDMETHODCALLTYPE MT_StateBlock_Release(IDirect3DStateBlock9* pThis);

// ID3DXBaseEffect
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetValue(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetBool(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, BOOL b);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetBoolArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetInt(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, INT n);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetIntArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetFloat(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, FLOAT f);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetFloatArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetVector(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetVectorArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrix(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrixArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrixPointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrixTranspose(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrixTransposeArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetMatrixTransposePointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetString(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCSTR pString);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetTexture(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
//
// ID3DXEffect
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetTechnique(ID3DXEffect* pID3DXEffect, THIS_ D3DXHANDLE hTechnique);
//HRESULT	STDMETHODCALLTYPE MT_Effect_Begin(ID3DXEffect* pID3DXEffect, THIS_ UINT *pPasses, DWORD Flags) ;
//HRESULT	STDMETHODCALLTYPE MT_Effect_BeginPass(ID3DXEffect* pID3DXEffect, THIS_ UINT Pass) ;
//HRESULT	STDMETHODCALLTYPE MT_Effect_CommitChanges(ID3DXEffect* pID3DXEffect) ;
//HRESULT	STDMETHODCALLTYPE MT_Effect_EndPass(ID3DXEffect* pID3DXEffect) ;
//HRESULT	STDMETHODCALLTYPE MT_Effect_End(ID3DXEffect* pID3DXEffect) ;
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetStateManager(ID3DXEffect* pID3DXEffect, THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
//HRESULT	STDMETHODCALLTYPE MT_Effect_SetRawValue(ID3DXEffect* pID3DXEffect, THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);

// PIX
//int		WINAPI MT_PIX_D3DPERF_BeginEvent(D3DCOLOR col,LPCWSTR wszName);
//int		WINAPI MT_PIX_D3DPERF_EndEvent();
//void		WINAPI MT_PIX_D3DPERF_SetMarker(D3DCOLOR col,LPCWSTR wszName);

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void ReleaseAllResource();

#endif // RENDERDEVICE_HEAD_FILE