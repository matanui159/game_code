#ifndef VIDEO_TEXT_H_
#define VIDEO_TEXT_H_
#include <stdint.h>

void video_text_init();
void video_text_update();
void video_text_set(int x, int y, uint16_t chr);

#endif