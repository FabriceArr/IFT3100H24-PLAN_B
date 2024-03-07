#pragma once 

#include "ofMain.h"
#include "Object.h"
#include "ofVbo.h"


enum class VectorPrimitiveType
{
	none,
	point,
	ligne,
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
	int stroke_width;
	ofColor stroke_color;
	ofColor fill_color;
};



class Element2DPrimitive : public Object
{
private:
	VectorPrimitive shape;

public:
	
	Element2DPrimitive(string name, ofColor fill_color, ofColor stroke_color, int stroke_width, ofVec3f point1, ofVec3f point2, ofVec3f point3, ofVec3f radius);
	~Element2DPrimitive();

	void drawVectorPoint(const glm::vec3& position);
	void drawVectorLine(const glm::vec3& start, const glm::vec3& end);
	void drawVectorEllipse(const glm::vec3& position, float radiusX, float radiusY);
	void drawVectorTriangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
	void drawVectorRect(const glm::vec3& position, float width, float height);

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);

};