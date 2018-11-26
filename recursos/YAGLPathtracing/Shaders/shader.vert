#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec2 inUV;

out vec2 uv;

void main(){
	gl_Position=vec4(inPos,1.0);
	uv=inUV;
}