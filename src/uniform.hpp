namespace ogl {


struct Uniform {

  GLint location = -1;
  VertexFormat format = VertexFormat::MAT4;
  const char* name = nullptr;

};


} // namespace ogl
