#ifndef VIDEO_RECT_H_
#define VIDEO_RECT_H_
#include "matrix.h"
#include <stdint.h>

void video_rect_init();
void video_rect_draw(video_matrix_t* matrix, uint32_t color);
void video_rect_flush();

#endif