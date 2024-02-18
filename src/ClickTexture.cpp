//implémentation des concept vue ici https://ogldev.org/www/tutorial29/tutorial29.html avec modification

#include "ClickTexture.h"
bool ClickTexture::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
    //create a second framebuffer to capture the clickable object catcher, and setting up for read and write
    glGenFramebuffers(1, &selection_frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, selection_frame_buffer);

    //creates a texture to catch the pixels that will be rresterized bu the second framebuffer,
    //  and setting it up to use unsigned int instead of float
    glGenTextures(1, &clickable_pixel_texture);
    glBindTexture(GL_TEXTURE_2D, clickable_pixel_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, WindowWidth, WindowHeight, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, clickable_pixel_texture, 0);

    //une deuxieme depth_map est aussi necessaire puique nous avons un second framebuffer.
    //  ceci vas nous aider lors d'un click de selection simple avec deux object un devant l'autre.
    glGenTextures(1, &selection_depth_texture);
    glBindTexture(GL_TEXTURE_2D, selection_depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, selection_depth_texture, 0);

    //check if its all good
    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) 
    {
        ofLog() << "Clickable Frame Buffer Init Error, status : " << Status << endl;
        exit(1);
    }

    //Puts back the normal Frames Buffer since setting up the old one replaced it
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //Sets up the shaders needed to make the objects produce the image that gives off their pointers as first value

    click_shader.load("click_select_vs", "click_select_fs");
    m_WVPLocation = glGetUniformLocation(0, "WVP");

    if (m_WVPLocation == GL_INVALID_VALUE) {
        return false;
    }

    return true;
}

void ClickTexture::EnableWriting()
{
    //sets up the clicker frame buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, selection_frame_buffer);
}

void ClickTexture::DisableWriting()
{
    //turns off the clicker frame buffer, replacing it with the normal frame buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

unsigned int ClickTexture::ReadPixel(unsigned int x, unsigned int y)
{
    return 0;
}


void ClickTexture::SetWVP(const ofMatrix4x4& WVP)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, WVP.getPtr());
}

void ClickTexture::enable() {
    click_shader.begin();
}

void ClickTexture::disable() {
    click_shader.end();
}


