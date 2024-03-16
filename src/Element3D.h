#pragma once
#include "ofMain.h"
#include "Object.h"
#include "ofVbo.h"
#include "ofxAssimpModelLoader.h"
#include "Element2D.h"

class Element3D : public Object
{
private:
	Element2D texture;
	ofVbo object_buffer, limit_box;
	ofVec2f holder_uvs[];

public:
	Element3D(string primitivetype, ofColor color);
	Element3D(string name, ofMesh mesh);
	~Element3D();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);


	void primitivesLimitBox(bool type);
	void customBox(ofMesh mesh);

	void updateTextureData(const ofVec2f* uvs, unsigned int size);


};

