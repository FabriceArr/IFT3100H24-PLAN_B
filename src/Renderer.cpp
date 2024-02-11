#include "ofMain.h"
#include "Renderer.h"


void Renderer::setup(Scene* sce)
{
	// Initialisation du vecteur
	shapes.clear(); // Assurez-vous que le vecteur est vide au début
	shapes.reserve(100); // Réservez de l'espace pour 100 éléments si nécessaire

	mouse_button = 10; // set mouse button to none

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
			drawVectorPoint(glm::vec3(shape.position1[0], shape.position1[1], 0));
			break;

		case VectorPrimitiveType::line:
			drawVectorLine(glm::vec3(shape.position1[0], shape.position1[1], 0),
				glm::vec3(shape.position2[0], shape.position2[1], 0));
			break;

		case VectorPrimitiveType::rectangle:
			drawVectorRect(glm::vec3(shape.position1[0], shape.position1[1], 0),
				shape.position2[0] - shape.position1[0], shape.position2[1] - shape.position1[1]);
			break;

		case VectorPrimitiveType::ellipse:
			drawVectorEllipse(glm::vec3(shape.position1[0], shape.position1[1], 0),
				shape.position2[0], shape.position2[1]);
			break;

		case VectorPrimitiveType::triangle:
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

	//CursorVisible();
	//draw_cursor(mouse_current_x, mouse_current_y);
}

void Renderer::add_vector_shape(VectorPrimitiveType type)
{
	VectorPrimitive newShape;
	newShape.type = type;

	newShape.position1[0] = mouse_press_x;
	newShape.position1[1] = mouse_press_y;

	newShape.position2[0] = mouse_current_x;
	newShape.position2[1] = mouse_current_y;

	switch (newShape.type)
	{
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
		newShape.position3 = glm::vec3(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0);
		newShape.stroke_width = ofRandom(1, 16);
		break;

	default:
		newShape.stroke_width = stroke_width_default;
		break;
	}

	ofLog() << "<new primitive at index: " << shapes.size() << ">";

	// Ajoutez la nouvelle primitive directement au vecteur
	shapes.push_back(newShape);
}

// Implementation of drawVectorPoint function
void Renderer::drawVectorPoint(const glm::vec3& position)
{
	ofDrawSphere(position.x, position.y, position.z, 5);
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
	cursorVisible();
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
void Renderer::clear()
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


	if (isCursorVisible)
	{
		//ofLog() << "cursor is visible? " << isCursorVisible;
		ofHideCursor();
	}
	
		ofSetLineWidth(2);
		if (mouse_button == 0)
		{
			// left mouse button pressed down
			ofSetColor(255);

			ofDrawLine(x + offset, y, x + offset + length, y);
			ofDrawLine(x - offset, y, x - offset - length, y);
			ofDrawLine(x, y + offset, x, y + offset + length);
			ofDrawLine(x, y - offset, x, y - offset - length);
		}
		else
		{
			// no mouse button pressed
			ofSetColor(31);
			ofDrawLine(x + offset, y, x + offset + length, y);
			ofDrawLine(x - offset, y, x - offset - length, y);
			ofDrawLine(x, y + offset, x, y + offset + length);
			ofDrawLine(x, y - offset, x, y - offset - length);

		}
	
}

void Renderer::cursorVisible()
{
	if (mouse_current_x <= ofGetWindowWidth() )
		isCursorVisible = true;
		
	if (mouse_current_y <= ofGetWindowHeight())
		isCursorVisible = true;

	isCursorVisible = false;
	//ofLog() << "cursor not visible";
}
