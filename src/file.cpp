
/**
 * File management utilities
*/

#include "file.h"
#include <fstream>

using namespace std;

string get_resource_path (string path) {
    return "../res/" + path;
}

string get_shader_path (string path) {
    return "../shaders/" + path;
}

void write_to_file (string filename, string contents) {
    
    ofstream file(get_resource_path(filename));
    file << contents;
    file.close();

}
