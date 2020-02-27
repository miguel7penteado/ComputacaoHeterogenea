/*
 * ChunkManager.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: jack
 */

#include "ChunkManager.h"
#include "LightNode.h"

ChunkManager::ChunkManager() {
	// TODO Auto-generated constructor stub

}

ChunkManager::~ChunkManager() {
	// TODO Auto-generated destructor stub
}

bool contains_ivec2(std::vector<glm::ivec2> list,glm::ivec2 v){
	for(unsigned int i=0;i<list.size();i++)if(list[i]==v)return true;
	return false;
}
bool contains_ivec3(std::vector<glm::ivec3> list,glm::ivec3 v){
	for(unsigned int i=0;i<list.size();i++)if(list[i]==v)return true;
	return false;
}

ChunkPtr ChunkManager::getChunk(int x,int z,bool instantiateChunk){
	bool foundChunk=false;
	ChunkPtr c=nullptr;
	for(unsigned int i=0;i<chunks.size()&&!foundChunk;i++){
		if(chunks[i]->chunkPos.x==x&&chunks[i]->chunkPos.y==z){
			c=chunks[i];
			foundChunk=true;
		}
	}
	if(!foundChunk){
#ifdef DEBUG_CHUNKMANAGER
		printf("\tCreating data for %i,%i\n",x,z);
#endif
		c=new Chunk();
		c->chunkPos=glm::ivec2(x,z);
		c->createChunkData(noise,worldGen);
		chunks.push_back(c);
#ifdef DEBUG_CHUNKMANAGER
		printf("\tFinished creating data for %i,%i\n",x,z);
#endif
	}
	if(instantiateChunk){
		c->instantiated=true;
	}
	if(instantiateChunk&&!c->meshCreated){
#ifdef DEBUG_CHUNKMANAGER
		printf("\nInstantiating %i,%i\n",x,z);
#endif
		c->meshCreated=true;
		ChunkPtr xmi=getChunk(x-1,z,false);
		ChunkPtr xpl=getChunk(x+1,z,false);
		ChunkPtr zmi=getChunk(x,z-1,false);
		ChunkPtr zpl=getChunk(x,z+1,false);
		c->cXMI=xmi;
		c->cXPL=xpl;
		c->cZMI=zmi;
		c->cZPL=zpl;
//		setLighting(c);
		c->prepareMesh(atlas);
		c->prepareGL();
#ifdef DEBUG_CHUNKMANAGER
		printf("Finished instantiating %i,%i:  %i,%i,%i,%i\n",x,z,c->vao.id,c->vboPos.id,c->vboUV.id,c->ebo.id);
#endif
	}
	return c;
}

void ChunkManager::eraseChunk(int x,int z){
	for(unsigned int i=0;i<chunks.size();i++){
		if(chunks[i]->chunkPos==glm::ivec2(x,z)){
			chunks[i]->instantiated=false;
		}
	}
}

void ChunkManager::setBlock(int x,int y,int z,Block b){
	glm::ivec2 xz(x,z);
	glm::ivec2 chunkCoord=getChunkCoord(xz);
	glm::ivec2 pos=getPosInChunk(xz);
	ChunkPtr chunk=getChunk(chunkCoord.x,chunkCoord.y,false);
	chunk->blockData[pos.x][y][pos.y]=b;
}

void ChunkManager::remeshChunk(int x,int z){
	ChunkPtr chunk=getChunk(x,z,false);
	ChunkPtr xmi=getChunk(x-1,z,false);
	ChunkPtr xpl=getChunk(x+1,z,false);
	ChunkPtr zmi=getChunk(x,z-1,false);
	ChunkPtr zpl=getChunk(x,z+1,false);
	chunk->cXMI=xmi;
	chunk->cXPL=xpl;
	chunk->cZMI=zmi;
	chunk->cZPL=zpl;
//	setLighting(chunk);
	chunk->prepareMesh(atlas);
	chunk->prepareGL();
}

void ChunkManager::setLight(int x,int y,int z,float l){
	glm::ivec2 pos=getChunkCoord(glm::ivec2(x,z));
	if(!contains_ivec2(remeshChunks,pos))remeshChunks.push_back(pos);
	glm::ivec2 p=getPosInChunk(glm::ivec2(x,z));
	getChunk(pos.x,pos.y,false)->setTorchlight(p.x,y,p.y,l);
}

float ChunkManager::getLight(int x,int y,int z){
	glm::ivec2 c=getChunkCoord(glm::ivec2(x,z));
	glm::ivec2 p=getPosInChunk(glm::ivec2(x,z));
	return getChunk(c.x,c.y,false)->torchlightData[p.x][y][p.y];
}

void ChunkManager::setTorchlight(int x,int y,int z,float l){
	glm::ivec2 chunk=getChunkCoord(glm::ivec2(x,z));
	glm::ivec2 pos=getPosInChunk(glm::ivec2(x,z));
	getChunk(chunk.x,chunk.y,false)->torchlightData[pos.x][y][pos.y]=l;
}

void ChunkManager::updateLights(){
	remeshChunks.clear();
	for(int i=0;i<chunks.size();i++){
		chunks[i]->clearLight();
	}
	for(int i=0;i<lights.size();i++){
		propogateLight(lights[i]);
	}
	remeshChunkList();
}

void ChunkManager::propogateLight(glm::ivec3 pos){
	setLight(pos.x,pos.y,pos.z,1);

	std::queue<LightNode>bfs;
	bfs.emplace(LightNode(pos.x,pos.y,pos.z,this));

	float df=0.1;

	while(!bfs.empty()){
		LightNode node=bfs.front();
		Chunk*chunk=node.chunk;
		glm::ivec3 p=node.pos;
		bfs.pop();
		int x=p.x;
		int y=p.y;
		int z=p.z;

		dirtyChunk(getChunkCoord(glm::ivec2(x,z)));

		glm::ivec2 ___posInChunk=getPosInChunk(glm::ivec2(x,z));
		glm::ivec3 pc=glm::ivec3(___posInChunk.x,y,___posInChunk.y);
		float f=chunk->getTorchlight(pc.x,pc.y,pc.z);
		if(f<0)continue;

		if(chunk->isEmpty(pc.x-1,pc.y,pc.z)&&chunk->getTorchlight(pc.x-1,pc.y,pc.z)<f-df){
			setTorchlight(x-1,y,z,f-df);
			bfs.emplace(LightNode(x-1,y,z,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x-1,z)));
		}
		if(chunk->isEmpty(pc.x+1,pc.y,pc.z)&&chunk->getTorchlight(pc.x+1,pc.y,pc.z)<f-df){
			setTorchlight(x+1,y,z,f-df);
			bfs.emplace(LightNode(x+1,y,z,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x+1,z)));
		}
		if(chunk->isEmpty(pc.x,pc.y-1,pc.z)&&chunk->getTorchlight(pc.x,pc.y-1,pc.z)<f-df){
			setTorchlight(x,y-1,z,f-df);
			bfs.emplace(LightNode(x,y-1,z,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x,z)));
		}
		if(chunk->isEmpty(pc.x,pc.y+1,pc.z)&&chunk->getTorchlight(pc.x,pc.y+1,pc.z)<f-df){
			setTorchlight(x,y+1,z,f-df);
			bfs.emplace(LightNode(x,y+1,z,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x,z)));
		}
		if(chunk->isEmpty(pc.x,pc.y,pc.z-1)&&chunk->getTorchlight(pc.x,pc.y,pc.z-1)<f-df){
			setTorchlight(x,y,z-1,f-df);
			bfs.emplace(LightNode(p.x,p.y,p.z-1,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x,z-1)));
		}
		if(chunk->isEmpty(pc.x,pc.y,pc.z+1)&&chunk->getTorchlight(pc.x,pc.y,pc.z+1)<f-df){
			setTorchlight(x,y,z+1,f-df);
			bfs.emplace(LightNode(x,y,z+1,this));
			dirtyChunk(getChunkCoord(glm::ivec2(x,z+1)));
		}

	}
}

void ChunkManager::dirtyChunk(glm::ivec2 v){
	if(!contains_ivec2(remeshChunks,v))remeshChunks.push_back(v);
}

void ChunkManager::dirtyChunk(int x,int z){
	glm::ivec2 v(x,z);
	if(!contains_ivec2(remeshChunks,v))remeshChunks.push_back(v);
}

void ChunkManager::addLight(glm::ivec3 pos){
	//TODO: figure out how to change world AND lights together
	lights.push_back(pos);
	remeshChunks.clear();

	propogateLight(pos);

	remeshChunkList();
}

void ChunkManager::remeshChunkList(){
	for(int i=0;i<remeshChunks.size();i++){
		printf("%i,%i\n",remeshChunks[i].x,remeshChunks[i].y);
		remeshChunk(remeshChunks[i].x,remeshChunks[i].y);
	}
}

void ChunkManager::render(gl::Shader shader,glm::mat4 vp){
	for(unsigned int i=0;i<chunks.size();i++){
		ChunkPtr c=chunks[i];
		if(c->instantiated){
			glGetError();
			glm::mat4 m=vp*c->getModelMatrix();
			if(i==0){
//				printf("%f,%f,%f,%f %f,%f,%f,%f %f,%f,%f,%f %f,%f,%f,%f\n",m[0][0],m[0][1],m[0][2],m[0][3],m[1][0],m[1][1],m[1][2],m[1][3],m[2][0],m[2][1],m[2][2],m[2][3],m[3][0],m[3][1],m[3][2],m[3][3]);
//				printf("%i\n",shader.getUniformLocation("MVP"));
			}
			shader.setMat4("MVP",m);
//			printError();
			c->render();
		}
	}
}

int ChunkManager::getNumChunksInMemory(){
	return chunks.size();
}

int ChunkManager::getNumChunksRendered(){
	int i=0;
	for(ChunkPtr c:chunks){
		if(c->instantiated)i++;
	}
	return i;
}

void ChunkManager::update(int frames,glm::ivec2 chunkPos){
	int chunkX=chunkPos.x;
	int chunkZ=chunkPos.y;

	int o=7;
	for(int x=-o;x<=o;x++){
		for(int z=-o;z<=o;z++){
			if(!contains_ivec2(chunksToAdd,glm::ivec2(x+chunkX,z+chunkZ))){
				chunksToAdd.push_back(glm::ivec2(x+chunkX,z+chunkZ));
			}
//				getChunk(x+chunkX,z+chunkZ,true);
		}
	}
	for(int i=0;i<10;i++){
		if(frames%1==0&&chunksToAdd.size()>0){
			glm::ivec2 chunkToAdd=chunksToAdd[0];
			getChunk(chunkToAdd.x,chunkToAdd.y,true);
			chunksToAdd.erase(chunksToAdd.begin());
		}
	}
	for(int i=0;i<200;i++){
		if(frames%1==0&&chunksToRemove.size()>0){
			glm::ivec2 chunkToRem=chunksToRemove[0];
			eraseChunk(chunkToRem.x,chunkToRem.y);
			chunksToRemove.erase(chunksToRemove.begin());
		}
	}

	for(unsigned int i=0;i<chunks.size();i++){
		float d=max(abs(chunks[i]->chunkPos.x-chunkX),abs(chunks[i]->chunkPos.y-chunkZ));
		if(d>o+2&&!contains_ivec2(chunksToRemove,chunks[i]->chunkPos))chunksToRemove.push_back(chunks[i]->chunkPos);
	}
}

Block ChunkManager::getBlock(int x,int y,int z){
	glm::ivec2 chunkPos=getChunkCoord(glm::ivec2(x,z));
	glm::ivec2 posInChunk=getPosInChunk(glm::ivec2(x,z));
	ChunkPtr c=getChunk(chunkPos.x,chunkPos.y,false);
	return c->blockData[posInChunk.x][y][posInChunk.y];
}
Block ChunkManager::getBlock(glm::ivec3 p){
	return getBlock(p.x,p.y,p.z);
}

//In world coordinates, not pos in chunk coordinates
Intersection ChunkManager::intersectWorld(glm::vec3 start,glm::vec3 dir,float range){
	//Line 70 of https://bitbucket.org/volumesoffun/polyvox/src/9a71004b1e72d6cf92c41da8995e21b652e6b836/include/PolyVox/Raycast.inl?at=develop&fileviewer=file-view-default
	//Don't use the callbacks until later

	glm::vec3 end=start+dir*range;

	float o=0;
	const float x1=start.x+o;
	const float y1=start.y+o;
	const float z1=start.z+o;
	const float x2=end.x+o;
	const float y2=end.y+o;
	const float z2=end.z+o;

	int i=floor(x1);
	int j=floor(y1);
	int k=floor(z1);

//	const int iend=floor(x2);
//	const int jend=floor(y2);
//	const int kend=floor(z2);

	const int di = ((x1 < x2) ? 1 : ((x1 > x2) ? -1 : 0));
	const int dj = ((y1 < y2) ? 1 : ((y1 > y2) ? -1 : 0));
	const int dk = ((z1 < z2) ? 1 : ((z1 > z2) ? -1 : 0));

	const float deltax=1/std::abs(x2-x1);
	const float deltay=1/std::abs(y2-y1);
	const float deltaz=1/std::abs(z2-z1);

	const float minx=floor(x1),maxx=minx+1;
	float tx=((x1>x2)?(x1-minx):(maxx-x1))*deltax;

	const float miny=floor(y1),maxy=miny+1;
	float ty=((y1>y2)?(y1-miny):(maxy-y1))*deltay;

	const float minz=floor(z1),maxz=minz+1;
	float tz=((z1>z2)?(z1-minz):(maxz-z1))*deltaz;

	std::vector<glm::ivec3>list;
	glm::vec3 normal(0,0,0);

	for(int num=0;num<range;num++){
		if(j<0||j>=CHUNK_HEIGHT)break;
		list.push_back(glm::ivec3(i,j,k));
		if(tx<=ty&&tx<=tz){
			//if(i==iend)break;
			tx+=deltax;
			i+=di;
			normal=glm::vec3(deltax,0,0);

			//if(di==1)sampler.movePositiveX();
			//if(di==-1)sampler.moveNegativeX();
		}else if(ty<=tz){
			//if(j==jend)break;
			ty+=deltay;
			j+=dj;
			normal=glm::vec3(0,deltay,0);

			//if(dj==1)sampler.movePositiveY();
			//if(dj==-1)sampler.moveNegativeY();
		}else{
			//if(k==kend)break;
			tz+=deltaz;
			k+=dk;
			normal=glm::vec3(0,0,deltaz);

			//if(dk==1)sampler.movePositiveZ();
			//if(dk==-1)sampler.moveNegativeZ();
		}
	}

	for(unsigned int i=1;i<list.size();i++){//Start at 1, so that when retrieving previous block list[i-1] we stay inside the array
		if(!getBlock(list[i]).empty){
//			printf("Intersection at %i,%i,%i   ",list[i].x,list[i].y,list[i].z);
			Intersection inters(list[i],list[i-1],normal);
			inters.dist=i;
			return inters;
		}
	}
//	Block camBlock=getBlock(start);
//	if(!camBlock.empty)printf("CAMERA INSIDE TERRAIN\n");

//	start+=dir;
//
//	float x=floor(start.x);
//	float y=floor(start.y);
//	float z=floor(start.z);
//
//	float dx=dir.x;
//	float dy=dir.y;
//	float dz=dir.z;
//
//	float stepX=sign(dx);
//	float stepY=sign(dy);
//	float stepZ=sign(dz);
//
//	float tMaxX=intbound(start.x,dx);
//	float tMaxY=intbound(start.y,dy);
//	float tMaxZ=intbound(start.z,dz);
//
//	float tDeltaX=stepX/dx;
//	float tDeltaY=stepY/dy;
//	float tDeltaZ=stepZ/dz;
//
//	std::vector<glm::ivec3>blocks;
//
//	for(int i=0;i<range;i++){
//		if(tMaxX<tMaxY){
//			if(tMaxX<tMaxZ){
//				x+=stepX;
//				tMaxX+=tDeltaX;
//				//normal of this face is -1,0,0
//			}else{
//				z+=stepZ;
//				tMaxZ+=tDeltaZ;
//				//normal of this face is 0,0,-1
//			}
//		}else{
//			if(tMaxY<tMaxZ){
//				y+=stepY;
//				tMaxY+=tDeltaY;
//				//normal of this face is 0,-1,0
//			}else{
//				z+=stepZ;
//				tMaxZ+=tDeltaZ;
//				//normal of this face is 0,0,-1
//			}
//		}
//		blocks.push_back(glm::ivec3(x,y,z));
//	}
//
//	for(glm::ivec3 p:blocks){
//		if(!getBlock(p).empty)return Intersection(p);
//	}

	Intersection inters(false);
	inters.dist=range;
	return inters;
}
