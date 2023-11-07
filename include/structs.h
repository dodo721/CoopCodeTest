
#pragma once

#include "EyeMeshData.hpp"
#include <functional>
#include <iostream>
#include "vert_utils.h"

using namespace std;

template <>
struct std::hash<Vertex2D>
{
  std::size_t operator()(const Vertex2D& v) const
  {
    using std::hash;

    return hash<float>()(v.X)
             ^ (hash<float>()(v.Y) << 1);
  }
};


struct Mesh {

    Vertex2D *verts;
    int vert_length;
    int *indices;
    int indice_length;

    ~Mesh () {
        free(verts);
        free(indices);
    }

};


// for storing the side vertices and reconnecting afterword (as in the default mesh they are disconnected)
struct SideIndices {

    int tops[2];
    int topIdx = 0;
    int bottoms[2];
    int bottomIdx = 0;
    int lefts[2];
    int leftIdx = 0;
    int rights[2];
    int rightIdx = 0;

    int corner_00;
    int corner_01;
    int corner_10;
    int corner_11;

    bool add_side_vert (Vertex2D &v, int indice) {

        if (is_vertex_corner(v)) {
            // not a side - but could be a corner, even if this ultimately returns false
            if (v.X == 0 && v.Y == 0) corner_00 = indice;
            if (v.X == 0 && v.Y == 1) corner_01 = indice;
            if (v.X == 1 && v.Y == 0) corner_10 = indice;
            if (v.X == 1 && v.Y == 1) corner_11 = indice;
            return false;
        }

        // check if its a side vertex
        if (v.X == 0) {
            lefts[leftIdx] = indice;
            leftIdx++;
            return true;
        }
        if (v.X == 1) {
            rights[rightIdx] = indice;
            rightIdx++;
            return true;
        }
        if (v.Y == 0) {
            bottoms[bottomIdx] = indice;
            bottomIdx++;
            return true;
        }
        if (v.Y == 1) {
            tops[topIdx] = indice;
            topIdx++;
            return true;
        }
        
        return false;
    }

    ~SideIndices () {
        // here to prevent attempts to delete array memory on stack
        // stack will clear itself
    }

};