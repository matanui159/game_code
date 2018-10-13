#include "rect.h"
#include <ogl.h>
#include <stdint.h>
#include <stdbool.h>

#define GL_UBYTE GL_UNSIGNED_BYTE
#define RECT_LIMIT 64

typedef struct rect_t {
	video_matrix_t matrix;
	struct {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	} color;
} rect_t;

#define RECT_BUFFER (RECT_LIMIT * sizeof(rect_t))

static rect_t* g_buffer;
static int g_count = 0;

static void rect_map() {
	g_buffer = glMapBufferRange(GL_ARRAY_BUFFER,
		0, RECT_BUFFER,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
	);
}

void video_rect_init() {
	unsigned array;
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);

	const float data[] = {
		0, 0, 1,
		1, 0, 1,
		0, 1, 1,
		1, 1, 1
	};

	unsigned rect;
	glGenBuffers(1, &rect);
	glBindBuffer(GL_ARRAY_BUFFER, rect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);

	unsigned buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, RECT_BUFFER, NULL, GL_STREAM_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(rect_t), (void*)0);
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(rect_t), (void*)12);
	glVertexAttribDivisor(2, 1);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_UBYTE, true, sizeof(rect_t), (void*)24);
	glVertexAttribDivisor(3, 1);

	rect_map();
}

void video_rect_draw(video_matrix_t* matrix, float r, float g, float b, float a) {
	g_buffer[g_count].matrix = *matrix;
	g_buffer[g_count].color.r = r * UINT8_MAX;
	g_buffer[g_count].color.g = g * UINT8_MAX;
	g_buffer[g_count].color.b = b * UINT8_MAX;
	g_buffer[g_count].color.a = a * UINT8_MAX;
	if (++g_count == RECT_LIMIT) {
		video_rect_flush();
	}
}

void video_rect_flush() {
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, g_count);
	rect_map();
	g_count = 0;
}