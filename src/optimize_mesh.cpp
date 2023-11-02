
#include "optimize_mesh.h"
#include <unordered_map>
#include <iostream>

using namespace std;

Mesh *optimize_data (const Vertex2D *mesh_data, int mesh_data_length) {

    // map to index new vertex list with
    // doubles as being able to check for uniqueness, and cacheing new index positions for quick lookup
    unordered_map<Vertex2D, int> vertex_index;
    Vertex2D new_vertices[mesh_data_length];

    // generate unique list of vertices
    int new_vert_idx = 0;
    for (int i = 0; i < mesh_data_length; i++) {
        Vertex2D v = mesh_data[i];
        // insert if it hasnt been encountered yet
        if (vertex_index.find(v) == vertex_index.end()) {
            // store new index position for quick lookup later
            vertex_index[v] = new_vert_idx;
            new_vertices[new_vert_idx] = v;
            new_vert_idx++;
        }
    }

    // go over vertex triangle list and convert to index array
    int *indices = (int*)malloc(mesh_data_length * sizeof(int));
    for (int i = 0; i < mesh_data_length; i++) {
        Vertex2D v = mesh_data[i];
        int indice = vertex_index[v];
        indices[i] = indice;
    }

    // Shorten vertex array to unique length
    Vertex2D *new_vertices_shortened = (Vertex2D*)malloc(new_vert_idx * sizeof(Vertex2D));
    for (int i = 0; i < new_vert_idx; i++) {
        new_vertices_shortened[i] = new_vertices[i];
    }

    Mesh *mesh = new Mesh();
    
    mesh->verts = new_vertices_shortened; // vertices
    mesh->vert_length = new_vert_idx; // vertices length
    mesh->indices = indices; // indices
    mesh->indice_length = mesh_data_length; // indices length

    return mesh;

}

