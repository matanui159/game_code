#ifndef VIDEO_SHADER_H_
#define VIDEO_SHADER_H_

void video_shader_init();
unsigned video_shader_create(const char* code);
void video_shader_use(unsigned shader);

#define VIDEO_SHADER_CODE(code) ("#version 330\n" #code)

#endif