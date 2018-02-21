namespace ogl {


struct ShaderGLSL {

  GLuint id;
  bool is_valid;
  bool is_released;

  ShaderGLSL();
  ShaderGLSL(const ShaderGLSL& other) = delete;
  ShaderGLSL& operator=(const ShaderGLSL& other) = delete;
  ShaderGLSL(ShaderGLSL&& other);
  ShaderGLSL& operator=(ShaderGLSL&& other);
  ~ShaderGLSL();

};


ShaderGLSL shader_glsl_create(Uniform* uniform_ary, size_t uniform_ary_size, const VertexLayout* layout_ary, size_t layout_ary_size, const char* vert_glsl, const char* frag_glsl);
void shader_glsl_destroy(ShaderGLSL& glsl);


} // namespace ogl
