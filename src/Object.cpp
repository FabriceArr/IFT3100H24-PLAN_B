#include "Object.h"

Object::Object(ofNode object, string name = "Objet")
{
	this->name = name;
	this->object = object;
	translation_temp = { 0.f, 0.f, 0.f };
	rotation_temp = { 0.f, 0.f, 0.f };
	scale_temp = { 0.f, 0.f, 0.f };
}

const ofNode* Object::getObject() const
{
	return &this->object;
}

const ofTexture* Object::getTexture() const
{
	return &this->texture;
}

string* Object::getName()
{
	return &this->name;
}

void Object::setObject(ofNode object)
{
	this->object = object;
}

void Object::setTexture(ofTexture texture)
{
	this->texture = texture;
}


void Object::setName(string name)
{
	this->name = name;
}

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

