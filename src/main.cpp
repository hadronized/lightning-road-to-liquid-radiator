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
  string const VSPATH = "./data/vs.glsl";
  string const FSPATH = "./data/fs.glsl";
}

string load_source(string const &path) {
  ifstream fh(path.c_str());
  string s;

  if (fh) {
    stringstream ss;
    
    ss << fh.rdbuf();
    s = ss.str();
    fh.close();
  } else {
    throw "file not found: " + path;
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
    printf("Compilation error:\n%s", compilation_log(sh).c_str());
    return false;
  }
  
  return true;
}

GLuint gen_program() {
  GLuint vs, fs, sp;

  vs = glCreateShader(GL_VERTEX_SHADER);
  GLchar const *vssource = load_source(VSPATH).c_str();
  glShaderSource(vs, 1, &vssource, 0);
  compile_shader(vs);

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  GLchar const *fssource = load_source(FSPATH).c_str();
  glShaderSource(fs, 1, &fssource, 0);
  compile_shader(fs);

  sp = glCreateProgram();
  glAttachShader(sp, vs);
  glAttachShader(sp, fs);
  glLinkProgram(sp);
  glDeleteShader(vs);
  glDeleteShader(fs);

  GLint status;
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

GLint map_uniform(string const &name, GLuint sp) {
  GLchar const *n = name.c_str();
  GLint id = glGetUniformLocation(sp, n);
  return id;
}

int main() {
  SDL_Surface *pScreen = 0;
  SDL_Event event;
  bool loop = true;

  SDL_Init(SDL_INIT_VIDEO);

  pScreen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);

  auto sp = gen_program();
  glUseProgram(sp);
  auto res = map_uniform("res", sp);
  auto time = map_uniform("time", sp);
  if (res != -1) {
    cout << "res is active" << endl;
    glUniform2f(res, WIDTH, HEIGHT);
  }
  if (time != -1) {
    cout << "time is active" << endl;
  }
  float tf = 0.f;
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1f(time, tf);
    glRectf(-1.f,1.f,1.f,-1.f);
    SDL_GL_SwapBuffers();

    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT :
          loop = false;
          break;
      }
    }
    
    tf += 0.01f;
  }

  glDeleteProgram(sp);
  SDL_Quit();
  return 0;
}
