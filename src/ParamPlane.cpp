#include "ParamPlane.h"

ParamPlane::ParamPlane(ofShader* TesselShader) : Object("Curve")
{
	//pointeur du shader
	this->brazier_surface_shader = TesselShader;
	if (!this->brazier_surface_shader->isLoaded()) {
		ofLogFatalError() << "Brezier surface shader not loaded in param curve pointer!!!" ;
	}
	//default control points
	points.push_back(ofVec3f(0,0,-10));
	points.push_back(ofVec3f(0,5,-5));
	points.push_back(ofVec3f(0,0,0));
	points.push_back(ofVec3f(0,-5,5));
	points.push_back(ofVec3f(0,5,10));

	
	// Set up patch VBO
	float v[] = { -10.0f, 10.0f, 10.0f,
				10.0f, 10.0f, 10.0f,
				-10.0f, 10.0f, -10.0f,
				10.0f, 10.0f, -10.0f,
				-5.0f, -5.0f, 5.0f,
				5.0f, -5.0f, 5.0f,
				-5.0f, -5.0f, -5.0f,
				5.0f, -5.0f, -5.0f, };

	GLuint vboHandle;
	glGenBuffers(1, &vboHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), v, GL_STATIC_DRAW);

	// Set up patch VAO
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glPatchParameteri(GL_PATCH_VERTICES, 8);
}

void ParamPlane::draw(bool highlight, bool animated, unsigned int substage)
{
	ofPushMatrix();

	brazier_surface_shader->begin();

	brazier_surface_shader->setUniform1i("NumSegments", 50);
	brazier_surface_shader->setUniform4f("LineColor", ofVec4f(5.0f, 5.0f, 0.5f, 1.0f));

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_PATCHES, 0, 8);

	glDrawArrays(GL_POINTS, 0, 8);
	brazier_surface_shader->end();
	
	

	glFinish();
	ofPopMatrix();
}

void ParamPlane::update()
{
	
}




