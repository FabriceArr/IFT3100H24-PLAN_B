#pragma once

class Skybox
{
	private:
		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;

	public:
	Skybox();
	~Skybox();
	void draw();
};