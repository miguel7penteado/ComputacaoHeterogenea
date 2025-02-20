/*
 * Sampler.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: jack
 */

#include "Sampler.h"

Sampler::Sampler() {
	// TODO Auto-generated constructor stub

}

Sampler::~Sampler() {
	// TODO Auto-generated destructor stub
}


Sampler::Sampler(int ns){
	numSamples=ns;
}

void Sampler::shuffleX(){
	for(int i=0;i<samples.size();i++){
		int target=rand()%samples.size();
		float temp=samples[target].x;
		samples[target].x=samples[i].x;
		samples[i].x=temp;
	}
}
void Sampler::shuffleY(){
	for(int i=0;i<samples.size();i++){
		int target=rand()%samples.size();
		float temp=samples[target].y;
		samples[target].y=samples[i].y;
		samples[i].y=temp;
	}
}

void Sampler::mapSamplesToSphere(){
	samplesSphere.clear();
	for(int i=0;i<samples.size();i++){
		float theta=TWO_PI*samples[i].x;
		float phi=TWO_PI*samples[i].y;
		samplesSphere.push_back(Vector3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta)));
	}
}

void Sampler::mapSamplesToHemisphere(){
	float e=0;
	samplesHemisphere.clear();
	for(int i=0;i<samples.size();i++){
		float cosPhi=cos(2*PI*samples[i].x);
		float sinPhi=sin(2*PI*samples[i].x);
		float cosTheta=pow((1-samples[i].y),1/(e+1));
		float sinTheta=sqrt(1-cosTheta*cosTheta);
		samplesHemisphere.push_back(Vector3(sinTheta*cosPhi,sinTheta*sinPhi,cosTheta));
	}
}

Vector3 Sampler::sampleSphere(){
	indexSphere+=rand()%jump;
	return samplesSphere[indexSphere%numSamples];
}
Vector3 Sampler::sampleHemisphere(){
	float theta=TWO_PI*randomFloat();
	float phi=TWO_PI*randomFloat();
	return Vector3(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
//	indexHemisphere+=rand()%jump;
//	return samplesHemisphere[indexHemisphere%numSamples];
}

