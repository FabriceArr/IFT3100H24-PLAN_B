#include "Skybox.h"
#include "ofMain.h"

Skybox::Skybox()
{
	
	myCubeMap.loadImages(
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	);

	myCubeMap.bind();

	cubeMapShader.begin();
	cubeMapShader.setUniform1i("EnvMap", 0);

	myCubeMap.drawSkybox(800);

	cubeMapShader.end();

	myCubeMap.unbind();

	myFboCubeMap.initEmptyTextures(512);

	myFboCubeMap.setPosition(0.0f, 40.0f, 0.0f);

	for (int i = 0; i < 6; i++)
	{
		myFboCubeMap.beginDrawingInto3D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

		ofClear(0, 0, 0);
		draw();

		myFboCubeMap.endDrawingInto3D();
	}
}

Skybox::~Skybox()
{
}

void Skybox::draw()
{
	
}

