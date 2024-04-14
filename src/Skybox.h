#pragma once
#include "ofMain.h"
#include "ofxCubeMap.h"

class Skybox
{
	private:
		ofxCubeMap myCubeMap;
		ofShader cubeMapShader;
		ofxCubeMap myFboCubeMap;
		

	public:
	Skybox();
	~Skybox();
	void draw();
};