#include "Object.h"
#define MAXCHANGEBUFFERSIZE 10

Object::Object(string primitivetype)
{

	this->name = primitivetype;

	temp.g = temp.h = temp.i = 1;
	
	current_change = 0;
	changes_buffer.push_back(ofMatrix3x3(0,0,0,0,0,0,1,1,1));
	this->stroke_width = 1;

	this->exposure = 2.2f;
	this->gamma = 1.0f;
	this->tone_mapping = true;
	this->illumModel = illum_enum::flat;
	//this->TextureConfigure(image, 0);

	this->ambiantColor = ofColor(255, 0, 0);
	this->diffuseColor = ofColor(255, 0, 0);
	this->specularColor = ofColor(255, 0, 0);
	this->emissiveColor = ofColor(255, 0, 0);
	this->shininess = 40.0f;
}


Object::~Object()
{
	
}


string* Object::getName()
{
	return &this->name;
}

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

void Object::addChange(ofMatrix3x3 mat)
{
	//if the mat presented is the same as current one, all actions are ignored
	if(!isSameMatrix(mat, getCurrentChangeM()))
	{
		//current change isnt the newest, so clean the top until it meets the current change, discarting previous ones
		if (current_change != changes_buffer.size() - 1) {
			for (size_t i = 0; i < (changes_buffer.size() - current_change); i++)
			{
				changes_buffer.pop_back();
			}
		}


		if (changes_buffer.size() == MAXCHANGEBUFFERSIZE) {
			changes_buffer.pop_front();
		}


		changes_buffer.push_back(mat);
		current_change = changes_buffer.size() - 1;
	}
	
}

ofMatrix3x3 Object::getCurrentChangeM()
{
	//fail safe if the queu is somehow empty,
	//will show as teh object not being visible anymore and will never be visible again
	if (changes_buffer.size() < 1) {
		ofMatrix3x3 i;
		return i;
	}
	return (changes_buffer.at(current_change));
}

void Object::setColor(ofColor color)
{
	this->color = color;
}

ofColor Object::getColor()
{
	return this->color;
}

void Object::setStrokeColor(ofColor color)
{
	this->stroke_color = color;
}

ofColor Object::getStrokeColor()
{
	return this->stroke_color;
}

void Object::setStrokeWidth(unsigned int width)
{
	this->stroke_width = width;
}

unsigned int Object::getStrokeWidth()
{
	return this->stroke_width;
}

ofVec3f Object::getObbMin()
{
	return this->obb_min;
}

ofVec3f Object::getObbMax()
{
	return this->obb_max;
}

void Object::setToneMapping(float exposure, float gamma, bool tone_mapping)
{
	this->exposure = exposure;
	this->gamma = gamma;
	this->tone_mapping = tone_mapping;
}

void Object::setIllumModel(illum_enum illumModel)
{
	this->illumModel = illumModel;
}

float Object::getExposure()
{
	return this->exposure;
}

float Object::getGamma()
{
	return this->gamma;
}

bool Object::getToneMapping()
{
	return this->tone_mapping;
}

void Object::setAmbiantColor(ofColor color)
{
	this->ambiantColor = color;
}

void Object::setDiffuseColor(ofColor color)
{
	this->diffuseColor = color;
}

void Object::setSpecularColor(ofColor color)
{
	this->specularColor = color;
}

void Object::setEmissiveColor(ofColor color)
{
	this->emissiveColor = color;
}

void Object::setShininess(float shininess)
{
	this->shininess = shininess;
}

ofColor Object::getAmbiantColor()
{
	return this->ambiantColor;
}

ofColor Object::getDiffuseColor()
{
	return this->diffuseColor;
}

ofColor Object::getSpecularColor()
{
	return this->specularColor;
}

ofColor Object::getEmissiveColor()
{
	return this->emissiveColor;
}

float Object::getShininess()
{
	return this->shininess;
}

illum_enum Object::getIllumModel()
{
	return this->illumModel;
}

bool Object::undoChange()
{
	//no more changes to undo, first change is default location
	if (current_change == 0) {
		return false;
	}
	else {
		current_change--;
		return true;
	}
	
}

bool Object::recoverChange()
{
	//no more changes to recover
	if (current_change == changes_buffer.size()-1) {
		return false;
	}
	else {
		current_change++;
		return true;
	}
}

bool Object::isSameMatrix(ofMatrix3x3 a, ofMatrix3x3 b) {
	for (int i = 0; i < 9; i++) {
		float tempa = a[i];
		float tempb = b[i];
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;

}

//void Object::setFilter(unsigned int filter_setting)
//{
//	this->filterSelection = filter_setting;
//}
//
//unsigned int Object::getFilter()
//{
//	return filterSelection;
//}

void Object::TextureConfigure(ofImage image, unsigned int filterOption)
{
	/*
	// 1. ouvrir un fichier image en mode lecture et en extraire les propri�t�s
	int image_width = image.getWidth();
	int image_height = image.getHeight();
	int image_component = 3;

	// 2. allocation de l'espace m�moire pour les pixels de l'image
	int image_size = image_width * image_height * image_component;
	GLubyte* pixels = (GLubyte*)std::malloc(image_size * sizeof(GLubyte));

	//image.loadImage(image.getTextureReference());

	int index = 0;
	glActiveTexture(GL_TEXTURE0 + index);

	// 4. cr�ation d'une texture � partir des donn�es de l'image
	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// 5. d�finir les param�tres d'enveloppement aux extr�mit�s de la texture active
	// mode d'enveloppement de texture : GL_CLAMP_TO_BORDER
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	*/

	/* on utilise juste 1 par d�faut
	// mode d'enveloppement de texture : GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// mode d'enveloppement de texture : GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// mode d'enveloppement de texture : GL_MIRRORED_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	*/

	/*
	switch (filterOption)
	{
		//GLfloat largest_anisotropy = GL_EXT_texture_filter_anisotropic;

	case 0:// pas de filtrage		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	case 1: // filtrage bilin�aire
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	case 2: // filtrage trilin�aire
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	case 3: // filtrage anisotropique
		// avec GL_ARB_texture_filter_anisotropic si OpenGL 4.6
		// avec GL_EXT_texture_filter_anisotropic sinon
		GLfloat largest_anisotropy = GL_EXT_texture_filter_anisotropic;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_anisotropy);
	//default:
	//	break;
	}

	// 7. mipmapping
	// g�n�rer les diff�rents niveaux de mipmapping de la texture
	glGenerateMipmap(GL_TEXTURE_2D);

	//this->setFilter(filterOption);
	*/
}
