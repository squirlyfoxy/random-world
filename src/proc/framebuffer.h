#ifndef __PROC_FRAMEBUFFER_H
#define __PROC_FRAMEBUFFER_H

// ***
// Objects
extern unsigned int depth_buffer;
extern unsigned int depth_texture;

void GenerateFramebuffer();
void DestroyFramebuffer();

#endif
