#include "ParamObj.h"

ParamObj::ParamObj(ofShader* TesselShader, ofEasyCam* cam) : Object("Curve")
{
	//pointeur du shader
	this->brazier_curve_shader = TesselShader;
	if (!this->brazier_curve_shader->isLoaded()) {
		ofLogError() << "Brezier shader not loaded in param curve pointer!!!" ;
	}
	//default control points
	points.push_back(ofVec3f(0,0,-10));
	points.push_back(ofVec3f(0,5,-5));
	points.push_back(ofVec3f(0,0,0));
	points.push_back(ofVec3f(0,-5,5));
	points.push_back(ofVec3f(0,5,10));

	scene_cam = cam;
	
	// Set up patch VBO
	float v[] = { -10.0f, -10.0f, -5.0f, 10.0f, 5.0f, -10.0f, 10.0f, 10.0f };

	GLuint vboHandle;
	glGenBuffers(1, &vboHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), v, GL_STATIC_DRAW);

	// Set up patch VAO
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
}

void ParamObj::draw(bool highlight, bool animated, unsigned int substage)
{
	ofMatrix4x4 translate = ofMatrix4x4(1, 0, 0, this->getCurrentChangeM().a,
		0, 1, 0, this->getCurrentChangeM().b,
		0, 0, 1, this->getCurrentChangeM().c,
		0, 0, 0, 1);

	ofMatrix4x4 rotx = ofMatrix4x4(1, 0, 0, 0,
		0, cos(this->getCurrentChangeM().d), sin(this->getCurrentChangeM().d), 0,
		0, -sin(this->getCurrentChangeM().d), cos(this->getCurrentChangeM().d), 0,
		0, 0, 0, 1);

	ofMatrix4x4 roty = ofMatrix4x4(cos(this->getCurrentChangeM().e), 0, -sin(this->getCurrentChangeM().e), 0,
		0, 1, 0, 0,
		sin(this->getCurrentChangeM().e), 0, cos(this->getCurrentChangeM().e), 0,
		0, 0, 0, 1);

	ofMatrix4x4 rotz = ofMatrix4x4(cos(this->getCurrentChangeM().f), -sin(this->getCurrentChangeM().f), 0, 0,
		sin(this->getCurrentChangeM().f), cos(this->getCurrentChangeM().f), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	ofMatrix4x4 scale = ofMatrix4x4(this->getCurrentChangeM().g, 0, 0, 0,
		0, this->getCurrentChangeM().h, 0, 0,
		0, 0, this->getCurrentChangeM().i, 0,
		0, 0, 0, 1);


	ofMatrix4x4 fullTransform = translate * (rotx * roty * rotz) * scale;

	brazier_curve_shader->begin();

	scene_cam->getModelViewProjectionMatrix();
	
	brazier_curve_shader->setUniform1i("NumSegments", 50);
	brazier_curve_shader->setUniform1i("NumStrips", 1);
	brazier_curve_shader->setUniform4f("LineColor", ofVec4f(5.0f, 5.0f, 0.5f, 1.0f));

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_PATCHES, 0, 4);
	
	
	brazier_curve_shader->end();
	
	glDrawArrays(GL_POINTS, 0, 4);

	glFinish();
}

void ParamObj::update()
{
	
}




