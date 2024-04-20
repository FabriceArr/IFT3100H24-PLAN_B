#pragma once
#include "ofMain.h"
#include <GLFW/glfw3.h>

class Skybox
{
private:
	ofShader skybox;
	ofCubeMap cubemap;

	void loadCubemap(std::string path);

	unsigned int skyboxVAO, skyboxVBO;
public:
	Skybox();

	

	void setup();
	void draw();
};

