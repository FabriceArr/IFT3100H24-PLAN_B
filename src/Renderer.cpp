#include "ofMain.h"
#include "Renderer.h"

void Renderer::setup(Scene* sce, ofEasyCam* camref)
{
	//ofHideCursor();

	ofSetFrameRate(60);
	ofDisableArbTex();
	ofSetBackgroundColor(backgroundColor);
	ofEnableLighting();

	ofBackground(backgroundColor);
	scene = sce;

	saveNumber = 1;

	skybox.setup();
	ofLog() << "Shader1; " << raytracing_scene.setupShaderFromFile(GL_VERTEX_SHADER, "raytracingscene/ray_tracing_scene.vert");
	ofLog() << "Shader4; " << raytracing_scene.setupShaderFromFile(GL_FRAGMENT_SHADER, "raytracingscene/ray_tracing_scene.frag");
	ofLog() << "Shader5; " << raytracing_scene.linkProgram();
	cam = camref;
}

void Renderer::draw()
{
	clear();

	scene->draw();
	raytracing_scene.begin();
	raytracing_scene.setUniform3f("CameraPos", cam->getGlobalPosition());
	ofVec3f i = cam->getGlobalPosition();
	glm::quat j = cam->getGlobalOrientation();
	ofBox(ofVec3f(0.0), 100);
	raytracing_scene.end();
	
	skybox.draw();
	
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