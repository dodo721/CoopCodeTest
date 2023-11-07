
#include "vert_utils.h"

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

void add_triangle (int *indices, int *new_indices, int &startIdx) {
    for (int i = 0; i < 3; i++) {
        new_indices[startIdx + i] = indices[i];
    }
    startIdx += 3;
}
