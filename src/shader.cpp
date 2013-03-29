#include "shader_c.hpp"

/* =====================================
 * SHADER STAGE
 * =====================================
 */
shader_c::shader_c(GLenum type) :
  _(glCreateShader(type) {
}

shader_c::~shader_c() {
  glDeleteShader(_);
}

GLuint shader_c::id() const {
  return _;
}

void shader_c::source(char const *src) {
  glShaderSource(_, 1, &src, 0);
}

void shader_c::compile() {
  glCompileShader(_);
}

bool shader_c::compiled() {
  GLint status;

  glGetShaderiv(_, GL_COMPILE_STATUS, &status);
  return status == GL_TRUE;
}

std::string shader_c::compile_log() {
  string log;
  GLint length;

  glGetShaderiv(_, GL_INFO_LOG_LENGTH, &length);
  log.resize(length);
  getGetShaderInfoLog(_, length, &length, &log[0]);

  return log;
}

/* =====================================
 * SHADER PROGRAM
 * =====================================
 */
program_c::program_c() :
  _(glCreateProgram()) {
}

program_c::~program_c() {
  glDeleteProgram(_);
}

GLuint program_c::id() const {
  return _;
}

void program_c::attach(shader const &sh) {
  glAttachShader(_, sh.id());
}

void program_c::link() {
  glLinkProgram(_);
}

bool program_c::linked() const {
  GLint status;

  glGetProgramiv(_, GL_LINK_STATUS, &status);
  return status == GL_TRUE;
}

string program_c::link_log() const {
  string log;
  GLint length;

  glGetProgramiv(_, GL_INFO_LOG_LENGTH, &length);
  log.resize(length);
  glGetProgramInfoLog(_, length, &length, &log[0]);

  return log;
}
