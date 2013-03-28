#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace {
  float PI = 3.14159265359;
  int const WIDTH = 800;
  int const HEIGHT = 600;
  float const RATIO = 1.f * WIDTH / HEIGHT;
  int const DEPTH = 32;
  float const FOVY = PI/2;
  float const ZNEAR = 0.01f;
  float const ZFAR = 1000.f;
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
  ifstream fh;
  stringstream ss;

  fh.open(path);
  if (fh) {
    ss << fh.rdbuf();
    fh.close();
  } else {
    throw "file not found: " + path;
  }

  return ss.str();
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

GLuint gen_program(GLuint &vs, GLuint &fs) {
  GLuint sp;

  vs = glCreateShader(GL_VERTEX_SHADER);
  auto vsstr = load_source(VSPATH);
  GLchar const *vsp = &vsstr[0];
  glShaderSource(vs, 1, &vsp, 0);
  compile_shader(vs);

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  auto fsstr = load_source(FSPATH);
  GLchar const *fsp = &fsstr[0];
  glShaderSource(fs, 1, &fsp, 0);
  compile_shader(fs);

  sp = glCreateProgram();
  glAttachShader(sp, vs);
  glAttachShader(sp, fs);
  glLinkProgram(sp);

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
  GLint coid;

  coid = glGetAttribLocation(sp, "co");
  if (coid != -1)
    cout << "co is active" << endl;
  
  glGenVertexArrays(1, &va);
  glBindVertexArray(va);
    glEnableVertexAttribArray(coid);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexAttribPointer(coid, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
  glBindVertexArray(0);

  return va;
}

struct mat44_c {
  float _[16];

  mat44_c(float *sub) {
    copy(sub, sub+16, _);
  }
  
  ~mat44_c(void) {
  }
};

mat44_c gen_perspective(float fovy, float ratio, float znear, float zfar) {
  float itanfovy = 1.f / tan(fovy / 2);
  float itanfovyr = itanfovy / ratio;
  float inf = 1.f / (znear - zfar);
  float nfinf = (znear + zfar) * inf;
  float m[] = {
    itanfovyr,      0.f,   0.f,  0.f,
          0.f, itanfovy,   0.f,  0.f,
          0.f,      0.f,   inf, -1.f,
          0.f,      0.f, nfinf,  1.f
  };

  return mat44_c(m);
}

int main() {
  SDL_Surface *pScreen = 0;
  SDL_Event event;
  bool loop = true;

  SDL_Init(SDL_INIT_VIDEO);

  pScreen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);

  GLuint vs, fs;
  auto sp = gen_program(vs, fs);
  glUseProgram(sp);
  auto time = map_uniform("time", sp);
  auto proj = map_uniform("proj", sp);
  if (time != -1) {
    cout << "time is active" << endl;
  }
  if (proj != -1) {
    cout << "proj is active" << endl;
    auto m = gen_perspective(FOVY, RATIO, ZNEAR, ZFAR);
    glUniformMatrix4fv(proj, 1, GL_FALSE, m._);
  }
  
#if 0
  auto offtex = gen_offscreen_tex();
  auto rbfo = gen_renderbuffer();
  auto fbo = gen_framebuffer();
#endif
  GLuint buffers[2];
  gen_buffers(buffers);
  auto va = gen_va(sp, buffers);
  float tf = 0.f;
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1f(time, tf);

    glBindVertexArray(va);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

  glDeleteShader(vs);
  glDeleteShader(fs);
  glDeleteProgram(sp);
  SDL_Quit();
  return 0;
}
