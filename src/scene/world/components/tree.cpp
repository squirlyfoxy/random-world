#include "tree.h"

#include <glad/glad.h>

#include <cpmath/act/act_mat4.h>

#include <cstddef>

Object  tree_object;
bool    initialized = false;

unsigned int tree_vao;
unsigned int tree_vbo;
unsigned int tree_ebo;

void InitializeTree() {
    tree_object = Read3DObject(TREE_OBJ);

    // Buffers
    glGenVertexArrays(1, &tree_vao);
    glBindVertexArray(tree_vao);

    glGenBuffers(1, &tree_vbo);
    glGenBuffers(1, &tree_ebo);

    glBindBuffer(GL_ARRAY_BUFFER, tree_vbo);
    glBufferData(GL_ARRAY_BUFFER, tree_object.vertices.size() * sizeof(Vertex), &tree_object.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tree_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tree_object.indices.size() * sizeof(unsigned int), &tree_object.indices[0], GL_STATIC_DRAW);

    // VERTICES (3)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // NORMALS (3)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // TEXTURE COORDINATES (2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

    glBindVertexArray(0);

    initialized = true;
}

Tree NewTree(vec3 pos) {
    Tree tree;
    tree.pos = pos;
    
    tree.model = mat4_identity();
    tree.model = mat4_translate(tree.model, pos);

    return tree;
}

void BindTree() {
    if (!initialized) return;

    glBindVertexArray(tree_vao);
}

void RenderTree(Tree &tree, Program p) {
    // Model matrix
    BindMat4(p, "model", tree.model);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawElements(GL_TRIANGLES, tree_object.indices.size(), GL_UNSIGNED_INT, 0);
}
