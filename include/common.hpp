#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <iostream>
#include <string>

float const PI = 3.14159265359;
bool const FULLSCREEN = false;
int const WIDTH = 800;
int const HEIGHT = 600;
float const IWIDTH = 1.f / WIDTH;
float const IHEIGHT = 1.f / HEIGHT;
float const RATIO = 1.f * WIDTH / HEIGHT;
int const DEPTH = 32;
float const FOVY = 75.*PI/180.;
float const ZNEAR = 0.01f;
float const ZFAR = 1000.f;
std::string const TRACK_PATH         = "./data/track.ogg";
std::string const STD_VS_PATH        = "./data/01-vs.glsl";
std::string const STD_TCS_PATH       = "./data/01-tcs.glsl";
std::string const STD_TES_PATH       = "./data/01-tes.glsl";
std::string const STD_FS_PATH        = "./data/01-fs.glsl";
std::string const STD_GS_PATH        = "./data/01-gs.glsl";
std::string const PP_VS_PATH         = "./data/01-pp-vs.glsl";
std::string const PP_FS_PATH         = "./data/01-pp-fs.glsl";
std::string const TUNNEL_FS_PATH     = "./data/02-fs.glsl";
std::string const SWAP_LINES_PATH_FS = "./data/swap_lines-fs.glsl";
std::string const THUN_VS_PATH       = "./data/thun-vs.glsl";
std::string const THUN_TCS_PATH      = "./data/thun-tcs.glsl";
std::string const THUN_TES_PATH      = "./data/thun-tes.glsl";
std::string const THUN_FS_PATH       = "./data/thun-fs.glsl";
std::string const THUN_BLUR_FS_PATH  = "./data/thun-blur-fs.glsl";
std::string const STD_LAVA_FS_PATH   = "./data/03-fs.glsl";
std::string const LAVA_RGBA_FS_PATH  = "./data/lava-rgba-fs.glsl";
std::string const FINAL_FS_PATH      = "./data/04-fs.glsl";

std::string load_source(std::string const &path);

#endif /* guard */

