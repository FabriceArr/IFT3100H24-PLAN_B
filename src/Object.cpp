#include "Object.h"

Object::Object(ofNode object)
{
	this->object = object;
	translation_temp = { 0.f, 0.f, 0.f };
	rotation_temp = { 0.f, 0.f, 0.f };
	scale_temp = { 0.f, 0.f, 0.f };
}

ofNode* Object::getObject()
{
	return &this->object;
}

ofTexture* Object::getTexture()
{
	return &this->texture;
}

void Object::setObject(ofNode object)
{
	this->object = object;
}

void Object::setTexture(ofTexture texture)
{
	this->texture = texture;
}
