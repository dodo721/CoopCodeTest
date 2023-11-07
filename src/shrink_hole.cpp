
#include "shrink_hole.h"

#include "vert_utils.h"
#include "EyeMeshData.hpp"
#include <math.h>
#include <iostream>

using namespace std;


Mesh *shrink_hole (Mesh *eye_mesh, float frac) {

    Vertex2D *old_verts = eye_mesh->verts;
    int *old_indices = eye_mesh->indices;

    // new vert length = old verts + center edges = old verts + 4
    int new_vert_length = eye_mesh->vert_length;
    Vertex2D *new_verts = (Vertex2D*)malloc(new_vert_length * sizeof(Vertex2D));
    // new indice length = 4 new faces * 3 each = old index length + 36
    int new_indice_length = eye_mesh->indice_length + 36;
    int *new_indices = (int*)malloc(new_indice_length * sizeof(int));

    // find corner and side verts first
    SideIndices side_indices = {};
    int corner_indices[4];

    float shrink_frac = 1 - frac;

    // Shrink all verts by frac
    for (int i = 0; i < eye_mesh->vert_length; i++) {
        Vertex2D vert = old_verts[i];
        side_indices.add_side_vert(vert, i);
        if (is_vertex_corner(vert)) {
            new_verts[i] = vert;
            continue;
        }
        Vertex2D center = {0.5, 0.5};
        Vertex2D v_center_origin = vert - center;
        Vertex2D new_vertex = v_center_origin * shrink_frac;
        new_vertex = new_vertex + center;
        new_verts[i] = new_vertex;
    }

    int old_vert_length = eye_mesh->vert_length;

    // add old indices
    for (int i = 0; i < eye_mesh->indice_length; i++) {
        new_indices[i] = old_indices[i];
    }

    // Didn't get to filling in the edge triangles :((((

    Mesh *mesh = new Mesh();

    mesh->verts = new_verts;
    mesh->vert_length = new_vert_length;
    // TEST
    mesh->indices = new_indices;
    mesh->indice_length = new_indice_length;

    return mesh;

}

