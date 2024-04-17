#include "Skybox.h"
#include "ofMain.h"

Skybox::Skybox()
{
	/*myCubeMap.loadImages(
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	);

	myCubeMap.bind();
	myCubeMap.drawSkybox(800);
	myCubeMap.unbind();

	myFboCubeMap.initEmptyTextures(512);

	myFboCubeMap.setPosition(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 6; i++)
	{
		myFboCubeMap.beginDrawingInto3D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

		ofClear(0, 0, 0);

		myFboCubeMap.endDrawingInto3D();
	}*/
}

Skybox::~Skybox()
{
}

void Skybox::draw()
{
}
