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
		layout(location = 0) in vec2 vertex;
		layout(location = 1) in vec4 rect;
		layout(location = 2) in uint v_cell;

		out vec2 coord;
		out uint cell;

		void main() {
			coord = vertex;
			cell = v_cell;
			gl_Position = vec4(vertex * rect.zw + rect.xy, 0, 1);
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