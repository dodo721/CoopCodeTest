
#pragma once

#include "EyeMeshData.hpp"

// if a vertex has both (1 || 0) in X and Y, its in a corner
bool is_vertex_corner (Vertex2D &v);

// compare indice to previously stored list of corner indices
bool is_indice_corner (int indice, int *corners);

// for adding the top, bottom and side triangles after doing the rest of the tris
void add_side_triangle (int *side_indices, int center, int *new_indices, int &startIdx);

void add_triangle (int *indices, int *new_indices, int &startIdx);
