#pragma once 
#include "Object.h"
#include "ofVbo.h"

enum class VectorPrimitiveType
{
	// Add your primitive types here
	none,
	point,
	line,
	rectangle,
	ellipse,
	triangle,
	image
};

struct VectorPrimitive
{
	VectorPrimitiveType type;
	glm::vec3 position1;
	glm::vec3 position2;
	glm::vec3 position3;
	float radiusx;
	float radiusy;
	int stroke_width;
	ofColor stroke_color;
	ofColor fill_color;
};

class Element2DPrimitive : public Object
{
private:
public:
	std::vector<VectorPrimitive> shapes;
	Element2DPrimitive(string name, ofColor fill_color, ofColor stroke_color, int stroke_width);
	~Element2DPrimitive();

	void add_vector_shape(VectorPrimitiveType type, float x1, float y1, float x2, float y2, float x3, float y3, float radiusx, float radiusy);

	void draw(bool highlight, bool animated = false);

};