#include "ofMain.h"
#include "Renderer.h"

void Renderer::setup(Scene* sce)
{
	//ofHideCursor();

	ofSetFrameRate(60);
	ofDisableArbTex();
	ofSetBackgroundColor(backgroundColor);

	ofBackground(backgroundColor);
	scene = sce;

	saveNumber = 1;
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

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::image_export(const string name, const string extension)	
{
	ofImage imageExport;

	string file_name = name + "_" + to_string(saveNumber) + "." + extension;
	imageExport.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageExport.save(file_name);
	ofLog() << "<export image: " << file_name << ">";

}