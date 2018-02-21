namespace ogl {

  struct VBO {

    GLuint id;
    uint16_t size;
    GLenum usage;
    bool is_valid;
    bool is_released;

    VBO();
    VBO(const VBO& other) = delete;
    VBO& operator=(const VBO& other) = delete;
    VBO(VBO&& other);
    VBO& operator=(VBO&& other);
    ~VBO();

    bool operator==(const VBO& other);

  };


  VBO vbo_create(uint16_t size, const void* data);
  void vbo_destroy(VBO& vbo);


} // namespace ogl
