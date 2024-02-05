#include "Object.h"

Object::Object(ofNode object)
{
	this->object = object;
	translation_temp = { 0.f, 0.f, 0.f };
	rotation_temp = { 0.f, 0.f, 0.f };
	scale_temp = { 0.f, 0.f, 0.f };
}

const ofNode* Object::getObject()
{
	return &this->object;
}

const ofTexture* Object::getTexture()
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

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

