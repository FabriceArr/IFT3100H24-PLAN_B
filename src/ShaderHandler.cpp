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

void ShaderHandler::setShaderValue(ofColor amb, ofColor dif, ofColor spe)
{
	//charge the current illumination shader
	if (currentIllumination != nullptr) {
		switch (selectedIllumination)
		{

		case illum_enum::lambert:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", amb.r/255, amb.g / 255, amb.b / 255);
			currentIllumination->setUniform3f("color_diffuse", dif.r / 255, dif.g / 255, dif.b / 255);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;


			//these are the same so just no break and they spill over to the blinnPhong setting alloc
		case illum_enum::gouraud:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", amb.r / 255, amb.g / 255, amb.b / 255);
			currentIllumination->setUniform3f("color_diffuse", dif.r / 255, dif.g / 255, dif.b / 255);
			currentIllumination->setUniform3f("color_specular", spe.r / 255, spe.g / 255, spe.b / 255);
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;

		case illum_enum::phong:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", amb.r / 255, amb.g / 255, amb.b / 255);
			currentIllumination->setUniform3f("color_diffuse", dif.r / 255, dif.g / 255, dif.b / 255);
			currentIllumination->setUniform3f("color_specular", spe.r / 255, spe.g / 255, spe.b / 255);
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;

		case illum_enum::blinnPhong:

			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", amb.r / 255, amb.g / 255, amb.b / 255);
			currentIllumination->setUniform3f("color_diffuse", dif.r / 255, dif.g / 255, dif.b / 255);
			currentIllumination->setUniform3f("color_specular", spe.r / 255, spe.g / 255, spe.b / 255);
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();

			break;
		case illum_enum::toon:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", amb.r / 255, amb.g / 255, amb.b / 255);
			currentIllumination->setUniform3f("color_diffuse", dif.r / 255, dif.g / 255, dif.b / 255);
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;
		case illum_enum::flat:
		default:
			break;
		}
	}

}

void ShaderHandler::setSelectedShader(string selected)
{
	
	if (selected == "None") {
		selectedIllumination = illum_enum::flat;
	}
	else if (selected == "Lambert") {
		selectedIllumination = illum_enum::lambert;
	}
	else if (selected == "Gouraud") {
		selectedIllumination = illum_enum::gouraud;
	}
	else if (selected == "Phong") {
		selectedIllumination = illum_enum::phong;
	}
	else if (selected == "Blinn - Phong") {
		selectedIllumination = illum_enum::blinnPhong;
	}
	else if (selected == "Toon") {
		selectedIllumination = illum_enum::toon;
	}

	switch (selectedIllumination)
	{
	case illum_enum::flat:
		currentIllumination = nullptr;
		break;

	case illum_enum::lambert:
		if (lambert.isLoaded()) {
			currentIllumination = &lambert;
		}
		else ofLogFatalError() << "lambert not loaded";
		break;

	case illum_enum::gouraud:
		if (gouraud.isLoaded()) {
			currentIllumination = &gouraud;
		}
		else ofLogFatalError() << "gouraud not loaded";
		break;

	case illum_enum::phong:
		if (phong.isLoaded()) {
			currentIllumination = &phong;
		}
		else ofLogFatalError() << "phong not loaded";
		break;

	case illum_enum::blinnPhong:
		if (blinn_phong.isLoaded()) {
			currentIllumination = &blinn_phong;
		}
		else ofLogFatalError() << "blinn_phong not loaded";
		break;

	case illum_enum::toon:
		if (toon.isLoaded()) {
			currentIllumination = &toon;
		}
		else ofLogFatalError() << "toon not loaded";
		break;

	default:
		currentIllumination = nullptr;
		break;
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

	ofLog() << "Shader1; " << toon.setupShaderFromFile(GL_VERTEX_SHADER, "Illumination/toon/toon_vs.glsl");
	ofLog() << "Shader4; " << toon.setupShaderFromFile(GL_FRAGMENT_SHADER, "Illumination/toon/toon_fs.glsl");
	ofLog() << "Shader5; " << toon.linkProgram();

	toon.isLoaded();
}