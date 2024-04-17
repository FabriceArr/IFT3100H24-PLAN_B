#pragma once
#include "ofMain.h"

enum class illum_enum { flat, lambert, gouraud, phong, blinnPhong, toon};

class ShaderHandler
{
private:
    ofShader blinn_phong, gouraud, lambert, phong, toon;
    ofLight Scenelight;

    illum_enum selectedIllumination;
    ofShader* currentIllumination;

    ShaderHandler();
    ~ShaderHandler(); 
    int data{ 0 };
    ShaderHandler(ShaderHandler& other) = delete; 
    void operator = (const ShaderHandler&) = delete;

public:
    static ShaderHandler* instance;

    ShaderHandler* getInstance();

    void deleteInstance();
    ofShader* getIllumShaderUsed();
    void setSelectedShader(string selected);

    void ShaderHandler::setShaderValue(ofColor amb, ofColor dif, ofColor spe);

    void loadShaders();
};

ShaderHandler* ShaderHandler::instance = nullptr;

