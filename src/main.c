#include "video/window.h"
#include "video/context.h"
#include "video/shader.h"
#include "video/matrix.h"
#include "video/rect.h"

int main() {
	video_window_init();
	video_context_init();
	video_shader_init();
	video_rect_init();

	unsigned shader = video_shader_create(VIDEO_SHADER_CODE(
		in vec2 coord;
		in vec4 color;

		out vec4 fcolor;

		void main() {
			fcolor = color;
		}
	));
	video_shader_use(shader);

	video_matrix_t matrix;
	video_matrix_identity(&matrix);
	video_matrix_rotate(&matrix, 1);

	for (;;) {
		video_rect_draw(&matrix, 1, 1, 1, 1);
		video_rect_flush();
		video_context_update();
	}
}