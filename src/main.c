#include "video/window.h"
#include "video/context.h"
#include "video/shader.h"

int main() {
	video_window_init();
	video_context_init();
	video_shader_init();

	unsigned shader = video_shader_create(VIDEO_SHADER_CODE(
		in vec2 coord;
		in vec4 color;

		out vec4 fcolor;

		void main() {
			fcolor = color;
		}
	));
	video_shader_use(shader);

	for (;;) {
		video_context_update();
	}
}