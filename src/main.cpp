#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>

#include "shader.hpp"

using namespace std;

namespace {
  float PI = 3.14159265359;
  int const WIDTH = 800;
  int const HEIGHT = 600;
  float const RATIO = 1.f * WIDTH / HEIGHT;
  int const DEPTH = 32;
  float const FOVY = 75.*PI/180.;
  float const ZNEAR = 0.01f;
  float const ZFAR = 1000.f;
  string const STD_VS_PATH = "./data/01-vs.glsl";
  string const STD_FS_PATH = "./data/01-fs.glsl";
  string const PP_VS_PATH  = "./data/01-pp-vs.glsl";
  string const PP_FS_PATH  = "./data/01-pp-fs.glsl";
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
    2, 3, 6,
    3, 6, 7,
    /* right */
    0, 1, 4,
    1, 4, 5,
    /* top */
    0, 3, 4,
    3, 4, 7,
    /* back */
    1, 2, 5,
    2, 5, 6
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
  return fbo;
}

void setup_off(GLuint fbo, GLuint offtex, GLuint rbfo) {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbfo);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, offtex, 0);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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

GLuint setup_cube(GLuint sp, GLuint *buffers) {
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

struct mat4_c {
  float _[16];

  mat4_c(float *sub) {
    copy(sub, sub+16, _);
  }
  
  ~mat4_c(void) {
  }
};

mat4_c gen_perspective(float fovy, float ratio, float znear, float zfar) {
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

  return mat4_c(m);
}

bool treat_events(SDL_Event &event) {
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT :
        return false;

      case SDL_KEYUP :
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE :
            return false;

          default :;
        }
        break;

      default :;
    }
  }

  return true;
}

void render_one_frame(program_c const &stdP, program_c const &postprocessEffectP, GLuint offtex, GLuint rdbf, GLuint fb, GLuint cube) {
  /* offscreen */
  glUseProgram(stdP.id());
  glBindTexture(GL_TEXTURE_2D, offtex);
  glBindRenderbuffer(GL_RENDERBUFFER, rdbf);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fb);
  glBindVertexArray(cube);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  /* post-process */
  glUseProgram(postprocessEffectP.id());
  glRectf(-1.f, 1.f, 1.f, -1.f);
  glUseProgram(0); /* end of frame */
}

void main_loop() {
  SDL_Event event;
  bool loop = true;
  shader_c stdVS(GL_VERTEX_SHADER);
  shader_c stdFS(GL_FRAGMENT_SHADER);
  shader_c postprocessEffectVS(GL_VERTEX_SHADER);
  shader_c postprocessEffectFS(GL_FRAGMENT_SHADER);
  program_c stdP;
  program_c postprocessEffectP;

  /* standard program */
  stdVS.source(load_source(STD_VS_PATH).c_str());
  stdVS.compile();
  if (!stdVS.compiled()) {
    cerr << "STD Vertex shader failed to compile:\n" << stdVS.compile_log() << endl;
    exit(1);
  }
  stdFS.source(load_source(STD_FS_PATH).c_str());
  stdFS.compile();
  if (!stdFS.compiled()) {
    cerr << "STD Fragment shader failed to compile:\n" << stdFS.compile_log() << endl;
    exit(2);
  }
  stdP.attach(stdVS);
  stdP.attach(stdFS);
  stdP.link();
  if (!stdP.linked()) {
    cerr << "STD Program failed to link:\n" << stdP.link_log() << endl;
    exit(3);
  }
  /* postprocess program */
  postprocessEffectVS.source(load_source(PP_VS_PATH).c_str());
  postprocessEffectVS.compile();
  if (!postprocessEffectVS.compiled()) {
    cerr << "PP Vertex shader failed to compile:\n" << postprocessEffectVS.compile_log() << endl;
    exit(4);
  }
  postprocessEffectFS.source(load_source(PP_FS_PATH).c_str());
  postprocessEffectFS.compile();
  if (!postprocessEffectFS.compiled()) {
    cerr << "PP Fragment shader failed to compile:\n" << postprocessEffectFS.compile_log() << endl;
    exit(5);
  }
  postprocessEffectP.attach(postprocessEffectVS);
  postprocessEffectP.attach(postprocessEffectFS);
  postprocessEffectP.link();
  if (!postprocessEffectP.linked()) {
    cerr << "PP Program failed to link:\n" << postprocessEffectP.link_log() << endl;
    exit(6);
  }

  auto offtex = gen_offscreen_tex();
  auto rdbf = gen_renderbuffer();
  auto fbo = gen_framebuffer();
  setup_off(fbo, offtex, rdbf);
  GLuint cubeBuffers[2];
  gen_buffers(cubeBuffers);
  auto cube = setup_cube(stdP.id(), cubeBuffers);
  auto projection = gen_perspective(FOVY, RATIO, ZNEAR, ZFAR);
  auto projIndex = stdP.map_uniform("proj");
  auto offFactorIndex = stdP.map_uniform("off_factor");
  auto timeIndex = stdP.map_uniform("time");
  glUseProgram(stdP.id());
  glUniformMatrix4fv(projIndex, 1, GL_FALSE, projection._);
  glUniform1f(offFactorIndex, OFF_FACTOR);
  float time = 0.f;

  glEnable(GL_DEPTH_TEST);

  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(stdP.id());
    glUniform1f(timeIndex, time);
    render_one_frame(stdP, postprocessEffectP, offtex, rdbf, fbo, cube);
    SDL_GL_SwapBuffers();

    if (!treat_events(event))
      loop = false;

    time += 0.01f;
  }
}

int main() {
  SDL_Surface *pScreen = 0;
  SDL_Init(SDL_INIT_VIDEO);

  pScreen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);
  main_loop();
  return 0;
}
