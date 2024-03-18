#pragma once
#include "Scene.h"

class Renderer
{
private:

	Scene* scene;
	ofMatrix4x4 viewM, projectM;

	ofShader shader;

	bool has_changed;

	
	int buffer_count;
	int buffer_head;
	int buffer_stride;
	int buffer_size;
	int index;
	
	float stroke_width_default;
	ofColor clear_color;


	//void updateCamMatrixes();
public:
	ofImage imageImport;


	ofColor strokecolor;
	ofColor fillcolor;
	ofColor backgroundColor;

	int stroke_weight;
	
	int saveNumber;

	void setup(Scene* sce);
	void draw();
	
	void clear() const;
	void update();

	void exit();

	void image_export(const string name, const string extension);

};


