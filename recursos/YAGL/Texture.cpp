/*
 * Texture.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: jack
 */

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gl {

namespace TextureTarget {

GLuint texture_target_enum_to_int(texture_target_enum tte){
	if(tte==Tex1D)return GL_TEXTURE_1D;
	if(tte==Tex2D)return GL_TEXTURE_2D;
	if(tte==Tex3D)return GL_TEXTURE_3D;
	if(tte==Array1D)return GL_TEXTURE_1D_ARRAY;
	if(tte==Array2D)return GL_TEXTURE_2D_ARRAY;
	if(tte==Rectangle)return GL_TEXTURE_RECTANGLE;
	if(tte==CubeMap)return GL_TEXTURE_CUBE_MAP;
	if(tte==CubeMapArray)return GL_TEXTURE_CUBE_MAP_ARRAY;
	if(tte==Buffer)return GL_TEXTURE_BUFFER;
	if(tte==Multisample2D)return GL_TEXTURE_2D_MULTISAMPLE;
	if(tte==Multisample2DArray)return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
	return 0;
}

}

namespace TextureParamName {

GLuint param_name_to_int(param_name pv){
	if(pv==WrapS)return GL_TEXTURE_WRAP_S;
	if(pv==WrapT)return GL_TEXTURE_WRAP_T;
	if(pv==WrapR)return GL_TEXTURE_WRAP_R;
	if(pv==MinFilter)return GL_TEXTURE_MIN_FILTER;
	if(pv==MagFilter)return GL_TEXTURE_MAG_FILTER;
	return 0;
}

}

namespace TextureParamValue {

GLuint param_value_to_int(param_value pv){
	if(pv==Nearest)return GL_NEAREST;
	if(pv==Linear)return GL_LINEAR;
	if(pv==ClampToEdge)return GL_CLAMP_TO_EDGE;
	if(pv==ClampToBorder)return GL_CLAMP_TO_BORDER;
	if(pv==MirroredRepeat)return GL_MIRRORED_REPEAT;
	if(pv==Repeat)return GL_REPEAT;
	if(pv==MirrorClampToEdge)return GL_MIRROR_CLAMP_TO_EDGE;
	if(pv==LinearMipmapLinear)return GL_LINEAR_MIPMAP_LINEAR;
	if(pv==LinearMipmapNearest)return GL_LINEAR_MIPMAP_NEAREST;
	if(pv==NearestMipmapLinear)return GL_NEAREST_MIPMAP_LINEAR;
	if(pv==NearestMipmapNearest)return GL_NEAREST_MIPMAP_NEAREST;
	return 0;
}

}

Texture::Texture() {
	// TODO Auto-generated constructor stub

}

Texture::~Texture() {
	// TODO Auto-generated destructor stub
}

bool Texture::isCreated(){
	return id!=-1;
}

void Texture::setTarget(TextureTarget::texture_target_enum tte){
	target=tte;
}

void Texture::create(){
	glGenTextures(1,&id);
}

void Texture::bind(){
	glBindTexture(TextureTarget::texture_target_enum_to_int(target),id);
}

void Texture::unbind(){
	glBindTexture(TextureTarget::texture_target_enum_to_int(target),0);
}

void Texture::setParam(TextureParamName::param_name pn,TextureParamValue::param_value pv){
	glTexParameteri(TextureTarget::texture_target_enum_to_int(target),TextureParamName::param_name_to_int(pn),TextureParamValue::param_value_to_int(pv));
}

void Texture::setData(int w,int h,TextureData data,GLint internalFormat,GLint format){
	width=w;
	height=h;
	glTexImage2D(TextureTarget::texture_target_enum_to_int(target),0,internalFormat,w,h,0,format,GL_UNSIGNED_BYTE,data);


//	int num_mipmaps=8;
	//TODO: Why does this not change anything
//	glTexStorage2D(TextureTarget::texture_target_enum_to_int(target),num_mipmaps,GL_RGBA8,w,h);
//	glTexSubImage2D(TextureTarget::texture_target_enum_to_int(target),0,0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glGenerateMipmap(TextureTarget::texture_target_enum_to_int(target));
}

void Texture::bindToUnit(int u){
	glActiveTexture(GL_TEXTURE0+u);
	bind();
}

Texture createTexture(int w,int h,TextureData data,GLint internalFormat,GLint format){
	Texture t;
	t.setTarget(TextureTarget::Tex2D);
	t.create();
	t.bind();
	t.setParam(TextureParamName::WrapS,TextureParamValue::ClampToBorder);
	t.setParam(TextureParamName::WrapT,TextureParamValue::ClampToBorder);
	t.setParam(TextureParamName::MinFilter,TextureParamValue::Nearest);
	t.setParam(TextureParamName::MagFilter,TextureParamValue::Nearest);
	t.setData(w,h,data,internalFormat,format);
	t.unbind();
	return t;
}

Texture createEmptyTexture(int w,int h){
	return createTexture(w,h,nullptr);
}

Texture loadTexture(std::string fn,int i,GLint internalFormat,GLint format){
	TextureData img;
	int w;
	int h;
	int channels;
	stbi_set_flip_vertically_on_load(true);
	img=stbi_load(fn.c_str(),&w,&h,&channels,i);
	printf("Texture %s   width=%i, height=%i, channels=%i\n",fn.c_str(),w,h,channels);
	return createTexture(w,h,img,internalFormat,format);
}

void Texture::del(){
	glDeleteTextures(1,&id);
	id=-1;
}

} /* namespace gl */
