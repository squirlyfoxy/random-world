#include "framebuffer.h"

#include <glad/glad.h>

unsigned int depth_buffer;
unsigned int depth_texture;

void DepthTextureGen() {

}

void DepthBufferGen() {

}

void GenerateFramebuffer() {
    DepthTextureGen();
    DepthBufferGen();
}

void DestroyFramebuffer() {
    
}
