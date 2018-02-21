void ogl::bind_glsl(const ogl::ShaderGLSL& glsl)
{
  assert(glsl.is_valid);
  assert(glsl.is_released == false);
}

void ogl::bind_vbo(const ogl::VertexLayout* layout_ary, uint8_t layout_ary_size, const ogl::VBO* vbo_ary, uint8_t vbo_ary_size, const VertexLayout* cache_layout_ary, uint8_t cache_layout_ary_size, const ogl::VBO* cache_vbo_ary, uint8_t cache_vbo_ary_size)
{
  assert(cache_layout_ary && cache_layout_ary_size && cache_vbo_ary && cache_vbo_ary_size);
  assert(layout_ary_size <= cache_layout_ary_size);
  assert(vbo_ary_size <= cache_vbo_ary_size);

  bool same = true;
  for (uint8_t i=0; i < layout_ary_size; ++i) {
    if (cache_layout_ary[i]) { same = (same && layout_ary[i] == cache_layout_ary[i]); }
    else {
      same = false;
      break;
    }
  }
}
