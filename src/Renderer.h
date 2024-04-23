#pragma once
#include "Scene.h"
#include "skybox.h"

class Renderer
{
private:
	ofEasyCam* cam;
	Scene* scene;
	ofMatrix4x4 viewM, projectM;

	ofShader raytracing_scene;



	bool has_changed;

	
	int buffer_count;
	int buffer_head;
	int buffer_stride;
	int buffer_size;
	int index;
	
	float stroke_width_default;
	ofColor clear_color;

	Skybox skybox;

	//void updateCamMatrixes();
public:
	ofImage imageImport;

	ofColor strokecolor;
	ofColor fillcolor;
	ofColor backgroundColor;

	int stroke_weight;
	
	int saveNumber;

	void setup(Scene* sce, ofEasyCam* cam);
	void draw();
	
	void clear() const;
	void update();

	void exit();

	void image_export(const string name, const string extension);

};


