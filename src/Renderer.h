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
	float stroke_width;
	ofColor stroke_color;
	ofColor fill_color;
};

class Renderer
{
private:

	Scene* scene;
	ofNode node;

	bool has_changed;

	
	int buffer_count;
	int buffer_head;
	int buffer_stride;
	int buffer_size;
	int index;
	
	float stroke_width_default;
	ofColor clear_color;

public:
	std::vector<VectorPrimitive> shapes;
	VectorPrimitiveType draw_mode;

	float radius;

	int mouse_press_x;
	int mouse_press_y;

	int mouse_button;

	int mouse_current_x;
	int mouse_current_y;

	bool isCursorVisible;
	bool isSelectable;

	void setup(Scene* sce);
	void draw();
	void drawVectorPoint(const glm::vec3& position);
	void drawVectorLine(const glm::vec3& start, const glm::vec3& end);
	void drawVectorRect(const glm::vec3& position, float width, float height);
	void drawVectorEllipse(const glm::vec3& position, float radiusX, float radiusY);
	void drawVectorTriangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
	void update();
	void add_vector_shape(VectorPrimitiveType type);
	void draw_cursor(float x, float y) const;
	void cursorVisible();
	void clear() const;

	void createObject(int type, const glm::vec3 cameraAngle);
	void removeLastShape();
};


