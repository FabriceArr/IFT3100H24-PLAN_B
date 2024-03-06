#pragma once
#include "Object.h"
#include "ofVbo.h"


class Element2D : public Object
{
private:
	ofImage image;

public:
	Element2D(string primitivetype, string path);
	~Element2D();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);

};
