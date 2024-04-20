#include "Skybox.h"

void Skybox::loadCubemap(std::string path)
{
    cubemap.load(path, 512);
}

Skybox::Skybox()
{
    
}

void Skybox::setup()
{
    loadCubemap("skybox/skybox.png");
}

void Skybox::draw() {

    cubemap.drawCubeMap();
}


