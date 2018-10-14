#include "shader.h"
#include "error.h"
#include <ogl.h>
#include <stdlib.h>
#include <stdio.h>

typedef PFNGLGETSHADERIVPROC glGetiv_t;
typedef PFNGLGETSHADERINFOLOGPROC glGetInfoLog_t;

static FILE* g_log;
static unsigned g_vertex;

static void shader_check(const char* name, unsigned obj, glGetiv_t glGetiv, glGetInfoLog_t glGetInfoLog, unsigned GL_STATUS) {
	int size;
	glGetiv(obj, GL_INFO_LOG_LENGTH, &size);
	if (size > 0) {
		char buffer[size];
		glGetInfoLog(obj, size, NULL, buffer);
		fprintf(g_log, "= %s LOG =\n%s\n", name, buffer);
	}

	int status;
	glGetiv(obj, GL_STATUS, &status);
	if (!status) {
		video_error("Invalid status");
	}
	video_error_gl();
}

static unsigned shader_stage(const char* name, unsigned type, const char* code) {
	unsigned stage = glCreateShader(type);
	glShaderSource(stage, 1, &code, NULL);
	glCompileShader(stage);
	shader_check(
		name,
		stage,
		glGetShaderiv,
		glGetShaderInfoLog,
		GL_COMPILE_STATUS
	);
	return stage;
}

void video_shader_init() {
	g_log = fopen("shader.log", "wb");
	setbuf(g_log, NULL);

	g_vertex = shader_stage("VERTEX", GL_VERTEX_SHADER, VIDEO_SHADER_CODE(
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
	unsigned fragment = shader_stage("FRAGMENT", GL_FRAGMENT_SHADER, code);
	unsigned program = glCreateProgram();
	glAttachShader(program, g_vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	shader_check(
		"PROGRAM",
		program,
		glGetProgramiv,
		glGetProgramInfoLog,
		GL_LINK_STATUS
	);

	glDetachShader(program, fragment);
	glDeleteShader(fragment);
	return program;
}

void video_shader_use(unsigned program) {
	glUseProgram(program);
}