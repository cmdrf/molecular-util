/*	GlConstants.h

MIT License

Copyright (c) 2019-2020 Fabian Herb

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MOLECULAR_UTIL_GLCONSTANTS_H
#define MOLECULAR_UTIL_GLCONSTANTS_H

#undef NO_ERROR // Defined in Windows somewhere

namespace molecular
{
namespace util
{

struct GlConstants
{
	enum
	{
		NO_ERROR                      = 0,
		NONE                          = 0,
		POINTS                        = 0x0000,
		LINES                         = 0x0001,
		LINE_LOOP                     = 0x0002,
		LINE_STRIP                    = 0x0003,
		TRIANGLES                     = 0x0004,
		TRIANGLE_STRIP                = 0x0005,
		TRIANGLE_FAN                  = 0x0006,
		QUADS                         = 0x0007,
		LINES_ADJACENCY               = 0x000A,
		LINE_STRIP_ADJACENCY          = 0x000B,
		TRIANGLES_ADJACENCY           = 0x000C,
		TRIANGLE_STRIP_ADJACENCY      = 0x000D,
		PATCHES                       = 0x000E,
		FRONT_LEFT                    = 0x0400,
		FRONT_RIGHT                   = 0x0401,
		BACK_LEFT                     = 0x0402,
		BACK_RIGHT                    = 0x0403,
		FRONT                         = 0x0404,
		BACK                          = 0x0405,
		LEFT                          = 0x0406,
		RIGHT                         = 0x0407,
		FRONT_AND_BACK                = 0x0408,
		INVALID_ENUM                  = 0x0500,
		INVALID_VALUE                 = 0x0501,
		INVALID_OPERATION             = 0x0502,
		OUT_OF_MEMORY                 = 0x0505,
		POLYGON_MODE                  = 0x0B40,
		POLYGON_SMOOTH                = 0x0B41,
		CULL_FACE                     = 0x0B44,
		CULL_FACE_MODE                = 0x0B45,
		FRONT_FACE                    = 0x0B46,
		DEPTH_RANGE                   = 0x0B70,
		DEPTH_TEST                    = 0x0B71,
		DEPTH_WRITEMASK               = 0x0B72,
		DEPTH_CLEAR_VALUE             = 0x0B73,
		DEPTH_FUNC                    = 0x0B74,
		TEXTURE_WIDTH                 = 0x1000,
		TEXTURE_HEIGHT                = 0x1001,
		TEXTURE_INTERNAL_FORMAT       = 0x1003,
		TEXTURE_BORDER_COLOR          = 0x1004,
		BYTE                          = 0x1400,
		UNSIGNED_BYTE                 = 0x1401,
		SHORT                         = 0x1402,
		UNSIGNED_SHORT                = 0x1403,
		INT                           = 0x1404,
		UNSIGNED_INT                  = 0x1405,
		FLOAT                         = 0x1406,
		HALF_FLOAT                    = 0x140B,
		FIXED                         = 0x140C,
		DEPTH_COMPONENT               = 0x1902,
		RED                           = 0x1903,
		GREEN                         = 0x1904,
		BLUE                          = 0x1905,
		ALPHA                         = 0x1906,
		RGB                           = 0x1907,
		RGBA                          = 0x1908,
		VENDOR                        = 0x1F00,
		RENDERER                      = 0x1F01,
		VERSION                       = 0x1F02,
		EXTENSIONS                    = 0x1F03,
		NEAREST                       = 0x2600,
		LINEAR                        = 0x2601,
		NEAREST_MIPMAP_NEAREST        = 0x2700,
		LINEAR_MIPMAP_NEAREST         = 0x2701,
		NEAREST_MIPMAP_LINEAR         = 0x2702,
		LINEAR_MIPMAP_LINEAR          = 0x2703,
		TEXTURE_MAG_FILTER            = 0x2800,
		TEXTURE_MIN_FILTER            = 0x2801,
		TEXTURE_WRAP_S                = 0x2802,
		TEXTURE_WRAP_T                = 0x2803,
		BLEND_EQUATION_RGB            = 0x8009,
		UNSIGNED_BYTE_3_3_2           = 0x8032,
		UNSIGNED_SHORT_4_4_4_4        = 0x8033,
		UNSIGNED_SHORT_5_5_5_1        = 0x8034,
		UNSIGNED_INT_8_8_8_8          = 0x8035,
		UNSIGNED_INT_10_10_10_2       = 0x8036,
		RGB4                          = 0x804F,
		RGB5                          = 0x8050,
		RGB8                          = 0x8051,
		RGB10                         = 0x8052,
		RGB12                         = 0x8053,
		RGB16                         = 0x8054,
		RGBA2                         = 0x8055,
		RGBA4                         = 0x8056,
		RGB5_A1                       = 0x8057,
		RGBA8                         = 0x8058,
		RGB10_A2                      = 0x8059,
		RGBA12                        = 0x805A,
		RGBA16                        = 0x805B,
		TEXTURE_3D                    = 0x806F,
		TEXTURE_WRAP_R                = 0x8072,
		MAX_3D_TEXTURE_SIZE           = 0x8073,
		MULTISAMPLE                   = 0x809D,
		BGR                           = 0x80E0,
		BGRA                          = 0x80E1,
		CLAMP_TO_BORDER               = 0x812D,
		CLAMP_TO_EDGE                 = 0x812F,
		TEXTURE_MIN_LOD               = 0x813A,
		TEXTURE_MAX_LOD               = 0x813B,
		TEXTURE_BASE_LEVEL            = 0x813C,
		TEXTURE_MAX_LEVEL             = 0x813D,
		DEPTH_COMPONENT16             = 0x81A5,
		DEPTH_COMPONENT24             = 0x81A6,
		DEPTH_COMPONENT32             = 0x81A7,
		FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210,
		FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211,
		FRAMEBUFFER_ATTACHMENT_RED_SIZE = 0x8212,
		FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213,
		FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214,
		FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215,
		FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216,
		FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217,
		FRAMEBUFFER_DEFAULT           = 0x8218,
		FRAMEBUFFER_UNDEFINED         = 0x8219,
		DEPTH_STENCIL_ATTACHMENT      = 0x821A,
		NUM_EXTENSIONS                = 0x821D,
		RG                            = 0x8227,
		RG_INTEGER                    = 0x8228,
		R8                            = 0x8229,
		RG8                           = 0x822B,
		R16F                          = 0x822D,
		R32F                          = 0x822E,
		RG16F                         = 0x822F,
		RG32F                         = 0x8230,
		R8I                           = 0x8231,
		R8UI                          = 0x8232,
		R16I                          = 0x8233,
		R16UI                         = 0x8234,
		R32I                          = 0x8235,
		R32UI                         = 0x8236,
		RG8I                          = 0x8237,
		RG8UI                         = 0x8238,
		RG16I                         = 0x8239,
		RG16UI                        = 0x823A,
		RG32I                         = 0x823B,
		RG32UI                        = 0x823C,
		COMPRESSED_RGB_S3TC_DXT1_EXT  = 0x83F0,
		COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1,
		COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2,
		COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3,
		TEXTURE0                      = 0x84C0,
		COMPRESSED_RGB                = 0x84ED,
		COMPRESSED_RGBA               = 0x84EE,
		TEXTURE_COMPRESSION_HINT      = 0x84EF,
		MAX_TEXTURE_LOD_BIAS          = 0x84FD,
		TEXTURE_LOD_BIAS              = 0x8501,
		PROGRAM_POINT_SIZE            = 0x8642,
		NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2,
		COMPRESSED_TEXTURE_FORMATS    = 0x86A3,
		ATC_RGBA_INTERPOLATED_ALPHA_AMD = 0x87EE,
		_3DC_X_AMD                     = 0x87F9,
		_3DC_XY_AMD                    = 0x87FA,
		RGBA32F                       = 0x8814,
		RGB32F                        = 0x8815,
		RGBA16F                       = 0x881A,
		RGB16F                        = 0x881B,
		TEXTURE_COMPARE_MODE          = 0x884C,
		TEXTURE_COMPARE_FUNC          = 0x884D,
		COMPARE_REF_TO_TEXTURE        = 0x884E,
		QUERY_RESULT                  = 0x8866,
		ARRAY_BUFFER                  = 0x8892,
		ELEMENT_ARRAY_BUFFER          = 0x8893,
		ARRAY_BUFFER_BINDING          = 0x8894,
		ELEMENT_ARRAY_BUFFER_BINDING  = 0x8895,
		STREAM_DRAW                   = 0x88E0,
		STREAM_READ                   = 0x88E1,
		STREAM_COPY                   = 0x88E2,
		STATIC_DRAW                   = 0x88E4,
		STATIC_READ                   = 0x88E5,
		STATIC_COPY                   = 0x88E6,
		DYNAMIC_DRAW                  = 0x88E8,
		DYNAMIC_READ                  = 0x88E9,
		DYNAMIC_COPY                  = 0x88EA,
		UNIFORM_BUFFER                = 0x8A11,
		UNIFORM_BUFFER_BINDING        = 0x8A28,
		UNIFORM_BUFFER_START          = 0x8A29,
		UNIFORM_BUFFER_SIZE           = 0x8A2A,
		MAX_VERTEX_UNIFORM_BLOCKS     = 0x8A2B,
		MAX_GEOMETRY_UNIFORM_BLOCKS   = 0x8A2C,
		MAX_FRAGMENT_UNIFORM_BLOCKS   = 0x8A2D,
		MAX_COMBINED_UNIFORM_BLOCKS   = 0x8A2E,
		MAX_UNIFORM_BUFFER_BINDINGS   = 0x8A2F,
		MAX_UNIFORM_BLOCK_SIZE        = 0x8A30,
		MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31,
		MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = 0x8A32,
		MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33,
		UNIFORM_BUFFER_OFFSET_ALIGNMENT = 0x8A34,
		ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35,
		ACTIVE_UNIFORM_BLOCKS         = 0x8A36,
		UNIFORM_TYPE                  = 0x8A37,
		UNIFORM_SIZE                  = 0x8A38,
		UNIFORM_NAME_LENGTH           = 0x8A39,
		UNIFORM_BLOCK_INDEX           = 0x8A3A,
		UNIFORM_OFFSET                = 0x8A3B,
		UNIFORM_ARRAY_STRIDE          = 0x8A3C,
		UNIFORM_MATRIX_STRIDE         = 0x8A3D,
		UNIFORM_IS_ROW_MAJOR          = 0x8A3E,
		UNIFORM_BLOCK_BINDING         = 0x8A3F,
		UNIFORM_BLOCK_DATA_SIZE       = 0x8A40,
		UNIFORM_BLOCK_NAME_LENGTH     = 0x8A41,
		UNIFORM_BLOCK_ACTIVE_UNIFORMS = 0x8A42,
		UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43,
		UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44,
		UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45,
		UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46,
		FRAGMENT_SHADER               = 0x8B30,
		VERTEX_SHADER                 = 0x8B31,
		FLOAT_VEC2                    = 0x8B50,
		FLOAT_VEC3                    = 0x8B51,
		FLOAT_VEC4                    = 0x8B52,
		INT_VEC2                      = 0x8B53,
		INT_VEC3                      = 0x8B54,
		INT_VEC4                      = 0x8B55,
		BOOL                          = 0x8B56,
		BOOL_VEC2                     = 0x8B57,
		BOOL_VEC3                     = 0x8B58,
		BOOL_VEC4                     = 0x8B59,
		FLOAT_MAT2                    = 0x8B5A,
		FLOAT_MAT3                    = 0x8B5B,
		FLOAT_MAT4                    = 0x8B5C,
		SAMPLER_1D                    = 0x8B5D,
		SAMPLER_2D                    = 0x8B5E,
		SAMPLER_3D                    = 0x8B5F,
		SAMPLER_CUBE                  = 0x8B60,
		SAMPLER_1D_SHADOW             = 0x8B61,
		SAMPLER_2D_SHADOW             = 0x8B62,
		SAMPLER_2D_RECT               = 0x8B63,
		SAMPLER_2D_RECT_SHADOW        = 0x8B64,
		DELETE_STATUS                 = 0x8B80,
		COMPILE_STATUS                = 0x8B81,
		LINK_STATUS                   = 0x8B82,
		VALIDATE_STATUS               = 0x8B83,
		INFO_LOG_LENGTH               = 0x8B84,
		ATTACHED_SHADERS              = 0x8B85,
		ACTIVE_UNIFORMS               = 0x8B86,
		ACTIVE_UNIFORM_MAX_LENGTH     = 0x8B87,
		ACTIVE_ATTRIBUTES             = 0x8B89,
		ACTIVE_ATTRIBUTE_MAX_LENGTH   = 0x8B8A,
		SHADING_LANGUAGE_VERSION      = 0x8B8C,
		CURRENT_PROGRAM               = 0x8B8D,
		PALETTE4_RGB8_OES             = 0x8B90,
		PALETTE4_RGBA8_OES            = 0x8B91,
		PALETTE4_R5_G6_B5_OES         = 0x8B92,
		PALETTE4_RGBA4_OES            = 0x8B93, 
		PALETTE4_RGB5_A1_OES          = 0x8B94,
		PALETTE8_RGB8_OES             = 0x8B95,
		PALETTE8_RGBA8_OES            = 0x8B96,
		PALETTE8_R5_G6_B5_OES         = 0x8B97,
		PALETTE8_RGBA4_OES            = 0x8B98,
		PALETTE8_RGB5_A1_OES          = 0x8B99,
		SRGB                          = 0x8C40,
		SRGB8                         = 0x8C41,
		SRGB_ALPHA                    = 0x8C42,
		SRGB8_ALPHA8                  = 0x8C43,
		COMPRESSED_SRGB               = 0x8C48,
		COMPRESSED_SRGB_ALPHA         = 0x8C49,
		COMPRESSED_SRGB_S3TC_DXT1_EXT = 0x8C4C,
		COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT = 0x8C4D,
		COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT = 0x8C4E,
		COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT = 0x8C4F,
		TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76,
		TRANSFORM_FEEDBACK_BUFFER_MODE = 0x8C7F,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80,
		TRANSFORM_FEEDBACK_VARYINGS   = 0x8C83,
		TRANSFORM_FEEDBACK_BUFFER_START = 0x8C84,
		TRANSFORM_FEEDBACK_BUFFER_SIZE = 0x8C85,
		TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88,
		RASTERIZER_DISCARD            = 0x8C89,
		MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B,
		INTERLEAVED_ATTRIBS           = 0x8C8C,
		SEPARATE_ATTRIBS              = 0x8C8D,
		TRANSFORM_FEEDBACK_BUFFER     = 0x8C8E,
		TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F,
		ATC_RGB_AMD                   = 0x8C92,
		ATC_RGBA_EXPLICIT_ALPHA_AMD   = 0x8C93,
		FRAMEBUFFER_BINDING           = 0x8CA6,
		DRAW_FRAMEBUFFER_BINDING      = FRAMEBUFFER_BINDING,
		RENDERBUFFER_BINDING          = 0x8CA7,
		READ_FRAMEBUFFER              = 0x8CA8,
		DRAW_FRAMEBUFFER              = 0x8CA9,
		READ_FRAMEBUFFER_BINDING      = 0x8CAA,
		RENDERBUFFER_SAMPLES          = 0x8CAB,
		DEPTH_COMPONENT32F            = 0x8CAC,
		FRAMEBUFFER_COMPLETE          = 0x8CD5,
		FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6,
		FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
		FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
		FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
		FRAMEBUFFER_UNSUPPORTED       = 0x8CDD,
		MAX_COLOR_ATTACHMENTS         = 0x8CDF,
		COLOR_ATTACHMENT0             = 0x8CE0,
		DEPTH_ATTACHMENT              = 0x8D00,
		STENCIL_ATTACHMENT            = 0x8D20,
		FRAMEBUFFER                   = 0x8D40,
		RENDERBUFFER                  = 0x8D41,
		FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
		ETC1_RGB8_OES                 = 0x8D64,
		RGBA32UI                      = 0x8D70,
		RGB32UI                       = 0x8D71,
		RGBA16UI                      = 0x8D76,
		RGB16UI                       = 0x8D77,
		RGBA8UI                       = 0x8D7C,
		RGB8UI                        = 0x8D7D,
		RGBA32I                       = 0x8D82,
		RGB32I                        = 0x8D83,
		RGBA16I                       = 0x8D88,
		RGB16I                        = 0x8D89,
		RGBA8I                        = 0x8D8E,
		RGB8I                         = 0x8D8F,
		RED_INTEGER                   = 0x8D94,
		RGB_INTEGER                   = 0x8D98,
		RGBA_INTEGER                  = 0x8D99,
		FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8,
		FRAMEBUFFER_SRGB              = 0x8DB9,
		SAMPLER_1D_ARRAY              = 0x8DC0,
		SAMPLER_2D_ARRAY              = 0x8DC1,
		SAMPLER_1D_ARRAY_SHADOW       = 0x8DC3,
		SAMPLER_2D_ARRAY_SHADOW       = 0x8DC4,
		SAMPLER_CUBE_SHADOW           = 0x8DC5,
		UNSIGNED_INT_VEC2             = 0x8DC6,
		UNSIGNED_INT_VEC3             = 0x8DC7,
		UNSIGNED_INT_VEC4             = 0x8DC8,
		INT_SAMPLER_1D                = 0x8DC9,
		INT_SAMPLER_2D                = 0x8DCA,
		INT_SAMPLER_3D                = 0x8DCB,
		INT_SAMPLER_CUBE              = 0x8DCC,
		INT_SAMPLER_1D_ARRAY          = 0x8DCE,
		INT_SAMPLER_2D_ARRAY          = 0x8DCF,
		UNSIGNED_INT_SAMPLER_1D       = 0x8DD1,
		UNSIGNED_INT_SAMPLER_2D       = 0x8DD2,
		UNSIGNED_INT_SAMPLER_3D       = 0x8DD3,
		UNSIGNED_INT_SAMPLER_CUBE     = 0x8DD4,
		UNSIGNED_INT_SAMPLER_1D_ARRAY = 0x8DD6,
		UNSIGNED_INT_SAMPLER_2D_ARRAY = 0x8DD7,
		GEOMETRY_SHADER               = 0x8DD9,
		TRANSFORM_FEEDBACK            = 0x8E22,
		TRANSFORM_FEEDBACK_PAUSED     = 0x8E23,
		TRANSFORM_FEEDBACK_BUFFER_PAUSED = 0x8E23,
		TRANSFORM_FEEDBACK_ACTIVE     = 0x8E24,
		TRANSFORM_FEEDBACK_BUFFER_ACTIVE = 0x8E24,
		TRANSFORM_FEEDBACK_BINDING    = 0x8E25,
		R8_SNORM                      = 0x8F94,
		RG8_SNORM                     = 0x8F95,
		RGB8_SNORM                    = 0x8F96,
		RGBA8_SNORM                   = 0x8F97,
		SIGNED_NORMALIZED             = 0x8F9C,
		PRIMITIVE_RESTART             = 0x8F9D,
		PRIMITIVE_RESTART_INDEX       = 0x8F9E,
		TEXTURE_2D_MULTISAMPLE        = 0x9100,
		PROXY_TEXTURE_2D_MULTISAMPLE  = 0x9101,
		TEXTURE_2D_MULTISAMPLE_ARRAY  = 0x9102,
		PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103,
		TEXTURE_BINDING_2D_MULTISAMPLE = 0x9104,
		TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = 0x9105,
		TEXTURE_SAMPLES               = 0x9106,
		TEXTURE_FIXED_SAMPLE_LOCATIONS = 0x9107,
		SAMPLER_2D_MULTISAMPLE        = 0x9108,
		INT_SAMPLER_2D_MULTISAMPLE    = 0x9109,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = 0x910A,
		SAMPLER_2D_MULTISAMPLE_ARRAY  = 0x910B,
		INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910C,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D,
		MAX_COLOR_TEXTURE_SAMPLES     = 0x910E,
		MAX_DEPTH_TEXTURE_SAMPLES     = 0x910F,
		MAX_INTEGER_SAMPLES           = 0x9110,
		COMPRESSED_R11_EAC            = 0x9270,
		COMPRESSED_SIGNED_R11_EAC     = 0x9271,
		COMPRESSED_RG11_EAC           = 0x9272,
		COMPRESSED_SIGNED_RG11_EAC    = 0x9273,
		COMPRESSED_RGB8_ETC2          = 0x9274,
		COMPRESSED_SRGB8_ETC2         = 0x9275,
		COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9276,
		COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9277,
		COMPRESSED_RGBA8_ETC2_EAC     = 0x9278,
		COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = 0x9279,
		COMPRESSED_RGBA_ASTC_4x4_KHR  = 0x93B0,
		COMPRESSED_RGBA_ASTC_5x4_KHR  = 0x93B1,
		COMPRESSED_RGBA_ASTC_5x5_KHR  = 0x93B2,
		COMPRESSED_RGBA_ASTC_6x5_KHR  = 0x93B3,
		COMPRESSED_RGBA_ASTC_6x6_KHR  = 0x93B4,
		COMPRESSED_RGBA_ASTC_8x5_KHR  = 0x93B5,
		COMPRESSED_RGBA_ASTC_8x6_KHR  = 0x93B6,
		COMPRESSED_RGBA_ASTC_8x8_KHR  = 0x93B7,
		COMPRESSED_RGBA_ASTC_10x5_KHR = 0x93B8,
		COMPRESSED_RGBA_ASTC_10x6_KHR = 0x93B9,
		COMPRESSED_RGBA_ASTC_10x8_KHR = 0x93BA,
		COMPRESSED_RGBA_ASTC_10x10_KHR = 0x93BB,
		COMPRESSED_RGBA_ASTC_12x10_KHR = 0x93BC,
		COMPRESSED_RGBA_ASTC_12x12_KHR = 0x93BD,
		COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR = 0x93D0,
		COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR = 0x93D1,
		COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR = 0x93D2,
		COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR = 0x93D3,
		COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR = 0x93D4,
		COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR = 0x93D5,
		COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR = 0x93D6,
		COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR = 0x93D7,
		COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR = 0x93D8,
		COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR = 0x93D9,
		COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR = 0x93DA,
		COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR = 0x93DB,
		COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR = 0x93DC,
		COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR = 0x93DD
	};
};

}
}

#endif
