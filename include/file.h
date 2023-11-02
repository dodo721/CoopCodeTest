
#pragma once

/**
 * File management utilities for fetching shaders and textures
*/

#include <string>

// For things like textures
std::string get_resource_path (std::string path);
// For shader files
std::string get_shader_path (std::string path);

void write_to_file(std::string filename, std::string contents);

