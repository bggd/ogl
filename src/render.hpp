namespace ogl {

  void bind_glsl(const ShaderGLSL& glsl);
  void bind_vbo(const VertexLayout* layout_ary, uint8_t layout_ary_size, const VBO* vbo_ary, uint8_t vbo_ary_size, const VertexLayout* cache_layout_ary, uint8_t cache_layout_ary_size, const VBO* cache_vbo_ary, uint8_t cache_vbo_ary_size);

} // namespace ogl
