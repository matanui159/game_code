#include "shader.h"
#include <ogl.h>

static unsigned g_vertex;

static unsigned shader_stage(unsigned type, const char* code) {
	unsigned stage = glCreateShader(type);
	glShaderSource(stage, 1, &code, NULL);
	glCompileShader(stage);
	return stage;
}

void video_shader_init() {
	g_vertex = shader_stage(GL_VERTEX_SHADER, VIDEO_SHADER_CODE(
		layout(location = 0) in vec4 vertex;
		layout(location = 1) in vec2 v_coord;
		layout(location = 2) in uint v_chr;

		out vec2 coord;
		out uint chr;

		void main() {
			coord = v_coord;
			chr = v_chr;
			gl_Position = vertex;
		}
	));
}

unsigned video_shader_create(const char* code) {
	unsigned fragment = shader_stage(GL_FRAGMENT_SHADER, code);
	unsigned shader = glCreateProgram();
	glAttachShader(shader, g_vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);
	glDetachShader(shader, fragment);
	glDeleteShader(fragment);
	return shader;
}

void video_shader_use(unsigned shader) {
	glUseProgram(shader);
}