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
	ofMatrix3x3 hold = this->getCurrentChangeM();
	ofTranslate(
		hold.a,
		hold.b,
		hold.c);
	ofRotateXDeg(
		hold.d);
	ofRotateYDeg(
		hold.e);
	ofRotateZDeg(
		hold.f);
	ofScale(
		hold.g,
		hold.h,
		hold.i);

	brazier_curve_shader->begin();

	scene_cam->getModelViewProjectionMatrix();

	brazier_curve_shader->setUniformMatrix4f("modelViewProjectionMatrix", scene_cam->getModelViewProjectionMatrix());
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




