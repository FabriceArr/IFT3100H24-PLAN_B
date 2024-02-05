#pragma once
#include "ofMain.h"



class Object
{
private:
	ofTexture texture;

	



public:
	ofNode object;
	ofVec3f translation_temp;
	ofVec3f rotation_temp;
	ofVec3f scale_temp;

	Object(ofNode object);

	const ofNode* getObject();
	const ofTexture* getTexture();

	void setObject(ofNode object);
	void setTexture(ofTexture texture);

	bool operator==(const Object& a);
	
};

