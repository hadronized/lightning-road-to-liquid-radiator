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
  string const VSPATH = "./data/01-vs.glsl";
  string const FSPATH = "./data/01-fs.glsl";
  float const OFF_FACTOR = 2.f;
  float const CUBE_VERTICES[] = {
     1.f,  1.f,  1.f,
     1.f, -1.f,  1.f,
    -1.f, -1.f,  1.f,
    -1.f,  1.f,  1.f,
     1.f,  1.f, -1.f,
     1.f, -1.f, -1.f,
    -1.f, -1.f, -1.f,
    -1.f,  1.f, -1.f
  };
  unsigned int const CUBE_INDICES[] = {
    /* front */
    0, 1, 2,
    0, 2, 3,
    /* back */
    4, 5, 6,
    4, 6, 7,
    /* left */
    0, 3, 6,
    0, 6, 7,
    /* right */
    1, 2, 4,
    3, 4, 5,
    /* top */
    0, 1, 4,
    0, 4, 7,
    /* back */
    2, 3, 5,
    3, 5, 6
  };
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

GLuint gen_offscreen_tex() {
  GLuint off;

  glGenTextures(1, &off);
  glBindTexture(GL_TEXTURE_2D, off);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1.f*WIDTH/OFF_FACTOR, 1.f*HEIGHT/OFF_FACTOR, 0, GL_RGB, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  return off;
}

GLuint gen_renderbuffer() {
  GLuint rbfo;

  glGenRenderbuffers(1, &rbfo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbfo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1.f*WIDTH/OFF_FACTOR, 1.f*HEIGHT/OFF_FACTOR);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  
  return rbfo;
}

GLuint gen_framebuffer() {
  GLuint fbo;

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  
  return fbo;
}

void gen_buffers(GLuint *buffers) {
  glGenBuffers(2, buffers); /* 0 for VBO, 1 for IBO */
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint gen_va(GLuint sp, GLuint *buffers) {
  GLuint va;
  GLuint coid;

  /* TODO: coid */
  coid = glGetAttribLocation(sp, "co");
  
  glGenVertexArrays(1, &va);
  glBindVertexArray(va);
  glEnableVertexAttribArray(coid);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glVertexAttribPointer(va, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
  glBindVertexArray(0);

  return va;
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
  
  auto offtex = gen_offscreen_tex();
  auto rbfo = gen_renderbuffer();
  auto fbo = gen_framebuffer();
  GLuint buffers[2];
  gen_buffers(buffers);
  auto va = gen_va(sp, buffers);
  float tf = 0.f;
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1f(time, tf);

    glBindVertexArray(va);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    SDL_GL_SwapBuffers();

    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT :
          loop = false;
          break;

        case SDL_KEYUP :
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE :
              loop = false;
              break;
            default :;
          }
          break;

        default :;
      }
    }
    
    tf += 0.01f;
  }

  glDeleteProgram(sp);
  SDL_Quit();
  return 0;
}
