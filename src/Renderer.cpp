#include "ofMain.h"
#include "Renderer.h"


void Renderer::setup(Scene* sce)
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
	scene = sce;
	

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


	ofPopMatrix();
	
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

