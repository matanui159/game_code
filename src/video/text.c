#include "text.h"
#include "shader.h"
#include "varray.h"
#include <ogl.h>
#include <stdbool.h>

#define TEXT_CELLS (VIDEO_TEXT_WIDTH * VIDEO_TEXT_HEIGHT * 2)

static unsigned g_shader;
static unsigned g_varray;
static uint16_t* g_cell_data;

void video_text_init() {
	g_shader = video_shader_create(VIDEO_SHADER_CODE(
		out vec4 color;
		void main() {
			color = vec4(1);
		}
	));
	g_varray = video_varray_create();

	float rect_data[VIDEO_TEXT_WIDTH * VIDEO_TEXT_HEIGHT * 4];
	float cell_width = 2.0 / VIDEO_TEXT_WIDTH;
	float cell_height = 2.0 / VIDEO_TEXT_HEIGHT;
	for (int y = 0; y < VIDEO_TEXT_HEIGHT; ++y) {
		for (int x = 0; x < VIDEO_TEXT_WIDTH; ++x) {
			int i = (y * VIDEO_TEXT_WIDTH + x) * 4;
			rect_data[i + 0] = x * cell_width - 1;
			rect_data[i + 1] = y * cell_height - 1;
			rect_data[i + 2] = cell_width / 2;
			rect_data[i + 3] = cell_height / 2;
		}
	}

	unsigned rect;
	glGenBuffers(1, &rect);
	glBindBuffer(GL_ARRAY_BUFFER, rect);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(rect_data), rect_data,
		GL_STATIC_DRAW
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NULL);
	glVertexAttribDivisor(1, 1);

	unsigned cell;
	glGenBuffers(1, &cell);
	glBindBuffer(GL_ARRAY_BUFFER, cell);
	glBufferData(GL_ARRAY_BUFFER,
		TEXT_CELLS, NULL,
		GL_STREAM_DRAW
	);
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 1, GL_UNSIGNED_SHORT, 0, NULL);
	glVertexAttribDivisor(2, 1);

	g_cell_data = glMapBufferRange(GL_ARRAY_BUFFER,
		0, TEXT_CELLS,
		GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT
	);
}

void video_text_update() {
	glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, TEXT_CELLS);
	video_shader_use(g_shader);
	video_varray_use(g_varray);
	glDrawArraysInstanced(
		GL_TRIANGLE_STRIP,
		0, 4,
		VIDEO_TEXT_WIDTH * VIDEO_TEXT_HEIGHT
	);
}