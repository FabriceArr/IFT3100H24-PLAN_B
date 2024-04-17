#pragma once
#include "ofMain.h"
#include "ofxSkyBox.h"
#include "Scene.h"

class Skybox
{
	private:
		ofxSkyBox skybox;
		ofEasyCam camera;
		ofVec3f sphereCenter;
		

	public:
	Skybox();
	~Skybox();
	void draw();
};