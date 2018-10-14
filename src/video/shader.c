#include "shader.h"
#include "error.h"
#include "rect.h"
#include <ogl.h>
#include <stdlib.h>
#include <stdio.h>

typedef PFNGLGETSHADERIVPROC glGetiv_t;
typedef PFNGLGETSHADERINFOLOGPROC glGetInfoLog_t;

static unsigned g_vertex;

static unsigned shader_stage(unsigned type, const char* code) {
	unsigned stage = glCreateShader(type);
	glShaderSource(stage, 1, &code, NULL);
	glCompileShader(stage);
	return stage;
}

void video_shader_init() {
	g_vertex = shader_stage(GL_VERTEX_SHADER, VIDEO_SHADER_CODE(
		layout(location = 0) in vec3 vertex;
		layout(location = 1) in vec3 row0;
		layout(location = 2) in vec3 row1;
		layout(location = 3) in vec4 vcolor;

		out vec2 coord;
		out vec4 color;

		void main() {
			coord = vertex.xy;
			color = vcolor.abgr;
			gl_Position = vec4(mat3x2(
				row0.x, row1.x,
				row0.y, row1.y,
				row0.z, row1.z
			) * vertex, 0, 1);
		}
	));
}

unsigned video_shader_create(const char* code) {
	unsigned fragment = shader_stage(GL_FRAGMENT_SHADER, code);
	unsigned program = glCreateProgram();
	glAttachShader(program, g_vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glDetachShader(program, fragment);
	glDeleteShader(fragment);
	return program;
}

void video_shader_use(unsigned program) {
	video_rect_flush();
	glUseProgram(program);
}