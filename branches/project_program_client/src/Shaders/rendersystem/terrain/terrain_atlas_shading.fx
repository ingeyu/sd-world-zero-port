//*************************************************************************************************
// ����:	������ɫ
//---------------------------------------------------------
// ����:		
// ����:		2012-08-08
// ����޸�:
//*************************************************************************************************
#include "terrain_common.h"

//---------------------------------------------------------------------------------------
// ��������������
//---------------------------------------------------------------------------------------
SD_POINT_CLAMP_CUBESAMPLE(0, sdPlanarTableSampler, 	sdPlanarTableTex);				//
SD_POINT_CLAMP_SAMPLE(1, sdGeomSampler, 			sdGeomBuf, 			false);		// ��Ļ����뷨�߻���
SD_POINT_CLAMP_SAMPLE(2, sdLightSampler, 			sdLightBuf, 		false);		// ��Ļ�ֲ����ջ���
SD_LINEAR_WRAP_SAMPLE(3, sdBaseNormalSampler, 		sdBaseNormalTex, 	false);		// ���λ���������ͼ
SD_POINT_CLAMP_SAMPLE(4, sdTileSampler,				sdTileTex,			false);		// ����TileMap
SD_LINEAR_WRAP_SAMPLE(5, sdBlendSampler,			sdBlendTex,			false);		// ����BlendMap
SD_POINT_CLAMP_SAMPLE(6, sdAtlasTableSampler,		sdAtlasTableTex,	false);		// ������������ͼ��ѯ��
SD_LINEAR_WRAP_SAMPLE(7, sdDiffuseAtlasSampler,		sdDiffuseAtlasTex,	false);		// ������������ͼͼ��

//---------------------------------------------------------------------------------------
// ������ɫ������������
//---------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3	vPos			: POSITION0;	// ��Ļ���ζ�������
	float2	vUVSet0			: TEXCOORD0;	// ��Ļ���ζ�����������
};

//---------------------------------------------------------------------------------------
// ������ɫ�����������
//---------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	vProjPos			: POSITION;		// ͶӰ����
	float2	vUVSetScreenTex		: TEXCOORD0;	// ����������ƫ�Ƶ���Ļ��������
	float3	vUVFarClipWorldPos	: TEXCOORD1;	// ��ǰ���ӦԶ�ü����ϵĵ����������
	float3	vUVFarClipViewPos	: TEXCOORD2;	// ��ǰ���ӦԶ�ü����ϵĵ�Ĺ۲�����
};

//---------------------------------------------------------------------------------------
// ������ɫ��
//---------------------------------------------------------------------------------------
VS_OUTPUT VS_Main(VS_INPUT kInput)
{
	VS_OUTPUT kOutput;

	// ת����ͶӰ����
	kOutput.vProjPos = float4(kInput.vPos, 1.f);
	
	// ����������ƫ�Ƶ���Ļ��������
	kOutput.vUVSetScreenTex = kInput.vUVSet0 + g_vHalfPixelOffset;
	
	// ��ǰ���ӦԶ�ü����ϵĵ����������
	float4 vUVFarClipProjPos  = float4(kInput.vPos.xy, 1.f, 1.f);
	float4 vUVFarClipWorldPos = mul(vUVFarClipProjPos, g_mDepthToWorld);
	kOutput.vUVFarClipWorldPos = vUVFarClipWorldPos.xyz;
	
	// ��ǰ���ӦԶ�ü����ϵĵ�Ĺ۲�����
	// (�滻��w������Ϊ�˱����������ۻ�?)
	kOutput.vUVFarClipViewPos  = mul(float4(vUVFarClipWorldPos.xyz, 1.f), g_mView).xyz;
	
	return kOutput;
}

//---------------------------------------------------------------------------------------
// ������ɫ��
//---------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------
float4 PS_Main_Simple(VS_OUTPUT kInput) : COLOR0
{
	// ��ȡ�������
	float4 vGeoTex = tex2D(sdGeomSampler, kInput.vUVSetScreenTex);
	float fDepth = UnpackDepth(vGeoTex.xy);
	
	// ������������(�����������,�����λ�ú�Զƽ���Ӧ��λ�ý��в�ֵ)
	float3 vWorldPos = lerp(g_vViewPos, kInput.vUVFarClipWorldPos, fDepth);
	
	// ���㵱ǰ��ĵ������UV(ע��,����û��ƫ�ư�����)
	float2 vUVSet = vWorldPos.xy * g_vRecipTerrainSize;
	
	
	// NormalMap
	// @{
	// ����UV����NormalMap
	float4 vBaseNormalTex 	= tex2D(sdBaseNormalSampler, vUVSet);
	
	// �����б���,����һ���ǶȵĲ�������ɫ
	float3 vPlanarWeight;
	vPlanarWeight.xy 	= vBaseNormalTex.zw;
	vPlanarWeight.z 	= saturate(1.0 - vPlanarWeight.x - vPlanarWeight.y);

	clip(1.5 - dot(sign(vPlanarWeight), 1));
	
	// �������ռ䷨��
	float3 vWorldNormal;
	vWorldNormal.xy	= vBaseNormalTex.xy * 2.0 - 1.0;
	vWorldNormal.z 	= sqrt(dot(float3(1.0, vWorldNormal.xy), float3(1.0, -vWorldNormal.xy)));
	// @}
	
	
	// TileMap
	// @{
	// ����UV����TileMap(�����[0,1]�ָ���[0,255]��ͼ����������)
	float3 vIndices = tex2D(sdTileSampler, vUVSet).xyz * 255.f;
	// @} 
	
	
	// BlendMap
	// @{
	// �����µ�UV(����,�����Ϊ����Tile��Ե�����ں�)
	float2 tileCenterOffset = frac(vUVSet * g_fTileMapSize) - 0.5f;
	float2 vUVSet2 = vUVSet - tileCenterOffset * g_fRecipBlendMapSize;
	
	// ����UV����BlendMap
	float4 vBlendTex = tex2D(sdBlendSampler, vUVSet2);
	
	// ��һ��Ȩ��
	float fTotalWeight = dot(vBlendTex.xyz, 1.f);
	vBlendTex.rgb /= fTotalWeight;
	
#ifdef _SD_EDITOR
	vBlendTex.a = max(vBlendTex.a, g_fLightMapMask);
#endif
	// @}
	
	
	// ��ͼ���
	// @{
	// ��������������,�����µĵ���UV(GB����ϵ��D3D����ϵYZ�ụ��)
	float2 vUVSet3 = float2(vWorldPos.x, -vWorldPos.y);
	//float4 vPlanarVec = texCUBE(sdPlanarTableSampler, vWorldNormal.xzy) * 255 - 1; 
	//float2 vUVSet3 = float2(dot(vWorldPos.xy, vPlanarVec.xy), dot(vWorldPos.yz, vPlanarVec.zw));

	// ���㵱ǰ���ص��۲���ʸ��
	float3 vWorldViewVector = normalize(g_vViewPos - kInput.vUVFarClipWorldPos);
	
	// ���㵱ǰ����ӦȡLOD(�ȼ�����ǵ�ǰPixel��Ӧ������ռ�Pixel�ĳߴ�,Ȼ���2ȡ�����õ�LOD)
	//	g_vFarPixelSize				�����ڴ�ֱԶƽ���ϵĶ�Ӧ�ߴ�(���Ƴߴ�,��ʵԶƽ����һ���������һ����)
	//	g_vFarPixelSize * fDepth	�����ڵ�ǰ�����µĴ�ֱƽ���ϵĶ�Ӧ�ߴ�
	//	dot(vWorldViewVector, vWorldNormal)	��ǰ�������ͶӰ��λ�ĽǶ�,����ͶӰ����ļн�����ֵ
	float2 vLodLevel = log2(g_vFarPixelSize * fDepth / max(dot(vWorldViewVector, vWorldNormal), 0.25));
	
	// ����ͼ��UV
	//	.xyz �ֱ���3��Layer��id����õ�������U���� 	LayerId * (1.0f / uiWidth) + (0.5f / uiWidth)
	//	.w	 �����ص�lod��Ϣ����õ�������V����	 	PixelLod * (1.0f / uiHeight) + (-iMinLodFactor / (float)uiHeight)
	float4 vUVSetTable;
	vUVSetTable.xyz = saturate(vIndices.bgr * g_fDiffuseAtlasIdScale + g_fDiffuseAtlasIdOffset);
	vUVSetTable.w	= saturate(max(vLodLevel.x, vLodLevel.y) * g_fDiffuseAtlasLevelScale + g_fDiffuseAtlasLevelOffset);
	
	// ��ͼ���
	float4 vDiffuseGloss = SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.xw, vUVSet3) * vBlendTex.b +
		SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.yw, vUVSet3) * vBlendTex.g +
		SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.zw, vUVSet3) * vBlendTex.r;
	
#ifdef _SD_EDITOR
	vDiffuseGloss = max(vDiffuseGloss, float4(g_vDiffuseMapMask, g_fGlossMapMask));
#endif
	// @}


	// ����������ɫ
	// @{
	// ����LightBuffer
	float4 vLightTex = tex2D(sdLightSampler, kInput.vUVSetScreenTex);
	
	// ����۲췽���뷨��
	float3 vViewVector = -normalize(kInput.vUVFarClipViewPos);
	float3 vViewNormal 	= UnpackNormal(vGeoTex.zw);
	
	// �ϳɹ���
	float3 vDiffuseLight;
	AccumLightingOnlyDiffuse(vViewNormal, g_fTerrainUseLightMap > 0.f ? vBlendTex.z : 1.f, vLightTex, vDiffuseLight);

	// �ϳ�������ɫ
	float3 vColor = vDiffuseLight  * vDiffuseGloss.rgb * g_vTerrainDiffuseMaterial;
	// @}
	
#ifdef _SD_EDITOR
	vColor = lerp(vColor, float3(1.f, 0.f, 0.f), saturate(1.f - fTotalWeight) * g_fTerrainShowInvisibleLayers);
	vColor = lerp(vColor, float3(0.f, 1.f, 1.f), any(saturate(abs(tileCenterOffset) - 0.49f)) * g_fTerrainShowTileGrid);
#endif

	return float4(vColor, 0);
};
//---------------------------------------------------------------------------------------
// ƽ̹������ɫ
float4 PS_Main_Planar(VS_OUTPUT kInput) : COLOR0
{
	// ��ȡ�������
	float4 vGeoTex = tex2D(sdGeomSampler, kInput.vUVSetScreenTex);
	float fDepth = UnpackDepth(vGeoTex.xy);
	
	// ������������(�����������,�����λ�ú�Զƽ���Ӧ��λ�ý��в�ֵ)
	float3 vWorldPos = lerp(g_vViewPos, kInput.vUVFarClipWorldPos, fDepth);
	
	// ���㵱ǰ��ĵ������UV(ע��,����û��ƫ�ư�����)
	float2 vUVSet = vWorldPos.xy * g_vRecipTerrainSize;
	
	
	// NormalMap
	// @{
	// ����UV����NormalMap
	float4 vBaseNormalTex 	= tex2D(sdBaseNormalSampler, vUVSet);
	
	// �����б���,����һ���ǶȵĲ�������ɫ
	float3 vPlanarWeight;
	vPlanarWeight.xy 	= vBaseNormalTex.zw;
	vPlanarWeight.z 	= saturate(1.0 - vPlanarWeight.x - vPlanarWeight.y);

	clip(1.5 - dot(sign(vPlanarWeight), 1));
	
	// �������ռ䷨��
	float3 vWorldNormal;
	vWorldNormal.xy	= vBaseNormalTex.xy * 2.0 - 1.0;
	vWorldNormal.z 	= sqrt(dot(float3(1.0, vWorldNormal.xy), float3(1.0, -vWorldNormal.xy)));
	// @}
	
	
	// TileMap
	// @{
	// ����UV����TileMap(�����[0,1]�ָ���[0,255]��ͼ����������)
	float3 vIndices = tex2D(sdTileSampler, vUVSet).xyz * 255.0;
	// @} 
	
	
	// BlendMap
	// @{
	// �����µ�UV(����,�����Ϊ����Tile��Ե�����ں�)
	float2 tileCenterOffset = frac(vUVSet * g_fTileMapSize) - 0.5;
	float2 vUVSet2 = vUVSet - tileCenterOffset * g_fRecipBlendMapSize;
	
	// ����UV����BlendMap
	float4 vBlendTex = tex2D(sdBlendSampler, vUVSet2);
	
	// ��һ��Ȩ��
	float fTotalWeight = dot(vBlendTex.xyz, 1.0);
	vBlendTex.rgb /= fTotalWeight;
	
#ifdef _SD_EDITOR
	vBlendTex.a = max(vBlendTex.a, g_fLightMapMask);
#endif
	// @}
	
	
	// ��ͼ���
	// @{
	// ��������������,�����µĵ���UV(GB����ϵ��D3D����ϵYZ�ụ��)
	//float2 vUVSet3 = float2(vWorldPos.x, -vWorldPos.y);
	float4 vPlanarVec = texCUBE(sdPlanarTableSampler, vWorldNormal.xzy) * 255 - 1; 
	float2 vUVSet3 = float2(dot(vWorldPos.xy, vPlanarVec.xy), dot(vWorldPos.yz, vPlanarVec.zw));

	// ���㵱ǰ���ص��۲���ʸ��
	float3 vWorldViewVector = normalize(g_vViewPos - kInput.vUVFarClipWorldPos);
	
	// ���㵱ǰ����ӦȡLOD(�ȼ�����ǵ�ǰPixel��Ӧ������ռ�Pixel�ĳߴ�,Ȼ���2ȡ�����õ�LOD)
	//	g_vFarPixelSize				�����ڴ�ֱԶƽ���ϵĶ�Ӧ�ߴ�(���Ƴߴ�,��ʵԶƽ����һ���������һ����)
	//	g_vFarPixelSize * fDepth	�����ڵ�ǰ�����µĴ�ֱƽ���ϵĶ�Ӧ�ߴ�
	//	dot(vWorldViewVector, vWorldNormal)	��ǰ�������ͶӰ��λ�ĽǶ�,����ͶӰ����ļн�����ֵ
	float2 vLodLevel = log2(g_vFarPixelSize * fDepth / max(dot(vWorldViewVector, vWorldNormal), 0.25));
	
	// ����ͼ��UV
	//	.xyz �ֱ���3��Layer��id����õ�������U���� 	LayerId * (1.0f / uiWidth) + (0.5f / uiWidth)
	//	.w	 �����ص�lod��Ϣ����õ�������V����	 	PixelLod * (1.0f / uiHeight) + (-iMinLodFactor / (float)uiHeight)
	float4 vUVSetTable;
	vUVSetTable.xyz = saturate(vIndices.bgr * g_fDiffuseAtlasIdScale + g_fDiffuseAtlasIdOffset);
	vUVSetTable.w	= saturate(max(vLodLevel.x, vLodLevel.y) * g_fDiffuseAtlasLevelScale + g_fDiffuseAtlasLevelOffset);
	
	// ��ͼ���
	float4 vDiffuseGloss = SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.xw, vUVSet3) * vBlendTex.b +
		SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.yw, vUVSet3) * vBlendTex.g +
		SamplerAtlasMap(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.zw, vUVSet3) * vBlendTex.r;
	
#ifdef _SD_EDITOR
	vDiffuseGloss = max(vDiffuseGloss, float4(g_vDiffuseMapMask, g_fGlossMapMask));
#endif
	// @}


	// ����������ɫ
	// @{
	// ����LightBuffer
	float4 vLightTex = tex2D(sdLightSampler, kInput.vUVSetScreenTex);
	
	// ����۲췽���뷨��
	float3 vViewVector = -normalize(kInput.vUVFarClipViewPos);
	float3 vViewNormal 	= UnpackNormal(vGeoTex.zw);
	
	// �ϳɹ���
	float3 vDiffuseLight;
	float3 vSpeculatLight;
	AccumLighting(vViewVector, vViewNormal, g_fTerrainShiness, vBlendTex.a, vLightTex, vDiffuseLight, vSpeculatLight);

	// �ϳ�������ɫ
	float3 vColor = vDiffuseLight  * vDiffuseGloss.rgb * g_vTerrainDiffuseMaterial +
					vSpeculatLight * vDiffuseGloss.a   * g_vTerrainSpecularMaterial;	
	// @}
	
#ifdef _SD_EDITOR
	vColor = lerp(vColor, float3(1.f, 0.f, 0.f), saturate(1.f - fTotalWeight) * g_fTerrainShowInvisibleLayers);
	vColor = lerp(vColor, float3(0.f, 1.f, 1.f), any(saturate(abs(tileCenterOffset) - 0.49f)) * g_fTerrainShowTileGrid);
#endif

	return float4(vColor, 0);

	//*************************
	//return float4(vDiffuseLight.rgb, 0);
	
	//
	//return float4(vGeoTex.zw, 0, 0);
	
	// ����ƽ̹�붸�͵����ķָ�
	//return float4(0.5,0.5,0.5,0);
	
	// ������Ļ��������
	//return float4(kInput.vUVSetScreenTex, 0, 0);
	
	// ���Ե�����������
	//return float4(vUVSet.xy, 0, 0);
	
	// ���Ե����������
	//return float4(fDepth,fDepth,fDepth,0);
	
	// ���Է���
	//return float4(vBaseNormalTex.xy,1,0);
	//return float4((vWorldNormal + 1) * 0.5,0);
	//return float4((vViewNormal + 1) * 0.5,0);
	
	//if (vWorldNormal.z > 0.99)
	//return float4(1,0,0,0);
	//else
	//return float4(0,1,0,0);
	
	// ���Թ���1
	//float NL = dot(vWorldNormal, -g_vMainLightDir);
	//float NL = dot(mul(vWorldNormal, g_mView), -mul(g_vMainLightDir, g_mView));
	//float NL = dot(mul(vWorldNormal, g_mView), -g_vMainLightDir);
	//float NL = dot(mul(vViewNormal, g_mView), -g_vMainLightDir);
	//float NL = dot(vViewNormal, -g_vMainLightDir);
	//float NL = dot(mul(float3(0,0,1), g_mView), -g_vMainLightDir);
	//return float4(NL, NL, NL,0);

	// ���Թ���2
	//float3 vDiffuseLightTemp;
	//float3 vSpeculatLightTemp;
	//AccumLighting(vViewVector, vViewNormal, 0, 1, float4(0,0,0,0), vDiffuseLightTemp, vSpeculatLightTemp);
	//return float4(vDiffuseLightTemp.xyz, 0);
	
	// ����LODѡȡ���
	//if (vLodLevel.x > -1.f)
	//	return float4(0,0,0,0);
	//else if (vLodLevel.x > -2.f)
	//	return float4(0.5,0.5,0.5,0);
	//else if (vLodLevel.x > -4.f)
	//	return float4(0,0,1,0);	
	//else if (vLodLevel.x > -6.f)
	//	return float4(0,1,0,0);	
	//else if (vLodLevel.x > -8.f)
	//	return float4(1,0,0,0);	
	//else
	//	return float4(1,1,1,0);	
	
	// ���Դ�LOD��V����ת�����
	//if (vUVSetTable.w < 1.0 / 32.0)
	//	return float4(1,1,1,0);
	//else if (vUVSetTable.w < 2.0 / 32.0)
	//	return float4(1,0,0,0);
	//else if (vUVSetTable.w < 3.0 / 32.0)
	//	return float4(0,1,0,0);	
	//else if (vUVSetTable.w < 4.0 / 32.0)
	//	return float4(0,0,1,0);	
	//else if (vUVSetTable.w < 5.0 / 32.0)
	//	return float4(0.7,0.7,0.7,0);	
	//else if (vUVSetTable.w < 6.0 / 32.0)
	//	return float4(0.4,0.4,0.4,0);	
	//else
	//	return float4(0,0,0,0);	
	//*************************
};
//---------------------------------------------------------------------------------------
// ���͵�����ɫ
float4 PS_Main_Seam(VS_OUTPUT kInput) : COLOR0
{
	// ��ȡ�������
	float4 vGeoTex = tex2D(sdGeomSampler, kInput.vUVSetScreenTex);
	float fDepth = UnpackDepth(vGeoTex.xy);
	
	// ������������
	// (�����������,�����λ�ú�Զƽ���Ӧ��λ�ý��в�ֵ)
	float3 vWorldPos = lerp(g_vViewPos, kInput.vUVFarClipWorldPos, fDepth);
	
	// ���㵱ǰ��ĵ������UV(ע��,����û��ƫ�ư�����)
	float2 vUVSet = vWorldPos.xy * g_vRecipTerrainSize;
	
	
	// NormalMap
	// @{
	// ����UV����NormalMap
	float4 vBaseNormalTex 	= tex2D(sdBaseNormalSampler, vUVSet);
	
	// �����б���,С��һ���ǶȵĲ�������ɫ
	float3 vPlanarWeight;
	vPlanarWeight.xy 	= vBaseNormalTex.zw;
	vPlanarWeight.z 	= saturate(1.0 - vPlanarWeight.x - vPlanarWeight.y);

	clip(dot(sign(vPlanarWeight), 1) - 1.5);
	
	// �������ռ䷨��(x,y,z)
	float3 vWorldNormal;
	vWorldNormal.xy	= vBaseNormalTex.xy * 2.0 - 1.0;
	vWorldNormal.z 	= sqrt(dot(float3(1.0, vWorldNormal.xy), float3(1.0, -vWorldNormal.xy)));
	// @}
	
	
	// TileMap
	// @{
	// ����UV����TileMap,
	float3 vIndices = tex2D(sdTileSampler, vUVSet).xyz * 255.0;
	// @} 
	
	
	// BlendMap
	// @{
	// �����µ�UV(����,�����Ϊ����Tile��Ե�����ں�)
	float2 tileCenterOffset = frac(vUVSet * g_fTileMapSize) - 0.5;
	float2 vUVSet2 = vUVSet - tileCenterOffset * g_fRecipBlendMapSize;
	
	// ����UV����BlendMap
	float4 vBlendTex = tex2D(sdBlendSampler, vUVSet2);
	
	// ��һ��Ȩ��
	float fTotalWeight = dot(vBlendTex.xyz, 1.0);
	vBlendTex.rgb /= fTotalWeight;
	
#ifdef _SD_EDITOR
	vBlendTex.a = max(vBlendTex.a, g_fLightMapMask);
#endif
	// @}
	
	
	// ��ͼ���
	// @{
	// 
	//float4 vPlanarVec = texCUBE(sdPlanarTableSampler, vWorldNormal.xzy) * 255 - 1;
	float2 vTerrainUV_XY = float2(vWorldPos.x, -vWorldPos.y);
	float2 vTerrainUV_YZ = float2(vWorldPos.y * sign(vWorldNormal.x - 0.5f), -vWorldPos.z);
	float2 vTerrainUV_XZ = float2(-vWorldPos.x * sign(vWorldNormal.y - 0.5f), -vWorldPos.z);
	
	// ���㵱ǰ���ص��۲��ʸ��
	float3 vWorldViewVector = normalize(g_vViewPos - kInput.vUVFarClipWorldPos);
	
	// ���㵱ǰ����ӦȡLOD(���ﲻ��,�д���һ����ע)
	float2 vLodLevel = log2(g_vFarPixelSize * fDepth / max(dot(vWorldViewVector, vWorldNormal), 0.25));
	
	// ����ͼ��UV
	float4 vUVSetTable;
	vUVSetTable.xyz = saturate(vIndices.bgr * g_fDiffuseAtlasIdScale + g_fDiffuseAtlasIdOffset);
	vUVSetTable.w	= saturate(max(vLodLevel.x, vLodLevel.y) * g_fDiffuseAtlasLevelScale + g_fDiffuseAtlasLevelOffset);
	
	// ��ͼ���
	float4 vDiffuseGloss = SamplerAtlasMap_Planar(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.xw, vTerrainUV_XY, vTerrainUV_YZ, vTerrainUV_XZ, vPlanarWeight) * vBlendTex.b +
		SamplerAtlasMap_Planar(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.yw, vTerrainUV_XY, vTerrainUV_YZ, vTerrainUV_XZ, vPlanarWeight) * vBlendTex.g +
		SamplerAtlasMap_Planar(sdDiffuseAtlasSampler, sdAtlasTableSampler, vUVSetTable.zw, vTerrainUV_XY, vTerrainUV_YZ, vTerrainUV_XZ, vPlanarWeight) * vBlendTex.r;
	
#ifdef _SD_EDITOR
	vDiffuseGloss = max(vDiffuse_Gloss, float4(g_vDiffuseMapMask,g_fGlossMapMask));
#endif
	// @}
	
	
	// ����������ɫ
	// @{
	// ����LightBuffer
	float4 vLightTex = tex2D(sdLightSampler, kInput.vUVSetScreenTex);
	
	// ����۲췽���뷨��
	float3 vViewVector = -normalize(kInput.vUVFarClipViewPos);
	float3 vViewNormal 	= UnpackNormal(vGeoTex.zw);
	
	// �ϳɹ���
	float3 vDiffuseLight;
	float3 vSpeculatLight;
	AccumLighting(vViewVector, vViewNormal, g_fTerrainShiness, vBlendTex.a, vLightTex, vDiffuseLight, vSpeculatLight);
	
	// �ϳ�������ɫ
	float3 vColor = vDiffuseLight  * vDiffuseGloss.rgb * g_vTerrainDiffuseMaterial +
					vSpeculatLight * vDiffuseGloss.a   * g_vTerrainSpecularMaterial;	
	// @}
	
#ifdef _SD_EDITOR
	vColor = lerp(vColor, float3(1.f, 0.f, 0.f), saturate(1.f - fTotalWeight) * g_fTerrainShowInvisibleLayers);
	vColor = lerp(vColor, float3(0.f, 1.f, 1.f), any(saturate(abs(tileCenterOffset) - 0.49f)) * g_fTerrainShowTileGrid);
#endif
	
	return float4(vColor, 0);
	
	//*************************
	// ����ƽ̹�붸�͵����ķָ�
	//return float4(0.5,0.5,0.5,0);
	
		// ���Է���
	//return float4(vBaseNormalTex.xy,1,0);
	//return float4((vWorldNormal + 1) * 0.5,0);
	//return float4((vViewNormal + 1) * 0.5,0);
	
	// ����LODѡȡ���
	//if (vLodLevel.x > -1.f)
	//	return float4(0,0,0,0);
	//else if (vLodLevel.x > -2.f)
	//	return float4(0.5,0.5,0.5,0);
	//else if (vLodLevel.x > -4.f)
	//	return float4(0,0,1,0);	
	//else if (vLodLevel.x > -6.f)
	//	return float4(0,1,0,0);	
	//else if (vLodLevel.x > -8.f)
	//	return float4(1,0,0,0);	
	//else
	//	return float4(1,1,1,0);	
	//*************************
}

//---------------------------------------------------------------------------------------
// ��ɫ����
//---------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------
technique Terrain_AtlasShading_Simple
<
	string Description = "Terrain_AtlasShading_Simple";
	bool UsesNiRenderState = false;
	bool UsesNiLightState = false;
>
{
	pass P0
	{
		VertexShader 	= compile vs_3_0 VS_Main ();
		PixelShader 	= compile ps_3_0 PS_Main_Simple ();
	}
}
//---------------------------------------------------------------------------------------
technique Terrain_AtlasShading_Planar
<
	string Description = "Terrain_AtlasShading_Planar";
	bool UsesNiRenderState = false;
	bool UsesNiLightState = false;
>
{
	pass P0
	{
		VertexShader 	= compile vs_3_0 VS_Main ();
		PixelShader 	= compile ps_3_0 PS_Main_Planar ();
	}
}
//---------------------------------------------------------------------------------------
technique Terrain_AtlasShading_Seam
<
	string Description = "Terrain_AtlasShading_Seam";
	bool UsesNiRenderState = false;
	bool UsesNiLightState = false;
>
{
	pass P0
	{
		VertexShader 	= compile vs_3_0 VS_Main ();
		PixelShader 	= compile ps_3_0 PS_Main_Seam ();
	}
}
//---------------------------------------------------------------------------------------



















