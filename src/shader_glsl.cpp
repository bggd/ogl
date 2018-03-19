ogl::ShaderGLSL::ShaderGLSL() : id(0), is_valid(false), is_released(false)
{
}

ogl::ShaderGLSL::ShaderGLSL(ogl::ShaderGLSL&& other) : id(other.id), is_valid(other.is_valid), is_released(other.is_released)
{
  other.id = 0;
  other.is_valid = 0;
  other.is_released = 0;
}

ogl::ShaderGLSL& ogl::ShaderGLSL::operator=(ogl::ShaderGLSL&& other)
{
  assert(this != &other);

  this->id = other.id;
  this->is_valid = other.is_valid;
  this->is_released = other.is_released;

  other.id = 0;
  other.is_valid = 0;
  other.is_released = 0;

  return *this;
}

ogl::ShaderGLSL::~ShaderGLSL()
{
  if (this->is_valid) { assert(this->is_released); }
}

ogl::ShaderGLSL ogl::shader_glsl_create(ogl::Uniform* uniform_ary, size_t uniform_ary_size, const ogl::VertexLayout* layout_ary, size_t layout_ary_size, const char* vert_glsl, const char* frag_glsl)
{
  ShaderGLSL glsl;
  glsl.id = glCreateProgram();

  assert(vert_glsl);
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vert_glsl, NULL);
  glCompileShader(vert);

  GLint status = GL_TRUE;
  glGetShaderiv(vert, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    glDeleteShader(vert);
    glDeleteProgram(glsl.id);
    return ogl::ShaderGLSL{};
  }

  assert(frag_glsl);
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &frag_glsl, NULL);
  glCompileShader(frag);

  status = GL_TRUE;
  glGetShaderiv(frag, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    glDeleteShader(vert);
    glDeleteShader(frag);
    glDeleteProgram(glsl.id);
    return ogl::ShaderGLSL{};
  }

  for (size_t i=0; i < layout_ary_size; ++i) {
    glBindAttribLocation(glsl.id, layout_ary[i].location, layout_ary[i].name);
  }

  glAttachShader(glsl.id, vert);
  glAttachShader(glsl.id, frag);
  glLinkProgram(glsl.id);

  status = GL_TRUE;
  glGetProgramiv(glsl.id, GL_LINK_STATUS, &status);

  if (status == GL_FALSE) {
    glDeleteShader(vert);
    glDeleteShader(frag);
    glDeleteProgram(glsl.id);
    return ogl::ShaderGLSL{};
  }

  glDetachShader(glsl.id, vert);
  glDetachShader(glsl.id, frag);

  glUseProgram(glsl.id);
  for (size_t i=0; i < uniform_ary_size; ++i) {
    uniform_ary[i].location = glGetUniformLocation(glsl.id, uniform_ary[i].name);
    if (uniform_ary[i].location == -1) {
      glDeleteProgram(glsl.id);
      return ogl::ShaderGLSL{};
    }
  }
  glUseProgram(0);

  glsl.is_valid = true;
  return glsl;
}

void ogl::shader_glsl_destroy(ogl::ShaderGLSL& glsl)
{
  assert(glsl.is_valid);
  assert(glsl.id);
  assert(glsl.is_released == false);

  glDeleteProgram(glsl.id);

  glsl.is_released = true;
}
