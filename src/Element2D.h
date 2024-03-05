#pragma once
#include "Object.h"
#include "ofVbo.h"


class Element2D : public Object
{
private:
	ofImage image;
	//ofVbo object_buffer, limit_box;

public:
	Element2D(string primitivetype, string path);
	Element2D(string name, ofMesh mesh);
	~Element2D();

	void draw(bool highlight, bool animated = false);

	//void primitivesLimitBox(bool type);
	//void customBox(ofMesh mesh);

};
