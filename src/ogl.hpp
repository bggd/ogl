#pragma once


namespace ogl {
}


//#include <assert.h>
//#include <stdint.h>
//#include <stddef.h>

#include "info.hpp"
#include "vertex_format.hpp"
#include "vertex_layout.hpp"
#include "uniform.hpp"
#include "shader_glsl.hpp"
#include "vbo.hpp"
#include "gl_state.hpp"
#include "vao.hpp"

#define GAME_OGL_IMPL
#include "info.cpp"
#include "vertex_layout.cpp"
#include "shader_glsl.cpp"
#include "vbo.cpp"
#include "gl_state.cpp"
#include "vao.cpp"
