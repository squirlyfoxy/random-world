#include "texture.h"

#include "assets_manager.h"

#include <stdlib.h>
#include <cstdio>
#include <iostream>

#include <glad/glad.h>

#include "../../lib/cute_headers/cute_png.h"

void Texture_Load(Texture* texture) {
    std::cout << "Loading texture: " << texture->path << std::endl;

    //Load image
    int width, height;
    size_t size_data = 0;
    void* data = LoadAsset(texture->path.c_str(), &size_data);
    std::cout << "Size data: " << size_data << std::endl;
    cp_image_t img = cp_load_png_mem(data, size_data);

    width = img.w;
    height = img.h;

    //Generate texture
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.pix);
    glGenerateMipmap(GL_TEXTURE_2D);

    free(img.pix);

    texture->width = width;
    texture->height = height;
}