
#include <iostream>

#include "structs.h"
#include "EyeMeshData.hpp"
#include "optimize_mesh.h"
#include "export_mesh.h"
#include "file.h"
#include "invert_mesh.h"
#include "shrink_hole.h"

using namespace std;

int main () {

    cout << "Started!\n" << endl;

    // QUESTION 1
    Mesh *optimized_mesh = optimize_data(LeftEyeHiddenAreaPositions, LeftEyeHiddenAreaPositionsLength);
    cout << "Optimized mesh info:\nVert length: " << optimized_mesh->vert_length << "\nIndice length: " << optimized_mesh->indice_length << "\n" << endl;
    string obj_file = mesh_to_obj(optimized_mesh);
    write_to_file("eye_mesh.obj", obj_file);

    // QUESTION 2
    Mesh *inverted_mesh = invert_mesh(optimized_mesh);
    cout << "Inverted mesh info:\nVert length: " << inverted_mesh->vert_length << "\nIndice length: " << inverted_mesh->indice_length << "\n" << endl;
    string inverted_obj_file = mesh_to_obj(inverted_mesh);
    write_to_file("inverted_mesh.obj", inverted_obj_file);

    // QUESTION 3
    Mesh *shrunk_mesh = shrink_hole(optimized_mesh, 0.3f);
    cout << "Shurnk mesh info:\nVert length: " << shrunk_mesh->vert_length << "\nIndice length: " << shrunk_mesh->indice_length << "\n" << endl;
    string shrunk_obj_file = mesh_to_obj(shrunk_mesh);
    write_to_file("shrunk_mesh.obj", shrunk_obj_file);

    delete optimized_mesh;
    delete inverted_mesh;
    delete shrunk_mesh;

    cout << "Finished" << endl;

    return 0;

}

