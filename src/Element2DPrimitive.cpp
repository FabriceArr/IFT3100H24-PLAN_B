#include "Element2DPrimitive.h"

Element2DPrimitive::Element2DPrimitive(string primitivetype, ofColor fill_color, ofColor stroke_color, int stroke_width, ofVec3f point1, ofVec3f point2, ofVec3f point3, ofVec3f radius) : Object(primitivetype)
{
    shape.fill_color = fill_color;
    shape.stroke_color = stroke_color;
    shape.stroke_width = stroke_width;
    shape.position1 = point1;
    shape.position2 = point2;
    shape.position3 = point3;
    shape.radiusx = radius.x;
    shape.radiusy = radius.y;
   

	if (primitivetype == "triangle") {
        shape.type = VectorPrimitiveType::triangle;
        setUp3PointBox(shape.position1, shape.position2, shape.position3);

	}
	else if (primitivetype == "rectangle") {
        shape.type = VectorPrimitiveType::rectangle;
        setUp2PointBox(shape.position1, shape.position2);
	}
	else if (primitivetype == "ellipse") {
        shape.type = VectorPrimitiveType::ellipse;
        setUpCircleBox(shape.position1, shape.radiusx, shape.radiusy);
	}
	else if (primitivetype == "ligne") {
        shape.type = VectorPrimitiveType::ligne;
        setUp2PointBox(shape.position1, shape.position2);
	}
	else if (primitivetype == "point") {
        shape.type = VectorPrimitiveType::point;
        setUpCircleBox(shape.position1, shape.stroke_width, shape.stroke_width);
	}
    else {
        shape.type = VectorPrimitiveType::none;
	}
}

Element2DPrimitive::~Element2DPrimitive()
{
}

void Element2DPrimitive::draw(bool highlight, bool animated, unsigned int substage)
{
    if (highlight) {
        updateShapeData();
    }

    switch (shape.type)
    {
    case VectorPrimitiveType::point:
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(shape.stroke_color);
        drawVectorPoint(glm::vec3(shape.position1[0], shape.position1[1], 0));
        break;

    case VectorPrimitiveType::ligne:
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
        ofSetLineWidth(this->getStrokeWidth());
        ofSetColor(this->getStrokeColor());
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
        ofNoFill();
        ofSetLineWidth(shape.stroke_width);
        ofSetColor(shape.stroke_color);
        drawVectorTriangle(glm::vec3(shape.position1[0], shape.position1[1], 0),
            glm::vec3(shape.position2[0], shape.position2[1], 0),
            glm::vec3(shape.position3[0], shape.position3[1], 0));
        break;
    }

    draw_selectSquare(highlight);
}

void Element2DPrimitive::updateShapeData()
{
    shape.fill_color = this->getColor();
    shape.stroke_color = this->getStrokeColor();
    shape.stroke_width = this->getStrokeWidth();
}

void Element2DPrimitive::setUp2PointBox(ofVec3f p1, ofVec3f p2)
{
    float max_x, min_x, max_y, min_y;

    min_x = min(p1.x, p2.x);
    max_x = max(p1.x, p2.x);

    min_y = min(p1.y, p2.y);
    max_y = max(p1.y, p2.y);

    ofVec3f square_vertices_custom[] =
    {
        ofVec3f(min_x ,  max_y, 0),//0
        ofVec3f(max_x , max_y, 0),//1
        ofVec3f(min_x , min_y,  0),//2
        ofVec3f(max_x , min_y, 0),//3
    };


    GLuint square_vertices_ids[] =
    {
        0, 1,
        1, 3,
        3, 2,
        2, 0
    };

    this->select_Square.setVertexData(&square_vertices_custom[0], 4, GL_STATIC_DRAW);
    this->select_Square.setIndexData(&square_vertices_ids[0], 8, GL_STATIC_DRAW);

}

void Element2DPrimitive::setUp3PointBox(ofVec3f p1, ofVec3f p2, ofVec3f p3)
{
    float max_x, min_x, max_y, min_y;

    min_x = min({ p1.x, p2.x, p3.x });
    max_x = max({ p1.x, p2.x, p3.x });

    min_y = min({ p1.y, p2.y, p3.y });
    max_y = max({p1.y, p2.y, p3.y});

    ofVec3f square_vertices_custom[] =
    {
        ofVec3f(min_x ,  max_y, 0),//0
        ofVec3f(max_x , max_y, 0),//1
        ofVec3f(min_x , min_y,  0),//2
        ofVec3f(max_x , min_y, 0),//3
    };


    GLuint square_vertices_ids[] =
    {
        0, 1,
        1, 3,
        3, 2,
        2, 0
    };
    

    this->select_Square.setVertexData(&square_vertices_custom[0], 4, GL_STATIC_DRAW);
    this->select_Square.setIndexData(&square_vertices_ids[0], 8, GL_STATIC_DRAW);

}

void Element2DPrimitive::setUpCircleBox(ofVec3f p1, float w, float h)
{
    ofVec3f square_vertices_custom[] =
    {
        ofVec3f(p1.x - (w / 2), p1.y + (h / 2), 0),//0
        ofVec3f(p1.x + (w / 2), p1.x + (h / 2), 0),//1
        ofVec3f(p1.x - (w / 2), p1.x - (h / 2),  0),//2
        ofVec3f(p1.x + (w / 2), p1.x - (h / 2), 0),//3
    };


    GLuint square_vertices_ids[] =
    {
        0, 1,
        1, 3,
        3, 2,
        2, 0
    };


    this->select_Square.setVertexData(&square_vertices_custom[0], 4, GL_STATIC_DRAW);
    this->select_Square.setIndexData(&square_vertices_ids[0], 8, GL_STATIC_DRAW);

}

void Element2DPrimitive::draw_selectSquare(bool select)
{
    if (select) {
        //draw the box
        ofBeginShape();

        ofSetColor(232, 247, 14);
        glPointSize(5);
        select_Square.draw(GL_POINTS, 0, 8);
        glPointSize(0);
        ofSetColor(233, 15, 233);

        glLineWidth(5);
        select_Square.drawElements(GL_LINES, select_Square.getNumIndices());
        glLineWidth(0);
        ofSetColor(255);

        ofEndShape();
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