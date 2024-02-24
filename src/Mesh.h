#pragma once
#include "ofMain.h"



class mesh
{
private:
	ofVbo vbo;
	ofVboMesh mesh;
public:
	
	void init();

	void draw();
};

