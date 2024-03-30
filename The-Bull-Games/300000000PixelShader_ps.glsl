#if 0
	***	hlms_uv_count0	2
	***	hlms_pose	0
	***	texture_bind0	2
	***	hlms_uv_count	1
	***	diffuse_map0_idx	0
	***	hlms_disable_stage	0
	***	glsl	635204550
	***	uv_diffuse0	0
	***	out_uv_count	1
	***	hlms_high_quality	0
	***	num_array_textures	0
	***	alpha_test	0
	***	glsles	1070293233
	***	out_uv0_out_uv	0
	***	sampler_unit_slot_start	2
	***	hlms_identity_viewproj	1
	***	diffuse_map0	1
	***	out_uv0_texture_matrix	0
	***	hlms_pose_normals	0
	***	hlms_pose_half	0
	***	GL_ARB_shading_language_420pack	1
	***	hlms_alphablend	1
	***	num_textures	1
	***	hlms_shadow_uses_depth_texture	0
	***	hlms_tangent	0
	***	hlms_bones_per_vertex	0
	***	out_uv0_tex_unit	0
	***	alpha_test_shadow_caster_only	0
	***	materials_per_buffer	2
	***	hlms_skeleton	0
	***	out_uv0_source_uv	0
	***	syntax	635204550
	***	metal	-1698855755
	***	GL_ARB_base_instance	1
	***	diffuse_map	1
	***	GL3+	450
	***	hlms_render_depth_only	0
	***	hlms_qtangent	0
	***	out_uv_half_count0	2
	***	diffuse	0
	***	out_uv_half_count	1
	***	diffuse_map0_sampler	0
	***	hlms_normal	0
	***	num_samplers	1
	***	hlsl	-334286542
	***	GL_ARB_texture_buffer_range	1
	***	hlms_colour	1
	DONE DUMPING PROPERTIES
	***	blend_mode_idx3	@insertpiece( NormalNonPremul)
	***	uv_diffuse_swizzle0	xy
	***	blend_mode_idx11	@insertpiece( NormalNonPremul)
	***	blend_mode_idx2	@insertpiece( NormalNonPremul)
	***	blend_mode_idx14	@insertpiece( NormalNonPremul)
	***	blend_mode_idx5	@insertpiece( NormalNonPremul)
	***	blend_mode_idx8	@insertpiece( NormalNonPremul)
	***	blend_mode_idx10	@insertpiece( NormalNonPremul)
	***	blend_mode_idx9	@insertpiece( NormalNonPremul)
	***	blend_mode_idx15	@insertpiece( NormalNonPremul)
	***	blend_mode_idx6	@insertpiece( NormalNonPremul)
	***	blend_mode_idx7	@insertpiece( NormalNonPremul)
	***	blend_mode_idx1	@insertpiece( NormalNonPremul)
	***	blend_mode_idx0	@insertpiece( NormalNonPremul)
	***	blend_mode_idx12	@insertpiece( NormalNonPremul)
	***	blend_mode_idx4	@insertpiece( NormalNonPremul)
	***	blend_mode_idx13	@insertpiece( NormalNonPremul)
	***	diffuse_map0_tex_swizzle	xxxy
	DONE DUMPING PIECES
#endif


    #version 430 core





    #extension GL_ARB_shading_language_420pack: require
    #define layout_constbuffer(x) layout( std140, x )





	#define bufferFetch texelFetch
	#define structuredBufferFetch texelFetch



	#define min3( a, b, c ) min( a, min( b, c ) )
	#define max3( a, b, c ) max( a, max( b, c ) )


#define float2 vec2
#define float3 vec3
#define float4 vec4

#define int2 ivec2
#define int3 ivec3
#define int4 ivec4

#define uint2 uvec2
#define uint3 uvec3
#define uint4 uvec4

#define float2x2 mat2
#define float3x3 mat3
#define float4x4 mat4
#define ogre_float4x3 mat3x4

#define ushort uint
#define ushort3 uint3
#define ushort4 uint4

//Short used for read operations. It's an int in GLSL & HLSL. An ushort in Metal
#define rshort int
#define rshort2 int2
#define rint int
//Short used for write operations. It's an int in GLSL. An ushort in HLSL & Metal
#define wshort2 int2
#define wshort3 int3

#define toFloat3x3( x ) mat3( x )
#define buildFloat3x3( row0, row1, row2 ) mat3( row0, row1, row2 )

#define mul( x, y ) ((x) * (y))
#define saturate(x) clamp( (x), 0.0, 1.0 )
#define lerp mix
#define rsqrt inversesqrt
#define INLINE
#define NO_INTERPOLATION_PREFIX flat
#define NO_INTERPOLATION_SUFFIX

#define finalDrawId drawId
#define PARAMS_ARG_DECL
#define PARAMS_ARG

#define inVs_vertexId gl_VertexID
#define inVs_vertex vertex
#define inVs_blendWeights blendWeights
#define inVs_blendIndices blendIndices
#define inVs_qtangent qtangent


	#define inVs_drawId drawId



	#define inVs_uv0 uv0

#define outVs_Position gl_Position
#define outVs_viewportIndex gl_ViewportIndex
#define outVs_clipDistance0 gl_ClipDistance[0]

#define gl_SampleMaskIn0 gl_SampleMaskIn[0]
#define reversebits bitfieldReverse

#define outPs_colour0 outColour
#define OGRE_Sample( tex, sampler, uv ) texture( tex, uv )
#define OGRE_SampleLevel( tex, sampler, uv, lod ) textureLod( tex, uv, lod )
#define OGRE_SampleArray2D( tex, sampler, uv, arrayIdx ) texture( tex, vec3( uv, arrayIdx ) )
#define OGRE_SampleArray2DLevel( tex, sampler, uv, arrayIdx, lod ) textureLod( tex, vec3( uv, arrayIdx ), lod )
#define OGRE_SampleArrayCubeLevel( tex, sampler, uv, arrayIdx, lod ) textureLod( tex, vec4( uv, arrayIdx ), lod )
#define OGRE_SampleGrad( tex, sampler, uv, ddx, ddy ) textureGrad( tex, uv, ddx, ddy )
#define OGRE_SampleArray2DGrad( tex, sampler, uv, arrayIdx, ddx, ddy ) textureGrad( tex, vec3( uv, arrayIdx ), ddx, ddy )
#define OGRE_ddx( val ) dFdx( val )
#define OGRE_ddy( val ) dFdy( val )
#define OGRE_Load2D( tex, iuv, lod ) texelFetch( tex, iuv, lod )
#define OGRE_LoadArray2D( tex, iuv, arrayIdx, lod ) texelFetch( tex, ivec3( iuv, arrayIdx ), lod )
#define OGRE_Load2DMS( tex, iuv, subsample ) texelFetch( tex, iuv, subsample )

#define OGRE_Load3D( tex, iuv, lod ) texelFetch( tex, ivec3( iuv ), lod )

#define bufferFetch1( buffer, idx ) texelFetch( buffer, idx ).x

#define OGRE_SAMPLER_ARG_DECL( samplerName )
#define OGRE_SAMPLER_ARG( samplerName )

#define OGRE_Texture3D_float4 sampler3D

#define CONST_BUFFER( bufferName, bindingPoint ) layout_constbuffer(binding = bindingPoint) uniform bufferName
#define CONST_BUFFER_STRUCT_BEGIN( structName, bindingPoint ) layout_constbuffer(binding = bindingPoint) uniform structName
#define CONST_BUFFER_STRUCT_END( variableName ) variableName

#define FLAT_INTERPOLANT( decl, bindingPoint ) flat decl
#define INTERPOLANT( decl, bindingPoint ) decl

#define OGRE_OUT_REF( declType, variableName ) out declType variableName
#define OGRE_INOUT_REF( declType, variableName ) inout declType variableName

#define OGRE_ARRAY_START( type ) type[](
#define OGRE_ARRAY_END )



layout(std140) uniform;
#define FRAG_COLOR		0




layout(location = FRAG_COLOR, index = 0) out vec4 outColour;


// START UNIFORM DECLARATION



struct Material
{
	vec4 alpha_test_threshold;
	vec4 diffuse;

	uvec4 indices0_3;
	uvec4 indices4_7;

	
};

layout_constbuffer(binding = 1) uniform MaterialBuf
{
	Material m[2];
} materialArray;


//Uniforms that change per Item/Entity
layout_constbuffer(binding = 2) uniform InstanceBuffer
{
	//.x =
	//Contains the material's start index.
	//
	//.y =
	//shadowConstantBias. Send the bias directly to avoid an
	//unnecessary indirection during the shadow mapping pass.
	//Must be loaded with uintBitsToFloat
	//
	//.z =
	//Contains 0 or 1 to index into passBuf.viewProj[]. Only used
	//if hlms_identity_viewproj_dynamic is set.
	uvec4 worldMaterialIdx[4096];
};



// END UNIFORM DECLARATION

in block
{

	
		flat uint drawId;
		vec4 colour;
		
			vec2 uv0;
	
	
	

} inPs;




uniform sampler2D	textureMaps[1];



Material material;

void main()
{
	

	uint materialId	= worldMaterialIdx[inPs.drawId].x;
	material = materialArray.m[materialId];

	




	//Load base image
	outColour = texture( textureMaps[0], inPs.uv0.xy ).xxxy;





	outColour *= inPs.colour ;
	


	



	
}


