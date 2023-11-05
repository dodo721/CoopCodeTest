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

using namespace std;

// if a vertex has both (1 || 0) in X and Y, its in a corner
bool is_vertex_corner (Vertex2D &v) {
    return (v.X == 1 || v.X == 0) && (v.Y == 1 || v.Y == 0);
}

// compare indice to previously stored list of corner indices
bool is_indice_corner (int indice, int *corners) {
    for (int i = 0; i < 4; i++) {
        if (indice == corners[i]) {
            return true;
        }
    }
    return false;
}

// for adding the top, bottom and side triangles after doing the rest of the tris
void add_side_triangle (int *side_indices, int center, int *new_indices, int &startIdx) {
    new_indices[startIdx] = side_indices[0];
    new_indices[startIdx + 1] = center;
    new_indices[startIdx + 2] = side_indices[1];
    startIdx += 3;
}

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
    int tops[2];
    int topIdx = 0;
    int bottoms[2];
    int bottomIdx = 0;
    int lefts[2];
    int leftIdx = 0;
    int rights[2];
    int rightIdx = 0;

    for (int i = 0; i < eye_mesh->vert_length; i++) {
        Vertex2D v = old_verts[i];
        // omit the corners
        if (!is_vertex_corner(v)) {
            new_verts[new_vert_idx] = v;
            index_map[i] = new_vert_idx; // map old index to new
            
            // check if its a side vertex
            if (v.X == 0) {
                lefts[leftIdx] = new_vert_idx;
                leftIdx++;
            }
            if (v.X == 1) {
                rights[rightIdx] = new_vert_idx;
                rightIdx++;
            }
            if (v.Y == 0) {
                bottoms[bottomIdx] = new_vert_idx;
                bottomIdx++;
            }
            if (v.Y == 1) {
                tops[topIdx] = new_vert_idx;
                topIdx++;
            }
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
    add_side_triangle(tops, new_vert_idx, new_indices, startIdx);
    add_side_triangle(bottoms, new_vert_idx, new_indices, startIdx);
    add_side_triangle(lefts, new_vert_idx, new_indices, startIdx);
    add_side_triangle(rights, new_vert_idx, new_indices, startIdx);    

    Mesh *mesh = new Mesh();

    mesh->verts = new_verts;
    mesh->vert_length = new_vert_length;
    mesh->indices = new_indices;
    mesh->indice_length = new_indice_length;

    return mesh;

}
