#include "ofMain.h"
#include "Renderer.h"


void Renderer::setup(Scene* sce)
{
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
	

}

void Renderer::draw()
{
	clear();
	scene->draw();
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

