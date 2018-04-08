bool ogl::VertexLayout::operator==(const ogl::VertexLayout& other) const
{
  return (this->location == other.location &&
          this->format == other.format &&
          this->offset == other.offset &&
          this->stride == other.stride &&
          this->vbo_slot_idx == other.vbo_slot_idx &&
          this->name == other.name);
}

bool ogl::VertexLayout::operator!=(const ogl::VertexLayout& other) const
{
  return !(*this == other);
}
