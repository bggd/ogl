namespace ogl {


  struct VAO {

    static uint_fast64_t count;

    uint_fast64_t id;
    const ShaderGLSL* glsl;
    const VertexLayout* layout_ary;
    uint8_t layout_ary_size;
    const VBO* vbo_ary;
    uint8_t vbo_ary_size;
    bool is_valid;
    bool is_released;

    VAO();
    VAO(const ShaderGLSL* ctor_val_glsl);
    VAO(const VAO& other) = delete;
    VAO& operator=(const VAO& other) = delete;
    VAO(VAO&& other);
    VAO& operator=(VAO&& other);
    ~VAO();

  };

  VAO vao_create(const ShaderGLSL*, const VertexLayout* layout_ary, uint8_t layout_ary_size, const VBO* vbo_ary, uint8_t vbo_ary_size);
  void vao_draw_triangles(const VAO& vao, uint16_t first, uint16_t count);
  void vao_destroy(VAO& vao);

} // namespace ogl
