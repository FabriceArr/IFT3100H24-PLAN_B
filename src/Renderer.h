#pragma once
#include "Scene.h"

//// énumération des types de shader
//enum class ShaderType { color_fill, lambert, gouraud, phong, blinn_phong };
//
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
	//ofLight defaultLight;
	//ofLight light;

	ofColor strokecolor;
	ofColor fillcolor;
	ofColor backgroundColor;

	//ShaderType shader_active;

	//ofShader shader_color_fill;
	//ofShader shader_lambert;
	//ofShader shader_gouraud;
	//ofShader shader_phong;
	//ofShader shader_blinn_phong;

	//ofShader* shader;

	//string shader_name;

	int stroke_weight;
	
	int saveNumber;

	void setup(Scene* sce);
	void draw();
	
	void clear() const;
	void update();

	void exit();

	void image_export(const string name, const string extension);

};


