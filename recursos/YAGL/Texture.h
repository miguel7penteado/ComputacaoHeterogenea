/*
 * Texture.h
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

namespace gl {

namespace TextureTarget {

enum texture_target_enum {
	Tex1D,
	Tex2D,
	Tex3D,
	Array1D,
	Array2D,
	Rectangle,
	CubeMap,
	CubeMapArray,
	Buffer,
	Multisample2D,
	Multisample2DArray
};

GLuint texture_target_enum_to_int(texture_target_enum tte);

}

namespace TextureParamName {

enum param_name {
	WrapS,
	WrapT,
	WrapR,
	MinFilter,
	MagFilter
};

GLuint param_name_to_int(param_name pn);

}

namespace TextureParamValue {

enum param_value {
	Nearest,
	Linear,
	ClampToEdge,
	ClampToBorder,
	MirroredRepeat,
	Repeat,
	MirrorClampToEdge,
	LinearMipmapLinear,
	LinearMipmapNearest,
	NearestMipmapLinear,
	NearestMipmapNearest
};

GLuint param_value_to_int(param_value pv);

}

typedef unsigned char* TextureData;

class Texture {
public:
	Texture();
	Texture(TextureTarget::texture_target_enum tte);
	virtual ~Texture();

	GLuint id=-1;
	int width;
	int height;

	bool isCreated();

	TextureTarget::texture_target_enum target;

	void create();
	void bind();
	void unbind();
	void setTarget(TextureTarget::texture_target_enum tte);
	void setParam(TextureParamName::param_name pn,TextureParamValue::param_value pv);
	void setData(int w,int h,TextureData data,GLint internalFormat=GL_RGBA32F,GLint format=GL_RGBA);
	void bindToUnit(int u);

	void del();

};

Texture createTexture(int w,int h,TextureData data,GLint internalFormat=GL_RGBA32F,GLint format=GL_RGBA);
Texture createEmptyTexture(int w,int h);
Texture loadTexture(std::string fn,int i=4,GLint internalFormat=GL_RGBA32F,GLint format=GL_RGBA);

} /* namespace gl */

#endif /* TEXTURE_H_ */
