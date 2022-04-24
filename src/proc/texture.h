#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

struct Texture {
    unsigned int id;
    std::string path;

    // GL_RGBA texture format
    int width;
    int height;
};
void Texture_Load(Texture* texture);

#endif
