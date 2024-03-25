#include "Element2D.h"


Element2D::Element2D(string primitivetype, string path) : Object(primitivetype)
{
	if (primitivetype == "Imported") {
		if (!this->image.load(path)) {
						ofLogNotice("Element2D") << "Image not loaded";
		}
		this->image.load(path);

		ofVec3f square_vertices_custom[] =
		{
			ofVec3f(image.getWidth() / 2 ,  this->image.getHeight(), 0),//0
			ofVec3f(-image.getWidth() / 2 , this->image.getHeight(), 0),//1
			ofVec3f(image.getWidth() / 2 , 0,  0),//2
			ofVec3f(-image.getWidth() / 2 , 0, 0)//3
		};

		GLuint square_vertices_ids[] =
		{
			0, 1,
			1, 3,
			3, 2,
			2, 0
		};

		this->square.setVertexData(&square_vertices_custom[0], 4, GL_STATIC_DRAW);
		this->square.setIndexData(&square_vertices_ids[0], 8, GL_STATIC_DRAW);
	}
	this->TextureConfigure(image,0);
	
	if (!shader.load("tone_mapping_330_vs.glsl", "tone_mapping_330_fs.glsl")) {
		ofLogError("Element2D") << "Shader tone mapping failed to load";
	}
}

Element2D::Element2D() : Object("Default_texture")
{
	//default texture loading
	this->image = TexTGen::generateTextureDefault(8);

	ofVec3f square_vertices_custom[] =
	{
		ofVec3f(image.getWidth() / 2 ,  this->image.getHeight(), 0),//0
		ofVec3f(-image.getWidth() / 2 , this->image.getHeight(), 0),//1
		ofVec3f(image.getWidth() / 2 , 0,  0),//2
		ofVec3f(-image.getWidth() / 2 , 0, 0)//3
	};

	GLuint square_vertices_ids[] =
	{
		0, 1,
		1, 3,
		3, 2,
		2, 0
	};

	this->square.setVertexData(&square_vertices_custom[0], 4, GL_STATIC_DRAW);
	this->square.setIndexData(&square_vertices_ids[0], 8, GL_STATIC_DRAW);

	if (!shader.load("tone_mapping_330_vs.glsl", "tone_mapping_330_fs.glsl")) {
		ofLogError("Element2D") << "Shader tone mapping failed to load";
	}

}

Element2D::~Element2D()
{
}

ofImage* Element2D::getImage()
{
	return &this->image;
}

void Element2D::draw(bool highlight, bool animated, unsigned int substage)
{
	if (highlight) {
		//draw the box
		ofBeginShape();

		ofSetColor(232, 247, 14);
		glPointSize(5);
		square.draw(GL_POINTS, 0, 8);
		glPointSize(0);
		ofSetColor(233, 15, 233);

		glLineWidth(5);
		square.drawElements(GL_LINES, square.getNumIndices());
		glLineWidth(0);
		ofSetColor(255);

		ofEndShape();
	}
	// activer le filtre
	shader.begin();

	// passer les attributs uniformes au shader
	shader.setUniformTexture("image", image.getTexture(), 1);

	shader.setUniform1f("tone_mapping_exposure", getExposure());
	shader.setUniform1f("tone_mapping_gamma", getGamma());
	shader.setUniform1i("tone_mapping_toggle", getToneMapping());

	this->image.draw(image.getWidth()/-2,0,0);

	// désactiver le filtre
	shader.end();
}