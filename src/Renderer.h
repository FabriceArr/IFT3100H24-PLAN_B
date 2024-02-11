#pragma once
#include "Scene.h"


class Renderer
{
private:

	ofColor clear_color;
	Scene* scene;
	ofNode node;

	bool has_changed;
public:

	int mouse_press_x;
	int mouse_press_y;

	int mouse_button;

	int mouse_current_x;
	int mouse_current_y;

	bool isCursorVisible;
	bool isSelectable;

	void setup(Scene* sce);
	void draw();
	void update();
	void draw_cursor(float x, float y) const;
	void clear() const;

	void createObject(int type, const glm::vec3 cameraAngle);
};


