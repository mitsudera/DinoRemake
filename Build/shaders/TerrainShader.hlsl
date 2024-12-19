// �}�g���N�X�o�b�t�@
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewBuffer : register(b1)
{
    matrix View;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

// �}�e���A���o�b�t�@
struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    int noDiffuseTex;
    int noNormalTex;
    int noArmTex;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}


#define MAX_DIREC_LIGHT (4)
#define MAX_POINT_LIGHT (8)

// ���C�g�p�o�b�t�@
struct DIREC_LIGHT
{
    float4 m_Direction[MAX_DIREC_LIGHT]; // ���C�g�̕���
    float4 m_Diffuse[MAX_DIREC_LIGHT]; // �g�U���̐F
    float4 m_Ambient[MAX_DIREC_LIGHT]; // �����̐F
    int4 m_Enable[MAX_DIREC_LIGHT];
    int4 allEnable;

};


cbuffer DirecLightBuffer : register(b4)
{
    DIREC_LIGHT direcLight;
    
    
}
// ���C�g�p�萔�o�b�t�@�\����
struct POINT_LIGHT
{
    float4 m_Position[MAX_POINT_LIGHT]; // ���C�g�̈ʒu
    float4 m_Diffuse[MAX_POINT_LIGHT]; // �g�U���̐F
    float4 m_Ambient[MAX_POINT_LIGHT]; // �����̐F
    float4 m_Attenuation[MAX_POINT_LIGHT]; // ������    
    float4 m_intensity[MAX_POINT_LIGHT]; // ���C�g�̋��x
    int4 m_Enable[MAX_POINT_LIGHT];
    int4 allEnable;
};
cbuffer PointLightBuffer : register(b5)
{
    POINT_LIGHT pointLight;
    
    
}


cbuffer CameraBuffer : register(b6)
{
    float4 Camera;
}

struct SHADOW
{
    matrix wvp;
    int enable;
    int mode;
    float facter;
    int dummy;
};

cbuffer ShadowBuffer : register(b7)
{
    SHADOW Shadow;
}
cbuffer TessellationBuffer : register(b8)
{
    float tessellationFactor;
    float3 dummy;
};







//=============================================================================
// ���_�V�F�[�_
//=============================================================================
void VSmain(in float4 inPosition : POSITION0,
						  in float4 inNormal : NORMAL0,
						  in float4 inDiffuse : COLOR0,
						  in float2 inTexCoord : TEXCOORD0,
                          in float4 inTangent : TANGENT0,
                          in float4 inBiNoramal : BINORMAL0,

						  out float4 outPosition : SV_POSITION,
						  out float4 outNormal : NORMAL0,
						  out float2 outTexCoord : TEXCOORD0,
						  out float4 outDiffuse : COLOR0,
						  out float4 outWorldPos : POSITION0,
						  out float4 outPosSM : POSITION1,
						  out float4 outTangent : TANGENT0,
						  out float4 outBiNormal : BINORMAL0
)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    outPosition = mul(inPosition, wvp);

    outNormal = normalize(mul(float4(inNormal.xyz, 0.0f), World));
    outTangent = normalize(mul(float4(inTangent.xyz, 0.0f), World));
    outBiNormal = normalize(mul(float4(inBiNoramal.xyz, 0.0f), World));

    outTexCoord = inTexCoord;

    outWorldPos = mul(inPosition, World);

    outDiffuse = inDiffuse;
	
	
	 //���_���W�@���f�����W�n���������W�n(�V���h�E�}�b�v)
    matrix SMWorldViewProj = mul(World, Shadow.wvp);
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    float4 pos4 = mul(inPosition, SMWorldViewProj);
    pos4.xyz = pos4.xyz / pos4.w;
    outPosSM.x = (pos4.x + 1.0) / 2.0;
    outPosSM.y = (-pos4.y + 1.0) / 2.0;
    outPosSM.z = pos4.z;


}



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D DiffuseTexture : register(t0);
Texture2D NormalTex : register(t1);
Texture2D armTex : register(t2);
Texture2D ShadowMapNear : register(t3);
Texture2D ShadowMapFar : register(t4);
Texture2D HeightMap : register(t5);

SamplerState WrapSampler : register(s0);
SamplerState BorderSampler : register(s1);









//�e�b�Z���[�V����
//�n���V�F�[�_�[
struct HS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Normal : NORMAL0;
    float2 TexCoord : TEXCOORD0;
    float4 Diffuse : COLOR0;
    float4 WorldPos : POSITION0;
    float4 PosSM : POSITION1;
    float4 Tangent : TANGENT0;
    float4 BiNormal : BINORMAL0;
    
};

struct HS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Normal : NORMAL0;
    float2 TexCoord : TEXCOORD0;
    float4 Diffuse : COLOR0;
    float4 WorldPos : POSITION0;
    float4 PosSM : POSITION1;
    float4 Tangent : TANGENT0;
    float4 BiNormal : BINORMAL0;
};

HS_OUTPUT HS_ControlPoint(HS_INPUT input)
{
    HS_OUTPUT output;
    output.Position = input.Position;
    output.Normal = input.Normal;
    output.TexCoord = input.TexCoord;
    output.Diffuse = input.Diffuse;
    output.WorldPos = input.WorldPos;
    output.PosSM = input.PosSM;
    output.Tangent = input.Tangent;
    output.BiNormal = input.BiNormal;
    return output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("HS_PatchConstants")]
HS_OUTPUT HSmain(InputPatch<HS_INPUT, 4> patch, uint id : SV_OutputControlPointID)
{
    return HS_ControlPoint(patch[id]);
}

struct HS_CONSTANT_DATA
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

HS_CONSTANT_DATA HS_PatchConstants(InputPatch<HS_INPUT, 4> patch)
{
    HS_CONSTANT_DATA output;
    output.edges[0] = tessellationFactor;
    output.edges[1] = tessellationFactor;
    output.edges[2] = tessellationFactor;
    output.edges[3] = tessellationFactor;
    output.inside[0] = tessellationFactor;
    output.inside[1] = tessellationFactor; // �K���S�Ă̗v�f��������
    return output;
}


struct DS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Normal : NORMAL0;
    float2 TexCoord : TEXCOORD0;
    float4 Diffuse : COLOR0;
    float4 WorldPos : POSITION0;
    float4 PosSM : POSITION1;
    float4 Tangent : TANGENT0;
    float4 BiNormal : BINORMAL0;
};

[domain("quad")]
DS_OUTPUT DSmain(HS_CONSTANT_DATA input, float2 uv : SV_DomainLocation, const OutputPatch<HS_OUTPUT, 4> patch)
{
    DS_OUTPUT output;
    float3 pos = patch[0].Position * (1.0f - uv.x) * (1.0f - uv.y) +
                 patch[1].Position * uv.x * (1.0f - uv.y) +
                 patch[2].Position * uv.x * uv.y +
                 patch[3].Position * (1.0f - uv.x) * uv.y;

    
    float3 wpos = patch[0].WorldPos * (1.0f - uv.x) * (1.0f - uv.y) +
                 patch[1].WorldPos * uv.x * (1.0f - uv.y) +
                 patch[2].WorldPos * uv.x * uv.y +
                 patch[3].WorldPos * (1.0f - uv.x) * uv.y;


    
    
    // Heightmap�̃f�[�^���g�p���č����𒲐�
    float height = HeightMap.SampleLevel(WrapSampler, uv, 0);
    pos.y += height;
    

    output.Position = float4(pos, 1.0f);
        
    float4 nor = (patch[0].Normal + patch[1].Normal + patch[2].Normal + patch[3].Normal) / 4.0f;
    
    nor = normalize(nor);
    output.Normal = nor;
    output.TexCoord = uv;
    output.Diffuse = patch[0].Diffuse; // �K�v�ɉ����ĕ�Ԃ��邱�Ƃ��\
    output.WorldPos = wpos; // �K�v�ɉ����ĕ�Ԃ��邱�Ƃ��\
    output.PosSM = patch[0].PosSM; // �K�v�ɉ����ĕ�Ԃ��邱�Ƃ��\
    output.Tangent = patch[0].Tangent; // �K�v�ɉ����ĕ�Ԃ��邱�Ƃ��\
    output.BiNormal = patch[0].BiNormal; // �K�v�ɉ����ĕ�Ԃ��邱�Ƃ��\

    return output;
}


//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================


float GetVarianceDirectionalShadowFactor(float4 shadowCoord)
{
    
    float2 depth = ShadowMapNear.Sample(BorderSampler, shadowCoord.xy).xy;
    float depth_sq = depth.x * depth.x; // E(x)^2
    float variance = depth.y - depth_sq; // ��^2 = E(x^2) - E(x^2)
    variance = saturate(variance + Shadow.facter); // facter��ǉ����Ĉ��萫������

    float fragDepth = shadowCoord.z;
    float md = fragDepth - depth.x; // t - ��
    float p = variance / (variance + (md * md)); // ��^2 / (��^2 + (t - ��)^2)

    return saturate(max(p, fragDepth <= depth.x)); // P(x >= t)�𖞂����Ƃ��̂�
}


void PSmain(in float4 inPosition : SV_POSITION,
						 in float4 inNormal : NORMAL0,
						 in float2 inTexCoord : TEXCOORD0,
						 in float4 inDiffuse : COLOR0,
						 in float4 inWorldPos : POSITION0,
						 in float4 inPosSM : POSITION1,
						 in float4 inTangent : TANGENT0,
						 in float4 inBiNormal : BINORMAL0,

						 out float4 outDiffuse : SV_Target)
{
    float4 color;

    float sma = 1.0;
    bool shadow;
    
    
    float4 normal = inNormal;
    
    if (Material.noNormalTex == 0)
    {
        // Sample the normal map
        float3 normalMap = NormalTex.Sample(WrapSampler, inTexCoord).rgb;
        
        normalMap.x = 1.0 - normalMap.x;
        normalMap.y = 1.0 - normalMap.y;
        //normalMap.z = 1.0 - normalMap.z;
       
        normalMap = normalize(normalMap * 2.0 - 1.0);
        
        
        
        float3x3 TBN = float3x3(inTangent.xyz, inBiNormal.xyz, inNormal.xyz);
        normal.xyz = mul(normalMap, TBN);
        
        
    }
    
    					//�e
    if (Shadow.enable == 1)
    {
        if (inPosSM.z > 1.0)
        {
            sma = 1.0;
        }
        else if (Shadow.mode == 0)
        {
            float sm0 = ShadowMapNear.Sample(BorderSampler, inPosSM.xy);

            
            if (inPosSM.z - 0.0002 > sm0)
            {
                sma = 0.5;


            }
        }
        else if (Shadow.mode == 1)
        {
            sma = GetVarianceDirectionalShadowFactor(inPosSM);
            if (sma < 0.99f)
            {
                sma = sma * sma;

            }

        }
        
 

    }
    else
    {
        sma = 1.0;
    }

	
    if (Material.noDiffuseTex == 0)
    {
        color = DiffuseTexture.Sample(WrapSampler, inTexCoord);

        color *= inDiffuse;
    }
    else
    {
        color = inDiffuse;
    }

    float alpha = color.a;
    //�f�B���N�V���i�����C�g
    if (direcLight.allEnable.x == 0)
    {
        color = color * Material.Diffuse * sma;
    }
    else
    {
        float4 tempColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
        float4 outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

        float3 lightDir;
        float light;
        float3 iA;
        float3 iD;
        float3 iS;

        
        for (int i = 0; i < MAX_DIREC_LIGHT; i++)
        {
  
            if (direcLight.m_Enable[i].x == 1)
            {
                lightDir = normalize(direcLight.m_Direction[i].xyz);
                light = dot(lightDir, normal.xyz);
                light = (0.5 - 0.5 * light);

         

                float3 r = 2.0 * normal.xyz * light - lightDir;

                float3 v = normalize(Camera.xyz - inWorldPos.xyz);
                        
                        
                iA = color.xyz * Material.Ambient.xyz * direcLight.m_Ambient[i].xyz;
                        
                        
                        
                iD = color * Material.Diffuse * light * direcLight.m_Diffuse[i]*sma;
                iS = color.xyz * pow(saturate(dot(r, v)), Material.Shininess) * Material.Specular.xyz;

                //if (light > 0.5)
                //{
                //    iD *= sma;
                //}
                        

                       
                        
                        
                tempColor = float4(saturate((iA + iD + iS)), 1.0f);

                
            }
            else
            {
                tempColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
            }
            
            outColor += tempColor;
            
            for (int i = 0; i < MAX_POINT_LIGHT; i++)
            {
                if (pointLight.m_Enable[i].x == 1)
                {
                }

            }

            
        }
        
        
        
        color = outColor;
        color.a = alpha;
        
    }
		

    
    
    outDiffuse = color;
}

        
