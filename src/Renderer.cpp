#include "ofMain.h"
#include "Renderer.h"

void Renderer::setup(Scene* sce)
{
	//ofHideCursor();
	
	ofSetFrameRate(60);
	ofEnableDepthTest();
	ofDisableArbTex();
	ofEnableNormalizedTexCoords();
	ofSetBackgroundColor(backgroundColor);

	ofBackground(backgroundColor);
	//defaultLight.setDirectional();

	//defaultLight.setOrientation(glm::quat(0.0f, -1.0f, 0.0f, 0.0f));
	//ofLog() << "default Light orientation: " << defaultLight.getOrientationQuat();
	
	scene = sce;

	saveNumber = 1;

	
}

void Renderer::draw()
{
	clear();

    //// activer l'éclairage dynamique
    //ofEnableLighting();

    //// activer la lumière dynamique
    //light.enable();

    //// activer le shader
    //shader->begin();

	scene->draw();

    ofPopMatrix();

    //// désactiver le shader
    //shader->end();

    //// désactiver la lumière
    //light.disable();

    //// désactiver l'éclairage dynamique
    //ofDisableLighting();

}

void Renderer::update()
{
	//defaultLight.setGlobalPosition(
	//	ofMap(ofGetMouseX() / (float)ofGetWidth(), 0.0f, 1.0f, -ofGetWidth() / 2.0f, ofGetWidth() / 2.0f),
	//	ofMap(ofGetMouseY() / (float)ofGetHeight(), 0.0f, 1.0f, -ofGetHeight() / 2.0f, ofGetHeight() / 2.0f),
	//	//-offset_z * 1.5f);
	//	1.5f);

 //   // mise à jour d'une valeur numérique animée par un oscillateur
 //   //float oscillation = oscillate(ofGetElapsedTimeMillis(), oscillation_frequency, oscillation_amplitude) + oscillation_amplitude;

 //   // passer les attributs uniformes au shader de sommets
 //   switch (shader_active)
 //   {
 //   case ShaderType::color_fill:
 //       shader_name = "Color Fill";
 //       shader = &shader_color_fill;
 //       shader->begin();
 //       shader->setUniform3f("color", 1.0f, 1.0f, 0.0f);
 //       shader->end();
 //       break;

 //   case ShaderType::lambert:
 //       shader_name = "Lambert";
 //       shader = &shader_lambert;
 //       shader->begin();
 //       shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
 //       shader->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.6f);
 //       shader->setUniform3f("light_position", light.getGlobalPosition());
 //       shader->end();
 //       break;

 //   case ShaderType::gouraud:
 //       shader_name = "Gouraud";
 //       shader = &shader_gouraud;
 //       shader->begin();
 //       shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
 //       shader->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.0f);
 //       shader->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
 //       //shader->setUniform1f("brightness", oscillation);
 //       shader->setUniform1f("brightness", 1.0f);
 //       shader->setUniform3f("light_position", light.getGlobalPosition());
 //       shader->end();
 //       break;

 //   case ShaderType::phong:
 //       shader_name = "Phong";
 //       shader = &shader_phong;
 //       shader->begin();
 //       shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
 //       shader->setUniform3f("color_diffuse", 0.6f, 0.0f, 0.6f);
 //       shader->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
 //       //shader->setUniform1f("brightness", oscillation);
 //       shader->setUniform1f("brightness", 1.0f);
 //       shader->setUniform3f("light_position", light.getGlobalPosition());
 //       shader->end();
 //       break;

 //   case ShaderType::blinn_phong:
 //       shader_name = "Blinn-Phong";
 //       shader = &shader_blinn_phong;
 //       shader->begin();
 //       shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
 //       shader->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
 //       shader->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
 //       //shader->setUniform1f("brightness", oscillation);
 //       shader->setUniform1f("brightness", 1.0f);
 //       shader->setUniform3f("light_position", light.getGlobalPosition());
 //       shader->end();
 //       break;

 //   default:
 //       break;
 //   }
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
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