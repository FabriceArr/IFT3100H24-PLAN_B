#include "Element2D.h"


Element2D::Element2D(string primitivetype, string path) : Object(primitivetype)
{
	if (primitivetype == "Imported") {

		this->image.load(path);

	}
}

Element2D::~Element2D()
{
}

void Element2D::draw(bool highlight, bool animated)
{
	this->image.draw(image.getWidth()/-2,0,0);
}