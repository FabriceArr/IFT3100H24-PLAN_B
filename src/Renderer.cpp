#include "ofMain.h"
#include "Renderer.h"


void Renderer::setup(Scene* sce)
{
	// Initialisation du vecteur
	shapes.clear(); // Assurez-vous que le vecteur est vide au début
	shapes.reserve(100); // Réservez de l'espace pour 100 éléments si nécessaire

	mouse_button = 10; // set mouse button to none

	ofHideCursor();

	ofSetFrameRate(60);

	clear_color.r = 128;
	clear_color.g = 128;
	clear_color.b = 128;

	ofSetBackgroundAuto(true);

	ofSetBackgroundColor(clear_color);

	ofSetBackgroundAuto(false);

	ofSetBackgroundColor(clear_color);

	ofBackground(clear_color);
	scene = sce;

	// largeur de la ligne de contour
	stroke_width_default = 2;

	// couleur de la ligne de contour
	color_stroke();

	// couleur de la zone de remplissage
	color_fill();


	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

	radius = 4.0f;
}

void Renderer::draw()
{
	clear();

	ofPushMatrix();

	ofDrawGrid(100, 12, false, false, true, false);
	std::vector<Object*>::const_iterator it = scene->getSceneContent()->begin();

	for (std::vector<Object*>::const_iterator it = 
		scene->getSceneContent()->begin(); it !=
		scene->getSceneContent()->end(); it++)
	{
		ofLog() << "one drawn";
		if (*it) {
			(*it)->getObject()->draw();
		}
		
	}

	ofSetColor(255);


	// Draw based on the draw_mode
	 // Draw all shapes in the vector
	for (const auto& shape : shapes)
	{
		switch (shape.type)
		{
		case VectorPrimitiveType::point:
			ofFill();
			ofSetLineWidth(0);
			ofSetColor(shape.fill_color);
			drawVectorPoint(glm::vec3(shape.position1[0], shape.position1[1], 0));
			break;

		case VectorPrimitiveType::line:
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(shape.stroke_color);
			drawVectorLine(glm::vec3(shape.position1[0], shape.position1[1], 0),
				glm::vec3(shape.position2[0], shape.position2[1], 0));
			break;

		case VectorPrimitiveType::rectangle:
			ofFill();
			ofSetLineWidth(0);
			ofSetColor( shape.fill_color);
			drawVectorRect(glm::vec3(shape.position1[0], shape.position1[1], 0),
				shape.position2[0] - shape.position1[0], shape.position2[1] - shape.position1[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
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
				shape.position2[0], shape.position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(shape.stroke_color);
			drawVectorEllipse(glm::vec3(shape.position1[0], shape.position1[1], 0),
								shape.position2[0], shape.position2[1]);
			break;

		case VectorPrimitiveType::triangle:
			ofFill();
			ofSetLineWidth(0);
			ofSetCircleResolution(48);
			ofSetColor(shape.fill_color);
			drawVectorTriangle(glm::vec3(shape.position1[0], shape.position1[1], 0),
				glm::vec3(shape.position2[0], shape.position2[1], 0),
				glm::vec3(shape.position3[0], shape.position3[1], 0));
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(shape.stroke_color);
			drawVectorTriangle(glm::vec3(shape.position1[0], shape.position1[1], 0),
								glm::vec3(shape.position2[0], shape.position2[1], 0),
								glm::vec3(shape.position3[0], shape.position3[1], 0));
			break;

		default:
			// Draw nothing if type is not recognized
			break;
		}
	}

	ofPopMatrix();
}

void Renderer::add_vector_shape(VectorPrimitiveType type)
{
	VectorPrimitive newShape;
	newShape.type = type;

	newShape.position1[0] = 0;
	newShape.position1[1] = 0;

	newShape.position2[0] = 100;  // You can adjust the width or radius as needed
	newShape.position2[1] = 100;  // You can adjust the height as needed

	newShape.stroke_color = ofColor(stroke_color_r, stroke_color_g, stroke_color_b, stroke_color_a);
	newShape.fill_color = ofColor(fill_color_r, fill_color_g, fill_color_b, fill_color_a);

	switch (newShape.type)
	{
		// Adjust stroke width or other properties as needed for each shape type

	case VectorPrimitiveType::point:
		newShape.stroke_width = ofRandom(1, 64);
		break;

	case VectorPrimitiveType::line:
		newShape.stroke_width = ofRandom(1, 16);
		break;

	case VectorPrimitiveType::rectangle:
		newShape.stroke_width = ofRandom(1, 16);
		break;

	case VectorPrimitiveType::ellipse:
		newShape.stroke_width = stroke_width_default;
		break;

	case VectorPrimitiveType::triangle:
		// Adjust properties if needed for triangles
		newShape.position3 = glm::vec3(50, 100, 0);  // Example position for the third point
		newShape.stroke_width = ofRandom(1, 16);
		break;

	default:
		newShape.stroke_width = stroke_width_default;
		break;
	}

	ofLog() << "<new primitive at index: " << shapes.size() << ">";

	// Add the new primitive directly to the vector
	shapes.push_back(newShape);
}


// Implementation of drawVectorPoint function
void Renderer::drawVectorPoint(const glm::vec3& position)
{
	ofDrawCircle(position.x, position.y, 5);
}

// Implementation of drawVectorLine function
void Renderer::drawVectorLine(const glm::vec3& start, const glm::vec3& end)
{
	ofDrawLine(start.x, start.y, start.z, end.x, end.y, end.z);
}

// Implementation of drawVectorRect function
void Renderer::drawVectorRect(const glm::vec3& position, float width, float height)
{
	ofDrawRectangle(position.x, position.y, position.z, width, height);
}

// Implementation of drawVectorEllipse function
void Renderer::drawVectorEllipse(const glm::vec3& position, float radiusX, float radiusY)
{
	ofDrawEllipse(position.x, position.y, position.z, radiusX, radiusY);
}

// Implementation of drawVectorTriangle function
void Renderer::drawVectorTriangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
{
	ofDrawTriangle(point1.x, point1.y, point1.z, point2.x, point2.y, point2.z, point3.x, point3.y, point3.z);
}

void Renderer::update()
{
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
void Renderer::clear() const
{
	ofBackground(clear_color);
}

void Renderer::createObject(int type, const glm::vec3 cameraAngle)
{
		scene->createObject(type, cameraAngle);
	
}

void Renderer::draw_cursor(float x, float y) const
{
	float length = 10.0f;
	float offset = 5.0f;


	ofSetLineWidth(2);
	if (mouse_button == 0)
	{
		// left mouse button pressed down
		ofSetColor(255);

		ofDrawLine(x - offset - length, y - offset - length, x - offset, y - offset); //TL
		ofDrawLine(x - offset - length, y + offset + length, x - offset, y + offset); //BL
		ofDrawLine(x + offset + length, y - offset - length, x + offset, y - offset); // TR
		ofDrawLine(x + offset + length, y + offset + length, x + offset, y + offset); // BR

	}
	else		// no mouse button pressed

	{
		// if hovering above selecable object
		ofSetColor(isSelectable ? 256: 31 );

		ofDrawLine(x + offset, y, x + offset + length, y);
		ofDrawLine(x - offset, y, x - offset - length, y);
		ofDrawLine(x, y + offset, x, y + offset + length);
		ofDrawLine(x, y - offset, x, y - offset - length);

	}

}

void Renderer::removeLastShape()
{
	if (!shapes.empty())
	{
		shapes.pop_back();
		ofLog() << "Removed last shape. Total shapes: " << shapes.size();
	}
}

void Renderer::color_stroke()
{
	stroke_color_r = (int)ofRandom(0, 255);
	stroke_color_g = (int)ofRandom(0, 255);
	stroke_color_b = (int)ofRandom(0, 255);
	stroke_color_a = 255;
}

// fonction qui d�termine une couleur al�atoire pour les zones de remplissage
void Renderer::color_fill()
{
	fill_color_r = (int)ofRandom(0, 255);
	fill_color_g = (int)ofRandom(0, 255);
	fill_color_b = (int)ofRandom(0, 255);
	fill_color_a = 255;

}

void Renderer::setStrokeWidth(float strokeWidth)
{
	stroke_weight = strokeWidth;
}