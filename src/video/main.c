#include "../video.h"

int main() {
	video_init();
	unsigned shader = video_shader_create(VIDEO_SHADER_CODE(
		out vec4 color;
		void main() {
			color = vec4(1);
		}
	));
	video_window_show();

	for (;;) {
		video_shader_use(shader);
		video_update();
	}
	return 0;
}