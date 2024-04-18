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
	shader.load("tone_mapping_330_vs.glsl", "tone_mapping_330_fs.glsl");

	// sélectionner le filtre de convolution par défaut
	kernel_type = scene.kernel_type;
	kernel_name = scene.kernel_name;

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

void Element2D::filter()
{
	// résolution du kernel de convolution
	const int kernel_size = 3;

	// décalage à partir du centre du kernel
	const int kernel_offset = kernel_size / 2;

	// nombre de composantes de couleur (RGB)
	const int color_component_count = 3;

	// indices de l'image
	int x, y;

	// indices du kernel
	int i, j;

	// indices d'échantillonnage;
	int xi, yj;

	// index des composantes de couleur
	int c;

	// index du pixel de l'image source utilisé pour le filtrage
	int pixel_index_img_src;

	// index du pixel de l'image de destination en cours de filtrage
	int pixel_index_img_dst;

	// index du pixel de l'image de destination en cours de filtrage
	int kernel_index;

	// valeur à un des indices du kernel de convolution
	float kernel_value;

	// extraire les pixels de l'image source
	ofPixels pixel_array_src = image.getPixels();

	// extraire les pixels de l'image de destination
	ofPixels pixel_array_dst = image_destination.getPixels();

	// couleur du pixel lu dans l'image source
	ofColor pixel_color_src;

	// couleur du pixel à écrire dans l'image de destination
	ofColor pixel_color_dst;

	// somme du kernel appliquée à chaque composante de couleur d'un pixel
	float sum[color_component_count];

	// itération sur les rangées des pixels de l'image source
	for (y = 0; y < image_height; ++y)
	{
		// itération sur les colonnes des pixels de l'image source
		for (x = 0; x < image_width; ++x)
		{
			// initialiser le tableau où les valeurs de filtrage sont accumulées
			for (c = 0; c < color_component_count; ++c)
				sum[c] = 0;

			// déterminer l'index du pixel de l'image de destination
			pixel_index_img_dst = (image_width * y + x) * color_component_count;

			// itération sur les colonnes du kernel de convolution
			for (j = -kernel_offset; j <= kernel_offset; ++j)
			{
				// itération sur les rangées du kernel de convolution
				for (i = -kernel_offset; i <= kernel_offset; ++i)
				{
					// calculer les indices d'échantillonnage
					xi = x - i;
					yj = y - j;

					// traitement de la bordure
					if (xi < 0 || xi > image_width || yj < 0 || yj > image_height)
						continue;

					// déterminer l'index du pixel de l'image source à lire
					pixel_index_img_src = (image_width * yj + xi) * color_component_count;

					// lire la couleur du pixel de l'image source
					pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

					// déterminer l'indice du facteur à lire dans le kernel de convolution
					kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

					// extraction de la valeur à cet index du kernel
					switch (kernel_type)
					{
					case ConvolutionKernel::identity:
						kernel_value = convolution_kernel_identity.at(kernel_index);
						break;

					case ConvolutionKernel::emboss:
						kernel_value = convolution_kernel_emboss.at(kernel_index);
						break;

					case ConvolutionKernel::sharpen:
						kernel_value = convolution_kernel_sharpen.at(kernel_index);
						break;

					case ConvolutionKernel::edge_detect:
						kernel_value = convolution_kernel_edge_detect.at(kernel_index);
						break;

					case ConvolutionKernel::blur:
						kernel_value = convolution_kernel_blur.at(kernel_index);
						break;

					default:
						kernel_value = convolution_kernel_identity.at(kernel_index);
						break;
					}

					// itération sur les composantes de couleur
					for (c = 0; c < color_component_count; ++c)
					{
						// accumuler les valeurs de filtrage en fonction du kernel de convolution
						sum[c] = sum[c] + kernel_value * pixel_color_src[c];
					}
				}
			}

			// déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
			for (c = 0; c < color_component_count; ++c)
			{
				// conversion vers entier et validation des bornes de l'espace de couleur
				pixel_color_dst[c] = (int)ofClamp(sum[c], 0, 255);
			}

			// écrire la couleur à l'index du pixel en cours de filtrage
			pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
		}
	}

	// écrire les pixels dans l'image de destination
	image_destination.setFromPixels(pixel_array_dst);

	ofLog() << "<filtre de convolution complété (" << kernel_name << ")>";
}