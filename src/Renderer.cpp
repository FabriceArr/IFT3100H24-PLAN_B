#include "ofMain.h"
#include "Renderer.h"



void Renderer::setup(Scene* sce)
{

	mouse_release_button = mouse_button = 10; // set mouse button to none
	cursorSubOffset += cursorOffset;

	//ofHideCursor();

	ofSetFrameRate(60);

	ofSetBackgroundColor(backgroundColor);

	ofBackground(backgroundColor);
	scene = sce;

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

	//this->cam = cam;

	saveNumber = 1;
	//imageImport.allocate(0,0,OF_IMAGE_COLOR);
}

void Renderer::draw()
{
	clear();

	scene->draw();

}

void Renderer::update()
{
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par dÃ©faut
void Renderer::clear() const
{
	ofBackground(backgroundColor);
}

void Renderer::exit()
{
	//make scene destructor first
	//delete scene;
}
/*
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


}*/

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::image_export(const string name, const string extension)	
{
	ofImage imageExport;

	string file_name = name + "_" + to_string(saveNumber) + "." + extension;
	imageExport.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageExport.save(file_name);
	ofLog() << "<export image: " << file_name << ">";

}