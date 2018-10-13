#ifndef VIDEO_RECT_H_
#define VIDEO_RECT_H_
#include "matrix.h"

void video_rect_init();
void video_rect_draw(video_matrix_t* matrix, float r, float g, float b, float a);
void video_rect_flush();

#endif