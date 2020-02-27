#version 450 core

layout (location=0) in vec3 inPos;
layout (location=1) in vec2 inUV;
layout (location=3) in float inAO;
layout (location=4) in float inTorchlight;

out vec2 uv;

out float ao;
out float torchlight;

uniform mat4 MVP;

void main(){
	gl_Position=MVP*vec4(inPos,1.0);
	uv=inUV;
	ao=inAO;
	torchlight=inTorchlight;
}