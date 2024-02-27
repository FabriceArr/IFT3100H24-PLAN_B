#include "ofMain.h"
#include "Renderer.h"



void Renderer::setup(Scene* sce)
{
	// Initialisation du vecteur
	shapes.clear(); // Assurez-vous que le vecteur est vide au début
	shapes.reserve(100); // Réservez de l'espace pour 100 éléments si nécessaire

	mouse_release_button = mouse_button = 10; // set mouse button to none
	cursorSubOffset += cursorOffset;

	//ofHideCursor();

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
	//this->cam = cam;

	saveNumber = 1;
	//imageImport.allocate(0,0,OF_IMAGE_COLOR);
}

void Renderer::draw()
{
	clear();

	ofPushMatrix();

	ofSetColor(255);

	scene->draw();

	// Draw based on the draw_mode
	 // Draw all shapes in the vector
	for (const auto& shape : shapes)
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
			ofSetCircleResolution(48);
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

		default:
			// Draw nothing if type is not recognized
			break;
		}
	}

	ofPopMatrix();
}

void Renderer::add_vector_shape(VectorPrimitiveType type, float x1, float y1, float x2, float y2, float x3, float y3, float radiusx, float radiusy)
{
	VectorPrimitive newShape;
	newShape.type = type;

	newShape.position1[0] = x1;
	newShape.position1[1] = y1;

	newShape.position2[0] = x2;
	newShape.position2[1] = y2;

	newShape.position3[0] = x3;
	newShape.position3[1] = y3;

	newShape.radiusx = radiusx;
	newShape.radiusy = radiusy;


	newShape.stroke_color = strokecolor;
	newShape.fill_color = fillcolor;
	newShape.stroke_width = stroke_weight;

	switch (newShape.type)
	{

	case VectorPrimitiveType::point:
		break;

	case VectorPrimitiveType::line:
		break;

	case VectorPrimitiveType::rectangle:
		break;

	case VectorPrimitiveType::ellipse:
		break;

	case VectorPrimitiveType::triangle:
		break;

	default:
		break;
	}

	ofLog() << "<new primitive at index: " << shapes.size() << ">";

	// Add the new primitive directly to the vector
	shapes.push_back(newShape);
}


// Implementation of drawVectorPoint function
void Renderer::drawVectorPoint(const glm::vec3& position)
{
	ofDrawCircle(position.x, position.y, 20);
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
	ofSetColor(strokecolor);
	ofSetColor(fillcolor);
	ofSetLineWidth(stroke_weight);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par dÃ©faut
void Renderer::clear() const
{
	ofBackground(clear_color);
}

void Renderer::exit()
{
	//make scene destructor first
	//delete scene;
}

void Renderer::draw_cursor(float x, float y) const
{

	ofSetLineWidth(2);
	if (mouse_button == 0)
	{
		// left mouse button pressed down
		ofSetColor(255);

		ofDrawLine(x - cursorOffset - cursorLength, y - cursorOffset - cursorLength, x - cursorOffset, y - cursorOffset); //TL
		ofDrawLine(x - cursorOffset - cursorLength, y + cursorOffset + cursorLength, x - cursorOffset, y + cursorOffset); //BL
		ofDrawLine(x + cursorOffset + cursorLength, y - cursorOffset - cursorLength, x + cursorOffset, y - cursorOffset); // TR
		ofDrawLine(x + cursorOffset + cursorLength, y + cursorOffset + cursorLength, x + cursorOffset, y + cursorOffset); // BR

	}
	else		// no mouse button pressed

	{
		// if hovering above selecable object
		ofSetColor(isSelectable ? 256: 31 );

		ofDrawLine(x + cursorOffset, y, x + cursorOffset + cursorLength, y);
		ofDrawLine(x - cursorOffset, y, x - cursorOffset - cursorLength, y);
		ofDrawLine(x, y + cursorOffset, x, y + cursorOffset + cursorLength);
		ofDrawLine(x, y - cursorOffset, x, y - cursorOffset - cursorLength);

	}
	switch (draw_mode)
	{
	case VectorPrimitiveType::point:
		ofFill();
		ofDrawCircle(x + cursorSubOffset, y - cursorSubOffset, cursorLength / 5);
		break;

	case VectorPrimitiveType::line:
		ofDrawLine(	x + cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset, //TL
					x - cursorLength / 2 + cursorSubOffset, y + cursorLength / 2 - cursorSubOffset);//BR
		break;

	case VectorPrimitiveType::rectangle:
		ofNoFill();
		ofDrawRectangle(glm::vec2(x + 2*cursorSubOffset, y - 2*cursorSubOffset),
			-cursorSubOffset, cursorSubOffset);

		break;

	case VectorPrimitiveType::ellipse:
		ofNoFill();
		ofDrawCircle(x + cursorSubOffset, y - cursorSubOffset, cursorLength /2);
		break;

	case VectorPrimitiveType::triangle:
		ofNoFill();
		ofDrawTriangle(
			x + cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset,	 //TR
			x - cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset,	 //TL
			x + cursorSubOffset, y + cursorLength / 2 - cursorSubOffset); //B

		break;

	case VectorPrimitiveType::image:
		imageImport.draw(imageImport.getWidth() / -2, 0);
		break;

	default:
		break;
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

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::image_export(const string name, const string extension)	
{
	ofImage imageExport;

	string file_name = name + "_" + to_string(saveNumber) + "." + extension;
	imageExport.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageExport.save(file_name);
	ofLog() << "<export image: " << file_name << ">";

}
