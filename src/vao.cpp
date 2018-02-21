uint_fast64_t ogl::VAO::count = 0;

ogl::VAO::VAO() : ogl::VAO::VAO(nullptr)
{
}

ogl::VAO::VAO(const ogl::ShaderGLSL* ctor_val_glsl) : id(ogl::VAO::count++), glsl(ctor_val_glsl), layout_ary(nullptr), layout_ary_size(0), vbo_ary(nullptr), vbo_ary_size(0), is_valid(false), is_released(false)
{
}

ogl::VAO::VAO(ogl::VAO&& other) : id(other.id), glsl(other.glsl), layout_ary(other.layout_ary), layout_ary_size(other.layout_ary_size), vbo_ary(other.vbo_ary), vbo_ary_size(other.vbo_ary_size), is_valid(other.is_valid), is_released(other.is_released)
{
  other.id = 0;
  other.glsl = nullptr;
  other.layout_ary = nullptr;
  other.layout_ary_size = 0;
  other.vbo_ary = nullptr;
  other.vbo_ary_size = 0;
  other.is_valid = false;
  other.is_released = false;
}

ogl::VAO& ogl::VAO::operator=(ogl::VAO&& other)
{
  assert(this != &other);

  this->id = other.id;
  this->glsl = other.glsl;
  this->layout_ary = other.layout_ary;
  this->layout_ary_size = other.layout_ary_size;
  this->vbo_ary = other.vbo_ary;
  this->vbo_ary_size = other.vbo_ary_size;
  this->is_valid = other.is_valid;
  this->is_released = other.is_released;

  other.id = 0;
  other.glsl = nullptr;
  other.layout_ary = nullptr;
  other.layout_ary_size = 0;
  other.vbo_ary = nullptr;
  other.vbo_ary_size = 0;
  other.is_valid = false;
  other.is_released = false;

  return *this;
}

ogl::VAO::~VAO()
{
  if (this->is_valid) { assert(this->is_released); }
}

ogl::VAO ogl::vao_create(const ogl::ShaderGLSL* glsl, const ogl::VertexLayout* layout_ary, uint8_t layout_ary_size, const ogl::VBO* vbo_ary, uint8_t vbo_ary_size)
{
  assert(glsl);
  assert(glsl->is_valid);
  assert(glsl->is_released == false);
  assert(layout_ary);
  assert(layout_ary_size);
  assert(vbo_ary);
  assert(vbo_ary_size);

  for (uint8_t i=0; i < layout_ary_size; ++i) {
    ogl::VertexLayout layout = layout_ary[i];
    assert(layout.vbo_slot_idx < vbo_ary_size);
    assert(vbo_ary[layout.vbo_slot_idx].id);
    assert(vbo_ary[layout.vbo_slot_idx].is_valid);
    assert(vbo_ary[layout.vbo_slot_idx].is_released == false);
  }

  return ogl::VAO(glsl);
}

void ogl::vao_draw_triangles(const ogl::VAO& vao, uint16_t first, uint16_t count)
{
  assert(vao.glsl);
  assert(vao.glsl->is_valid);
  assert(vao.glsl->is_released == false);
  assert(vao.layout_ary);
  assert(vao.layout_ary_size);
  assert(vao.vbo_ary);
  assert(vao.vbo_ary_size);
  assert(vao.is_valid);
  assert(vao.is_released == false);

  GLuint prev_vbo_id = 0;
  const ogl::VBO* vbo_ary = vao.vbo_ary;

  if (ogl::GLState::cache.vao_id == vao.id) { goto GOTO_ogl_vao_draw_triangle_GOTO; }
  ogl::GLState::cache.vao_id = vao.id;

  for (uint8_t i=0; i < vao.layout_ary_size; ++i) {
    ogl::VertexLayout layout = vao.layout_ary[i];
    assert(layout.vbo_slot_idx < vao.vbo_ary_size);
    assert(vbo_ary[layout.vbo_slot_idx].id);
    assert(vbo_ary[layout.vbo_slot_idx].is_valid);
    assert(vbo_ary[layout.vbo_slot_idx].is_released == false);

    GLuint vbo_id = vbo_ary[layout.vbo_slot_idx].id;
    if (vbo_id == prev_vbo_id) { continue; }
    GLint size;
    switch(layout.format) {
      case ogl::VertexFormat::FLOAT2: { size = 2; break; }
      case ogl::VertexFormat::FLOAT3: { size = 3; break; }
      default: abort();
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glVertexAttribPointer(layout.location, size, GL_FLOAT, false, layout.stride, (const GLvoid*)layout.offset);
    prev_vbo_id = vbo_id;
  }

GOTO_ogl_vao_draw_triangle_GOTO:
  glDrawArrays(GL_TRIANGLES, first, count);
}

void ogl::vao_destroy(ogl::VAO& vao)
{
  assert(vao.glsl);
  assert(vao.glsl->is_valid);
  assert(vao.glsl->is_released == false);
  assert(vao.layout_ary);
  assert(vao.layout_ary_size);
  assert(vao.vbo_ary);
  assert(vao.vbo_ary_size);
  assert(vao.is_valid);
  assert(vao.is_released == false);

  vao.glsl = nullptr;
  vao.is_released = true;
}
