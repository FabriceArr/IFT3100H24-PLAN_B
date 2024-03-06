#include "Element2DPrimitive.h"

Element2DPrimitive::Element2DPrimitive(string primitivetype, ofColor fill_color, ofColor stroke_color, int stroke_width) : Object(primitivetype)
{
    VectorPrimitive newShape;

    newShape.fill_color = fill_color;
    newShape.stroke_color = stroke_color;
    newShape.stroke_width = stroke_width;
   

	if (primitivetype == "triangle") {
        newShape.type = VectorPrimitiveType::triangle;
	}
	else if (primitivetype == "rectangle") {
        newShape.type = VectorPrimitiveType::rectangle;
	}
	else if (primitivetype == "ellipse") {
        newShape.type = VectorPrimitiveType::ellipse;
	}
	else if (primitivetype == "line") {
        newShape.type = VectorPrimitiveType::line;
	}
	else if (primitivetype == "point") {
        newShape.type = VectorPrimitiveType::point;
	}
    else {
        newShape.type = VectorPrimitiveType::none;
	}
    
	shape = newShape;
}

Element2DPrimitive::~Element2DPrimitive()
{
}

void Element2DPrimitive::draw(bool highlight, bool animated)
{
    switch (shape.type)
    {
    case VectorPrimitiveType::point:
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(shape.stroke_color);
        drawVectorPoint(glm::vec3(shape.position1[0], shape.position1[1], 0));
        break;

    case VectorPrimitiveType::line:
        ofNoFill();
        ofSetLineWidth(shape.stroke_width);
        ofSetColor(shape.stroke_color);
        drawVectorLine(glm::vec3(shape.position1[0], shape.position1[1], 0),
            glm::vec3(shape.position2[0], shape.position2[1], 0));
        break;

    case VectorPrimitiveType::rectangle:
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(shape.fill_color);
        drawVectorRect(glm::vec3(shape.position1[0], shape.position1[1], 0),
            shape.position2[0] - shape.position1[0], shape.position2[1] - shape.position1[1]);
        ofNoFill();
        ofSetLineWidth(shape.stroke_width);
        ofSetColor(shape.stroke_color);
        drawVectorRect(glm::vec3(shape.position1[0], shape.position1[1], 0),
            shape.position2[0] - shape.position1[0], shape.position2[1] - shape.position1[1]);
        break;

    case VectorPrimitiveType::ellipse:
        ofFill();
        ofSetLineWidth(0);
        ofSetCircleResolution(48);
        ofSetColor(shape.fill_color);
        drawVectorEllipse(glm::vec3(shape.position1[0], shape.position1[1], 0),
            shape.radiusx, shape.radiusy);
        ofNoFill();
        ofSetLineWidth(shape.stroke_width);
        ofSetColor(shape.stroke_color);
        drawVectorEllipse(glm::vec3(shape.position1[0], shape.position1[1], 0),
            shape.radiusx, shape.radiusy);
        break;

    case VectorPrimitiveType::triangle:
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(shape.fill_color);
        drawVectorTriangle(glm::vec3(shape.position1[0], shape.position1[1], 0),
            glm::vec3(shape.position2[0], shape.position2[1], 0),
            glm::vec3(shape.position3[0], shape.position3[1], 0));
        break;
    }
}

// Implementation of drawVectorPoint function
void Element2DPrimitive::drawVectorPoint(const glm::vec3& position)
{
    ofDrawCircle(position.x, position.y, 20);
}

// Implementation of drawVectorLine function
void Element2DPrimitive::drawVectorLine(const glm::vec3& start, const glm::vec3& end)
{
    ofDrawLine(start.x, start.y, start.z, end.x, end.y, end.z);
}

// Implementation of drawVectorRect function
void Element2DPrimitive::drawVectorRect(const glm::vec3& position, float width, float height)
{
    ofDrawRectangle(position.x, position.y, position.z, width, height);
}

// Implementation of drawVectorEllipse function
void Element2DPrimitive::drawVectorEllipse(const glm::vec3& position, float radiusX, float radiusY)
{
    ofDrawEllipse(position.x, position.y, position.z, radiusX, radiusY);
}

// Implementation of drawVectorTriangle function
void Element2DPrimitive::drawVectorTriangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
{
    ofDrawTriangle(point1.x, point1.y, point1.z, point2.x, point2.y, point2.z, point3.x, point3.y, point3.z);
}