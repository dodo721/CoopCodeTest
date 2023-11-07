/**
 * TEST QUESTION 2
 * Inverts eye mesh to cover visible area
 * 
*/

#include "invert_mesh.h"

#include "structs.h"
#include "EyeMeshData.hpp"
#include <unordered_map>
#include <iostream>
#include "vert_utils.h"

using namespace std;

Mesh *invert_mesh (Mesh *eye_mesh) {

    Vertex2D *old_verts = eye_mesh->verts;
    int *old_indices = eye_mesh->indices;

    // New vert length = og length - corners + center = -4 + 1 = -3
    int new_vert_length = eye_mesh->vert_length - 3;
    Vertex2D *new_verts = (Vertex2D*)malloc(new_vert_length * sizeof(Vertex2D));
    // new indice length = new triangle length * 3 = old triangles + center top+bottom+sides = old triangles + 4 = old indices + 12
    int new_indice_length = eye_mesh->indice_length + 12;
    int *new_indices = (int*)malloc(new_indice_length * sizeof(int));

    int new_vert_idx = 0;
    // store corner indexes for skipping
    int corner_idxs[4];
    int corners_found = 0;

    // get a map of old indexes to new indexes
    // for preserving order later
    unordered_map<int, int> index_map;
    // record top, bottom and side indices too for side triangles
    SideIndices side_indices = {};

    for (int i = 0; i < eye_mesh->vert_length; i++) {
        Vertex2D v = old_verts[i];
        // omit the corners
        if (!is_vertex_corner(v)) {
            new_verts[new_vert_idx] = v;
            index_map[i] = new_vert_idx; // map old index to new
            
            // check if its a side vertex
            side_indices.add_side_vert(v, new_vert_idx);
            new_vert_idx++;
        } else {
            corner_idxs[corners_found] = i;
            corners_found++;
        }
    }

    // add the center vertex on the end
    new_verts[new_vert_idx] = {0.5, 0.5};
    // center vertex idx is now = new_vert_idx

    // we need to preserve the order of the circle vertexes
    // this is stored in the old indice data
    // we just need to replace corners with the center

    // THIS SHOULD BE FOR TRIANGLE LENGTH ==== divide by 3
    for (int i = 0; i < eye_mesh->indice_length / 3; i++) {
        int indice_idx = i*3;
        // only one of the next 3 indices should be a corner
        int indice_1 = old_indices[indice_idx];
        int indice_2 = old_indices[indice_idx + 1];
        int indice_3 = old_indices[indice_idx + 2];

        if (is_indice_corner(indice_1, corner_idxs))
            new_indices[indice_idx] = new_vert_idx; // if this is a corner, replace with the center
        else new_indices[indice_idx] = index_map[indice_1]; // map old index to new
        if (is_indice_corner(indice_2, corner_idxs))
            new_indices[indice_idx + 1] = new_vert_idx; // if this is a corner, replace with the center
        else new_indices[indice_idx + 1] = index_map[indice_2]; // map old index to new
        if (is_indice_corner(indice_3, corner_idxs))
            new_indices[indice_idx + 2] = new_vert_idx; // if this is a corner, replace with the center
        else new_indices[indice_idx + 2] = index_map[indice_3]; // map old index to new
    }

    // add top and bottom and side triangles using side verts
    int startIdx = new_indice_length - 12;
    add_side_triangle(side_indices.tops, new_vert_idx, new_indices, startIdx);
    add_side_triangle(side_indices.bottoms, new_vert_idx, new_indices, startIdx);
    add_side_triangle(side_indices.lefts, new_vert_idx, new_indices, startIdx);
    add_side_triangle(side_indices.rights, new_vert_idx, new_indices, startIdx);    

    Mesh *mesh = new Mesh();

    mesh->verts = new_verts;
    mesh->vert_length = new_vert_length;
    mesh->indices = new_indices;
    mesh->indice_length = new_indice_length;

    return mesh;

}
