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
	std::vector<VectorPrimitive> shapes;
	VectorPrimitiveType draw_mode;
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

	int stroke_weight;

	int saveNumber;

	void setup(Scene* sce);
	void draw();
	void drawVectorPoint(const glm::vec3& position);
	void drawVectorLine(const glm::vec3& start, const glm::vec3& end);
	void drawVectorRect(const glm::vec3& position, float width, float height);
	void drawVectorEllipse(const glm::vec3& position, float radiusX, float radiusY);
	void drawVectorTriangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
	void update();
	void add_vector_shape(VectorPrimitiveType type, float x1, float y1, float x2, float y2, float x3, float y3, float radiusx, float raduisy);
	void draw_cursor(float x, float y) const;
	void clear() const;

	void exit();
	void removeLastShape();

	void image_export(const string name, const string extension);

	void Renderer::add_vector_cross(ofVec3f point1, ofVec3f point2);
	void Renderer::add_vector_house(ofVec3f point1, ofVec3f point2, ofVec3f point3);
	void Renderer::add_vector_flower(ofVec3f point1, ofVec3f radius);

};


