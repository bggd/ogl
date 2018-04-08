ogl::VBO::VBO() : id(0), size(0), usage(0), is_valid(false), is_released(false)
{
}

ogl::VBO::VBO(ogl::VBO&& other) : id(other.id), size(other.size), usage(other.usage), is_valid(other.is_valid), is_released(other.is_released)
{
  other.id = 0;
  other.size = 0;
  other.usage = 0;
  other.is_valid = false;
  other.is_released = false;
}

ogl::VBO& ogl::VBO::operator=(ogl::VBO&& other)
{
  assert(this != &other);

  this->id = other.id;
  this->size = other.size;
  this->usage = other.usage;
  this->is_valid = other.is_valid;
  this->is_released = other.is_released;

  other.id = 0;
  other.size = 0;
  other.usage = 0;
  other.is_valid = false;
  other.is_released = false;

  return *this;
}

ogl::VBO::~VBO()
{
  if (this->is_valid) { assert(this->is_released); }
}

bool ogl::VBO::operator==(const ogl::VBO& other) const
{
  return (this->id == other.id &&
          this->size == other.size &&
          this->usage == other.usage &&
          this->is_valid == other.is_valid &&
          this->is_released == other.is_released);
}

bool ogl::VBO::operator!=(const ogl::VBO& other) const
{
  return !(*this == other);
}

ogl::VBO ogl::vbo_create(uint16_t size, const void* data)
{
  ogl::VBO vbo;
  vbo.size = size;
  vbo.usage = (data == NULL ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

  glGenBuffers(1, &vbo.id);

  if (vbo.id == 0) { return ogl::VBO{}; }

  glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
  glBufferData(GL_ARRAY_BUFFER, size, data, vbo.usage);

  GLint size_check;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size_check);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (size != size_check) {
    glDeleteBuffers(1, &vbo.id);
    return ogl::VBO{};
  }

  vbo.is_valid = true;

  return vbo;
}

void ogl::vbo_destroy(ogl::VBO& vbo)
{
  assert(vbo.id);
  assert(vbo.size);
  assert(vbo.is_valid);
  assert(vbo.is_released == false);
  glDeleteBuffers(1, &vbo.id);
  vbo.is_released = true;
}
