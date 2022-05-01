#ifndef __TREE_H__
#define __TREE_H__

#define TREE_OBJ "3d_tree.obj"

#include "../../obj_3d.h"
#include "../../../proc/shaders/shaders.h"

#include <cpmath/cpmath.h>

extern Object tree_object;

struct Tree {
    vec3 pos;

    mat4 model;
};

void InitializeTree();

Tree NewTree(vec3 pos);
void BindTree();
void RenderTree(Tree &tree, Program p);

#endif
