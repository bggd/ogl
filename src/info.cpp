bool ogl::Info::is_initialized = false;
bool ogl::Info::is_gles = false;
uint8_t ogl::Info::major = 0;
uint8_t ogl::Info::minor = 0;


void ogl::Info::init(bool gles, uint8_t major, uint8_t minor)
{
  assert(ogl::Info::is_initialized == false);
  ogl::Info::is_gles = gles;
  ogl::Info::major = major;
  ogl::Info::minor = minor;
}

const char* ogl::Info::get_glsl_version()
{
  assert(ogl::Info::is_initialized);

  if (ogl::Info::is_gles) {
    if (ogl::Info::major == 2 && ogl::Info::minor == 0) { return "#version 100   "; }
    if (ogl::Info::major == 3 && ogl::Info::minor == 0) { return "#version 300 es"; }
  }
  else {
    if (ogl::Info::major == 3 && ogl::Info::minor == 3) { return "#version 330   "; }
  }

  abort();
}
