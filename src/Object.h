#pragma once
#include "ofMain.h"



class Object
{
private:
	ofNode object;
	ofTexture texture;

	



public:
	ofVec3f translation_temp;
	ofVec3f rotation_temp;
	ofVec3f scale_temp;

	Object(ofNode object);

	ofNode* getObject();
	ofTexture* getTexture();

	void setObject(ofNode object);
	void setTexture(ofTexture texture);
	
};

