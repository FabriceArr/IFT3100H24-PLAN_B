#pragma once
#include "Object.h"
#include "Scene.h"
#include "ofVbo.h"
#include "TextGen.h"
#include "ConvolutionKernel.h"
#include <array>

// kernel de convolution (3x3) : identité
const std::array<float, 9> convolution_kernel_identity
{
  0.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f,  0.0f
};

// kernel de convolution (3x3) : aiguiser
const std::array<float, 9> convolution_kernel_sharpen
{
  0.0f, -1.0f,  0.0f,
 -1.0f,  5.0f, -1.0f,
  0.0f, -1.0f,  0.0f
};

// kernel de convolution (3x3) : détection de bordure
const std::array<float, 9> convolution_kernel_edge_detect
{
  0.0f,  1.0f,  0.0f,
  1.0f, -4.0f,  1.0f,
  0.0f,  1.0f,  0.0f
};

// kernel de convolution (3x3) : bosseler
const std::array<float, 9> convolution_kernel_emboss
{
 -2.0f, -1.0f,  0.0f,
 -1.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  2.0f
};

// kernel de convolution (3x3) : flou
const std::array<float, 9> convolution_kernel_blur
{
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f
};


class Element2D : public Object
{
private:
	ConvolutionKernel kernel_type;

	string kernel_name;
	Scene scene;
	ofImage image_destination;

	int image_width;
	int image_height;

	int offset_vertical;
	int offset_horizontal;
	ofImage image;
	ofVbo square;
	ofShader shader;

	float tone_mapping_exposure;
	float tone_mapping_gamma;
	bool tone_mapping_toggle;

public:
	Element2D(string primitivetype, string path);
	Element2D();
	~Element2D();

	ofImage* getImage();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);
	void filter();

};
