
#include "export_mesh.h"
#include "EyeMeshData.hpp"
#include <iostream>

using namespace std;

string mesh_to_obj (Mesh *mesh) {

    string obj = "";

    // vertices
    for (int i = 0; i < mesh->vert_length; i++) {
        Vertex2D v = mesh->verts[i];
        obj += "v " + to_string(v.X) + " " + to_string(v.Y) + " 0.0\n";
    }

    obj += "\n";

    // normals - all just face one way
    // done this way instead of via face so blender shades smooth
    for (int i = 0; i < mesh->vert_length; i++) {
        obj += "vn 0.0 0.0 1.0\n";
    }

    obj += "\n";

    // indices (faces)
    for (int i = 0; i < mesh->indice_length; i += 3) {
        // OBJ format is 1-based indexing >:(
        int idx1 = mesh->indices[i] + 1;
        int idx2 = mesh->indices[i + 1] + 1;
        int idx3 = mesh->indices[i + 2] + 1;
        obj += "f " + to_string(idx1) + " " + to_string(idx2) + " " + to_string(idx3) + "\n";
    }

    return obj;

}

