#pragma once
#include "ofMain.h"
#include "Object.h"
#include "ofVbo.h"
#include "ofxAssimpModelLoader.h"

class Element3D : public Object
{
private:
	ofTexture texture;
	ofVbo object_buffer, limit_box;

public:
	Element3D(string primitivetype, ofColor color);
	Element3D(string name, ofMesh mesh);
	~Element3D();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);


	void primitivesLimitBox(bool type);
	void customBox(ofMesh mesh);

	void updateColorData(ofColor c);


};

