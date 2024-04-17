#include "ShaderHandler.h"


ShaderHandler::ShaderHandler()
{
	this->selectedIllumination = illum_enum::flat;
	this->currentIllumination = nullptr;


	Scenelight.setAmbientColor(0.1f);
	Scenelight.setPosition(200.0, 200.0, -50.0);

	loadShaders();
}

ShaderHandler::~ShaderHandler()
{
    blinn_phong.unload();
    gouraud.unload();
    lambert.unload();
    phong.unload();
    toon.unload();

    if (currentIllumination != nullptr) {
        delete currentIllumination;
    }
   
}

ShaderHandler* ShaderHandler::getInstance() {
    if (!this->instance)
        this->instance = new ShaderHandler();
    return this->instance;
}
void ShaderHandler::deleteInstance() {
    if (this->instance) {
        delete this->instance;
        this->instance = nullptr;
    }
}

ofShader* ShaderHandler::getIllumShaderUsed()
{
	return currentIllumination;
}

void ShaderHandler::setShaderValue(int value)
{
	//charge the current illumination shader
	if (currentIllumination != nullptr) {
		switch (selectedIllumination)
		{

		case illum_enum::lambert:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", Scenelight.getAmbientColor().r, Scenelight.getAmbientColor().g, Scenelight.getAmbientColor().b);
			currentIllumination->setUniform3f("color_diffuse", 0.2f, 0.6f, 0.4f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;


			//these are the same so just no break and they spill over to the blinnPhong setting alloc
		case illum_enum::gouraud:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", Scenelight.getAmbientColor().r, Scenelight.getAmbientColor().g, Scenelight.getAmbientColor().b);
			currentIllumination->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
			currentIllumination->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
			currentIllumination->setUniform1f("brightness", 1.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;

		case illum_enum::phong:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", Scenelight.getAmbientColor().r, Scenelight.getAmbientColor().g, Scenelight.getAmbientColor().b);
			currentIllumination->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
			currentIllumination->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
			currentIllumination->setUniform1f("brightness", 1.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;

		case illum_enum::blinnPhong:

			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", Scenelight.getAmbientColor().r, Scenelight.getAmbientColor().g, Scenelight.getAmbientColor().b);
			currentIllumination->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
			currentIllumination->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
			currentIllumination->setUniform1f("brightness", 1.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();

			break;
		case illum_enum::flat:
		default:
			break;
		}
	}
}

void ShaderHandler::loadShaders()
{
	//gives debug messages
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofLog() << "Shader1; " << blinn_phong.setupShaderFromFile(GL_VERTEX_SHADER, "Illumination/blinn_phong/blinn_phong_330_vs.glsl");
	ofLog() << "Shader4; " << blinn_phong.setupShaderFromFile(GL_FRAGMENT_SHADER, "Illumination/blinn_phong/blinn_phong_330_fs.glsl");
	ofLog() << "Shader5; " << blinn_phong.linkProgram();

	blinn_phong.isLoaded();

	ofLog() << "Shader1; " << gouraud.setupShaderFromFile(GL_VERTEX_SHADER, "Illumination/gouraud/gouraud_330_vs.glsl");
	ofLog() << "Shader4; " << gouraud.setupShaderFromFile(GL_FRAGMENT_SHADER, "Illumination/gouraud/gouraud_330_fs.glsl");
	ofLog() << "Shader5; " << gouraud.linkProgram();

	gouraud.isLoaded();

	ofLog() << "Shader1; " << lambert.setupShaderFromFile(GL_VERTEX_SHADER, "Illumination/lambert/lambert_330_vs.glsl");
	ofLog() << "Shader4; " << lambert.setupShaderFromFile(GL_FRAGMENT_SHADER, "Illumination/lambert/lambert_330_fs.glsl");
	ofLog() << "Shader5; " << lambert.linkProgram();

	lambert.isLoaded();

	ofLog() << "Shader1; " << phong.setupShaderFromFile(GL_VERTEX_SHADER, "Illumination/phong/phong_330_vs.glsl");
	ofLog() << "Shader4; " << phong.setupShaderFromFile(GL_FRAGMENT_SHADER, "Illumination/phong/phong_330_fs.glsl");
	ofLog() << "Shader5; " << phong.linkProgram();

	phong.isLoaded();
}