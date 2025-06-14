#pragma once
#include "ofMain.h"

enum class illum_enum { materiel, lambert, gouraud, phong, blinnPhong, toon};

class ShaderHandler
{
private:
    ofShader blinn_phong, gouraud, lambert, phong, toon;
    ofMaterial flatMat;
    ofLight Scenelight;

    illum_enum selectedIllumination;
    ofShader* currentIllumination;

    int light_index;

    ShaderHandler();
    ~ShaderHandler(); 
    int data{ 0 };
    ShaderHandler(ShaderHandler& other) = delete; 
    void operator = (const ShaderHandler&) = delete;

    
    
    ofVec3f getNormalizedLight(int type);

public:
    static ShaderHandler* instance;

    ShaderHandler* getInstance();

    void deleteInstance();
    ofShader* getIllumShaderUsed();
    void setSelectedShader(string selected);

    void ShaderHandler::setShaderValue(ofColor amb, ofColor dif, ofColor spe, ofColor emi, float shin, ofTexture * text, unsigned int text_id);

    void change_light(bool type);
    void enableShading();
    void disableShading();
    void enableLighting();
    void disableLighting();

    void loadShaders();

   
};

ShaderHandler* ShaderHandler::instance = nullptr;

