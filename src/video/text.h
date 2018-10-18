#ifndef VIDEO_TEXT_H_
#define VIDEO_TEXT_H_
#include <stdint.h>

#define VIDEO_TEXT_WIDTH 40
#define VIDEO_TEXT_HEIGHT 25

void video_text_init();
void video_text_update();
void video_text_set(int x, int y, uint16_t cell);

#endif