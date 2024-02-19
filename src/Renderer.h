#pragma once
#include "Scene.h"

enum class VectorPrimitiveType
{
	// Add your primitive types here
	none,
	point,
	line,
	rectangle,
	ellipse,
	triangle
};

struct VectorPrimitive
{
	VectorPrimitiveType type;
	glm::vec3 position1;
	glm::vec3 position2;
	glm::vec3 position3;
	float radiusx;
	float radiusy;
	float stroke_width;
	ofColor stroke_color;
	ofColor fill_color;
};

class Renderer
{
private:

	Scene* scene;
	ofCamera* cam;
	ofMatrix4x4 viewM, projectM;

	
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

	float radius;

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

	unsigned char stroke_color_r;
	unsigned char stroke_color_g;
	unsigned char stroke_color_b;
	unsigned char stroke_color_a;

	unsigned char fill_color_r;
	unsigned char fill_color_g;
	unsigned char fill_color_b;
	unsigned char fill_color_a;

	ofColor stroke_color;
	ofColor fill_color;
	float stroke_weight;

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

	void createObject(int type, const glm::vec3 cameraAngle);
	void removeLastShape();

	void color_stroke();
	void color_fill();
	void setStrokeWidth(float strokeWidth);
};


