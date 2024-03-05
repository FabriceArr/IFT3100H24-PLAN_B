#include "Element2DPrimitive.h"
/*
Element2DPrimitive::Element2D(string name, ofColor fill_color, ofColor stroke_color, int stroke_width) : Object(primitivetype)
{
	if (primitivetype == "triangle") {
		add_vector_shape(VectorPrimitiveType::triangle, 0, 0, 0, 1, 1, 0, 0, 0);
	}
	else if (primitivetype == "rectangle") {
		add_vector_shape(VectorPrimitiveType::rectangle, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "ellipse") {
		add_vector_shape(VectorPrimitiveType::ellipse, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "line") {
		add_vector_shape(VectorPrimitiveType::line, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "point") {
		add_vector_shape(VectorPrimitiveType::point, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

Element2DPrimitive::~Element2DPrimitive()
{
}

void Element2D::draw()
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
								glm::vec3(shape.position3[0]))
		}
}*/