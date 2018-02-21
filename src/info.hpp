namespace ogl {


struct Info {

  static bool is_initialized;
  static bool is_gles;
  static uint8_t major;
  static uint8_t minor;

  static void init(bool gles, uint8_t major, uint8_t minor);
  static const char* get_glsl_version();

};


} // namespace ogl
