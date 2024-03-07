#pragma once
#include "Scene.h"

class Renderer
{
private:

	Scene* scene;
	//ofCamera* cam;
	ofMatrix4x4 viewM, projectM;

	const float cursorLength = 10.0f;
	const float cursorOffset = 5.0f;
	float cursorSubOffset = 5.0f;

	bool has_changed;

	
	int buffer_count;
	int buffer_head;
	int buffer_stride;
	int buffer_size;
	int index;
	
	float stroke_width_default;
	ofColor clear_color;


	void updateCamMatrixes();
public:
	ofImage imageImport;

	int mouse_press_x;
	int mouse_press_y;
	int mouse_release_x;
	int mouse_release_y;

	bool mouse_pressed;
	bool mouse_released;

	int mouse_button;
	int mouse_release_button;

	int mouse_current_x;
	int mouse_current_y;

	bool isCursorVisible;
	bool isSelectable;

	ofColor strokecolor;
	ofColor fillcolor;
	ofColor backgroundColor;

	int stroke_weight;

	int saveNumber;

	void setup(Scene* sce);
	void draw();
	
	void draw_cursor(float x, float y) const;
	void clear() const;
	void update();

	void exit();

	void image_export(const string name, const string extension);

};


