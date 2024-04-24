#include "ParamObj.h"

ParamObj::ParamObj(ofShader* TesselShader) : Object("Curve")
{
	//pointeur du shader
	this->brazier_curve_shader = TesselShader;
	if (!this->brazier_curve_shader->isLoaded()) {
		ofLogFatalError() << "Brezier shader not loaded in param curve pointer!!!" ;
	}

	points.push_back(ofVec2f(-10.0f, -0.0));
	points.push_back(ofVec2f(-5.0f, 20.0f));
	points.push_back(ofVec2f(5.0f, -0.0));
	points.push_back(ofVec2f(10.0f, 20.0f));
	points.push_back(ofVec2f(15.0f, -0.0));
	pointsize = 2;

	segments = 30;

	// Set up patch VBO
	//float v[] = { -10.0f, -10.0f, -5.0f, 10.0f, 5.0f, -10.0f, 10.0f, 10.0f , 15.0f, -10.0f};

	/*GLuint vboHandle;
	glGenBuffers(1, &vboHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, 10 * sizeof(float), v, GL_STATIC_DRAW);

	// Set up patch VAO
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glPatchParameteri(GL_PATCH_VERTICES, 5);*/
}

void ParamObj::draw(bool highlight, bool animated, unsigned int substage)
{
	ofPushMatrix();
	ofSetColor(70, 0, 10);
	for (size_t i = 0; i < points.size(); i++)
	{
		ofSphere(points.at(i).x, points.at(i).y, pointsize);
	}
	float step = (1.0f / segments);
	float colorGrandiant = (255.f / segments);
	for (size_t i = 0; i < segments - 1; i++)
	{
		ofSetColor(colorGrandiant * i);
		ofDrawLine(getPointAt( i * step), getPointAt((i + 1.0f) * step));
	}
	ofSetColor(255);




	/*brazier_curve_shader->begin();
	
	
	brazier_curve_shader->setUniform1i("NumSegments", 20);
	brazier_curve_shader->setUniform1i("NumStrips", 1);
	brazier_curve_shader->setUniform4f("LineColor", ofVec4f(5.0f, 5.0f, 0.5f, 1.0f));
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_PATCHES, 0, 5);
	
	
	
	
	glDrawArrays(GL_POINTS, 0, 5);

	brazier_curve_shader->end();*/
	ofPopMatrix();
}

ofVec2f ParamObj::getPointAt(float t)
{

	
	return pow((1.0f - t), 4) * points.at(0)
		+ 4.0f * t * pow((1.0f - t), 3) * points.at(1)
		+ 6.0f * pow(t, 2) * pow((1.0f - t), 2) * points.at(2)
		+ 4.0f * pow(t, 3) * (1.0f - t) * points.at(3)
		+ pow(t, 4) * points.at(4);
}

void ParamObj::update()
{
	
}




