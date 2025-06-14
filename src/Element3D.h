#pragma once
#include "ofMain.h"
#include "Object.h"
#include "ofVbo.h"
#include "ofxAssimpModelLoader.h"
#include "ShaderHandler.h"
#include "Element2D.h"


class Element3D : public Object
{
private:
	ShaderHandler* shader_handler_singleton;

	Element2D texture;
	ofVbo object_buffer, limit_box;

public:
	Element3D(string primitivetype, ofColor color);
	Element3D(string name, ofMesh mesh);
	~Element3D();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);


	void primitivesLimitBox(bool type);
	void customBox(ofMesh mesh);

	void updateVertData(const ofVec3f* vecs, const GLuint* ids, unsigned int size);
	void updateTextureData(const ofVec2f* uvs, const GLuint* ids, unsigned int size);
	void updateColorData(ofColor c);


};

