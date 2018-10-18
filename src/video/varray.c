#include "varray.h"
#include <ogl.h>
#include <stdbool.h>

static unsigned g_rect;

void video_varray_init() {
	const int8_t rect_data[] = {
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};

	glGenBuffers(1, &g_rect);
	glBindBuffer(GL_ARRAY_BUFFER, g_rect);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(rect_data), rect_data,
		GL_STATIC_DRAW
	);
}

unsigned video_varray_create() {
	unsigned varray;
	glGenVertexArrays(1, &varray);
	glBindVertexArray(varray);
	glBindBuffer(GL_ARRAY_BUFFER, g_rect);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_BYTE, false, 0, NULL);
	return varray;
}

void video_varray_use(unsigned varray) {
	glBindVertexArray(varray);
}