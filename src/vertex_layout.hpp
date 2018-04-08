namespace ogl {

struct VertexLayout {

  uint8_t location = 0;
  VertexFormat format = VertexFormat::FLOAT3;
  size_t offset = 0;
  size_t stride = 0;
  uint8_t vbo_slot_idx = 0;
  const char* name = nullptr;

  bool operator==(const VertexLayout& other) const;
  bool operator!=(const VertexLayout& other) const;

};

} // namespace ogl
