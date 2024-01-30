#pragma once
#include "Scene.h"


class Renderer
{
private:

	ofColor clear_color;
	Scene scene;
	ofNode node;

	bool has_changed;
public:

	void setup();
	void draw();

	void clear() const;

	void createObject(int type, const glm::vec3 cameraAngle);
};


