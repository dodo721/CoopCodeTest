
#include <iostream>

#include "structs.h"
#include "EyeMeshData.hpp"
#include "optimize_mesh.h"
#include "export_mesh.h"
#include "file.h"
//#include "render.h"

using namespace std;

int main () {

    cout << "Started!" << endl;

    Mesh *optimized_mesh = optimize_data(LeftEyeHiddenAreaPositions, LeftEyeHiddenAreaPositionsLength);

    cout << "Optimized mesh info:\nVert length: " << optimized_mesh->vert_length << "\nIndice length: " << optimized_mesh->indice_length << endl;
    

    // render result to test
    //GLFWwindow *window = render_init(1024, 1024);

    string obj_file = mesh_to_obj(optimized_mesh);

    cout << "OBJ FILE\n" << obj_file << endl;

    write_to_file("eye_mesh.obj", obj_file);

    /*do {
		
		//render_update();

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 ); // Check if the ESC key was pressed or the window was closed

	render_cleanup();*/

    delete optimized_mesh;

    cout << "Finished" << endl;

    return 0;

}

