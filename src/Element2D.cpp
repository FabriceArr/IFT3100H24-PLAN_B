#include "Element2D.h"


Element2D::Element2D(string primitivetype, string path) : Object(primitivetype)
{
	if (primitivetype == "Imported") {

		this->image.load(path);

	}
}

Element2D::Element2D(string name, ofMesh mesh) : Object(name)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);

	customBox(mesh);

}

Element2D::Element2D(string primitivetype, ofColor color) : Object(primitivetype)
{
	if (primitivetype == "triangle") {
		add_vector_shape(VectorPrimitiveType::triangle, 0, 0, 0, 1, 1, 0, 0, 0);
	}
	else if (primitivetype == "rectangle") {
		add_vector_shape(VectorPrimitiveType::rectangle, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "ellipse") {
		add_vector_shape(VectorPrimitiveType::ellipse, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "line") {
		add_vector_shape(VectorPrimitiveType::line, 0, 0, 1, 1, 0, 0, 0, 0);
	}
	else if (primitivetype == "point") {
		add_vector_shape(VectorPrimitiveType::point, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

Element2D::~Element2D()
{
}

void Element2D::draw(bool highlight, bool animated)
{
	this->image.draw(image.getWidth()/-2,0,0);
}
