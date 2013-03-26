#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace {
  int const WIDTH = 800;
  int const HEIGHT = 600;
  int const DEPTH = 32;
  string const ROOTPATH = "./";
  string const VSPATH = "data/vs.glsl";
  string const FSPATH = "data/fs.glsl";
}

string load_source(string path) {
  ifstream fh(path.c_str());
  string s;

  if (fh) {
    stringstream ss;
    
    ss << fh.rdbuf();
    fh.close();
    s = ss.str();
  }

  return s;
}

string compilation_log(GLuint sh) {
  string log;
  GLint length;

  glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &length);
  log.resize(length);
  glGetShaderInfoLog(sh, length, &length, &log[0]);
  return log;
}

bool compile_shader(GLuint sh) {
  GLint status;

  glCompileShader(sh);
  glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    printf("Compilation error:\n%s", compilation_log);
    return false;
  }
  
  return true;
}

GLuint gen_program() {
  GLuint vs, fs, sp;

  vs = glCreateShader(GL_VERTEX_SHADER);
  auto *vssource = load_source(VSPATH).c_str();
  glShaderSource(vs, 1, &vssource, 0);
  glCompileShader(vs);
  GLint status;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint length;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
    string log;
    log.resize(length);
    glGetShaderInfoLog(vs, length, &length, &log[0]);
    cerr << "Vertex shader failed to compile:\n" << log << endl;
  }

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  auto *fssource = load_source(FSPATH).c_str();
  glShaderSource(fs, 1, &fssource, 0);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint length;
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
    string log;
    log.resize(length);
    glGetShaderInfoLog(fs, log.size(), &length, &log[0]);
    cerr << "Fragment shader failed to compile:\n" << log << endl;
  }

  sp = glCreateProgram();
  glAttachShader(sp, vs);
  glAttachShader(sp, fs);
  glLinkProgram(sp);
  glDeleteShader(vs);
  glDeleteShader(fs);

  glGetProgramiv(sp, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    GLint length;
    glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &length);
    string log;
    log.resize(length);
    glGetProgramInfoLog(sp, log.size(), &length, &log[0]);
    cerr << "Program failed to link:\n" << log << endl;
  }

  return sp;
}

int main() {
  SDL_Surface *pScreen = 0;
  SDL_Event event;
  bool loop = true;

  SDL_Init(SDL_INIT_VIDEO);

  pScreen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);

  auto sp = gen_program();
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapBuffers();

    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT :
          loop = false;
          break;
      }
    }
  }

  glDeleteProgram(sp);
  SDL_Quit();
  return 0;
}
