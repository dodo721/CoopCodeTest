
#pragma once

#include "EyeMeshData.hpp"
#include <functional>

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

