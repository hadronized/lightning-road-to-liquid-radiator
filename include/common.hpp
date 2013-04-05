#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <string>

float const PI = 3.14159265359;
int const WIDTH = 800;
int const HEIGHT = 600;
float const RATIO = 1.f * WIDTH / HEIGHT;
int const DEPTH = 32;
float const FOVY = 75.*PI/180.;
float const ZNEAR = 0.01f;
float const ZFAR = 1000.f;
std::string const STD_VS_PATH = "./data/01-vs.glsl";
std::string const STD_FS_PATH = "./data/01-fs.glsl";
std::string const STD_GS_PATH = "./data/01-gs.glsl";
std::string const PP_VS_PATH  = "./data/01-pp-vs.glsl";
std::string const PP_FS_PATH  = "./data/01-pp-fs.glsl";

std::string load_source(std::string const &path);

#endif /* guard */

