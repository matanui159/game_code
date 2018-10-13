#ifndef VIDEO_MATRIX_H_
#define VIDEO_MATRIX_H_

typedef struct video_matrix_t {
	float m00, m01, m02;
	float m10, m11, m12;
} video_matrix_t;

void video_matrix_identity(video_matrix_t* matrix);
void video_matrix_translate(video_matrix_t* matrix, float x, float y);
void video_matrix_scale(video_matrix_t* matrix, float width, float height);
void video_matrix_rotate(video_matrix_t* matrix, float angle);

#endif