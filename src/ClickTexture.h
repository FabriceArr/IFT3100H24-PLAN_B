//implémentation des concept vue ici https://ogldev.org/www/tutorial29/tutorial29.html

#pragma once
#include "ofMain.h"
#include <GL/glew.h>
#include <stdio.h>
#include <math.h>


class ClickTexture
{
private:
    GLuint m_WVPLocation;
    GLuint selection_frame_buffer = 0;
    GLuint clickable_pixel_texture = 0;
    GLuint selection_depth_texture = 0;
    ofShader click_shader;

public:

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void EnableWriting();

    void DisableWriting();

    unsigned int ReadPixel(unsigned int x, unsigned int y);

    void SetWVP(const ofMatrix4x4& WVP);
    
    void enable();
    void disable();


    
};

