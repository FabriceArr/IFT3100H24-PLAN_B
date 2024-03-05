#pragma once
#include "Object.h"
#include "ofVbo.h"


class Element2D : public Object
{
private:
	ofImage image;
	ofVbo square;
public:
	Element2D(string primitivetype, string path);
	~Element2D();



	void draw(bool highlight, bool animated = false);

};
