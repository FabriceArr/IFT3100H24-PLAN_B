#pragma once
#include "ofMain.h"
#include <GLFW/glfw3.h>

class Skybox
{
private:
	ofCubeMap cubemap;

	void loadCubemap(std::string path);

public:
	Skybox();

	

	void setup();
	void draw();
};

