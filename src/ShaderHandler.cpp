#include "ShaderHandler.h"


ShaderHandler::ShaderHandler()
{
	this->selectedIllumination = illum_enum::flat;
	this->currentIllumination = nullptr;


	Scenelight.setPointLight();

	Scenelight.setAmbientColor(0.1f);
	Scenelight.setDiffuseColor(0.1f);
	Scenelight.setSpecularColor(0.6f);

	Scenelight.setGlobalPosition(200.0, 200.0, -50.0);
	light_index = 1;
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
void ShaderHandler::change_light(bool light_type) {
	if (!(light_index <= 1) && light_type) {
		light_index--;
	}
	if (!(light_index >= 4) && !light_type) {
		light_index++;
	}
	switch (light_index)
	{
	case 1:
		Scenelight.setSpotlight();
			break;
	case 2:
		Scenelight.setDirectional();
		break;
	case 3:
		Scenelight.setPointLight();
		break;
	case 4:
		Scenelight.setAmbientColor(255);
		break;
	default:
		break;
	}
}

void ShaderHandler::setShaderValue(ofColor amb, ofColor dif, ofColor spe, ofColor emi, float shin)
{
	//charge the current illumination shader
		switch (selectedIllumination)
		{

		case illum_enum::lambert:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", getNormalizedLight(1));
			currentIllumination->setUniform3f("color_diffuse", getNormalizedLight(2));
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;


		case illum_enum::gouraud:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", getNormalizedLight(1));
			currentIllumination->setUniform3f("color_diffuse", getNormalizedLight(2));
			currentIllumination->setUniform3f("color_specular", getNormalizedLight(3));
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;

		case illum_enum::phong:
			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", getNormalizedLight(1));
			currentIllumination->setUniform3f("color_diffuse", getNormalizedLight(2));
			currentIllumination->setUniform3f("color_specular", getNormalizedLight(3));
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());
			

			currentIllumination->end();
			break;

		case illum_enum::blinnPhong:

			currentIllumination->begin();

			currentIllumination->setUniform3f("color_ambient", getNormalizedLight(1));
			currentIllumination->setUniform3f("color_diffuse", getNormalizedLight(2));
			currentIllumination->setUniform3f("color_specular", getNormalizedLight(3));
			currentIllumination->setUniform1f("brightness", 40.0f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();

			break;
		case illum_enum::toon:
			currentIllumination->begin();
			currentIllumination->setUniform3f("color_ambient", getNormalizedLight(1));
			currentIllumination->setUniform3f("color_diffuse", getNormalizedLight(2));

			currentIllumination->setUniform3f("matt_amb_reflect", ofVec3f(0.3, 0.2, 0.1));
			currentIllumination->setUniform3f("matt_diff_reflect", ofVec3f(0.3, 0.2, 0.1));

			currentIllumination->setUniform1f("brightness", 5.f);
			currentIllumination->setUniform3f("light_position", Scenelight.getGlobalPosition());

			currentIllumination->end();
			break;
		case illum_enum::flat:
			flatMat.setAmbientColor(amb);
			flatMat.setDiffuseColor(dif);
			flatMat.setEmissiveColor(emi);
			flatMat.setSpecularColor(spe);
			flatMat.setShininess(shin);
			break;
		default:
			break;
		}

}

void ShaderHandler::enableShading()
{
	if (selectedIllumination == illum_enum::flat) {
		flatMat.begin();
	}
	else {
		currentIllumination->begin();
	}
}

void ShaderHandler::disableShading()
{
	if (selectedIllumination == illum_enum::flat) {
		flatMat.end();
	}
	else {
		currentIllumination->end();
	}
}

void ShaderHandler::enableLighting()
{
	Scenelight.enable();
}

void ShaderHandler::disableLighting()
{
	Scenelight.disable();
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
	else if (selected == "Blinn-Phong") {
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

    //1: ambiant
	//2: diffuse
	//3: specular
ofVec3f ShaderHandler::getNormalizedLight(int type)
{
	switch (type)
	{
	case 1:
		
		return ofVec3f(Scenelight.getAmbientColor().r, Scenelight.getAmbientColor().g, Scenelight.getAmbientColor().b);
		break;
	case 2:
		return ofVec3f(Scenelight.getDiffuseColor().r, Scenelight.getDiffuseColor().g, Scenelight.getDiffuseColor().b);
		break;
	case 3:
		return ofVec3f(Scenelight.getSpecularColor().r, Scenelight.getSpecularColor().g, Scenelight.getSpecularColor().b);
		break;

	default:
		break;
	}
	
}
