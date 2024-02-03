#include "ofMain.h"
#include "Renderer.h"


void Renderer::setup()
{
	ofSetFrameRate(60);

	clear_color.r = 128;
	clear_color.g = 128;
	clear_color.b = 128;

	ofSetBackgroundAuto(true);

	ofSetBackgroundColor(clear_color);

	ofSetBackgroundAuto(false);

	ofSetBackgroundColor(clear_color);

	ofBackground(clear_color);

	

}

void Renderer::draw()
{
	clear();
	
	ofPushMatrix();

	ofDrawGrid(100, 12, false, false, true, false);

	for (std::vector<Object>::const_iterator it = scene.getSceneContent()->begin()
		; it != scene.getSceneContent()->end(); it++)
	{
		ofLog() << "one drawn";
		it->object.draw();
	}


	ofPopMatrix();
	
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
void Renderer::clear() const
{
	ofBackground(clear_color);
}

void Renderer::createObject(int type, const glm::vec3 cameraAngle)
{
		scene.createObject(type, cameraAngle);
	
}

