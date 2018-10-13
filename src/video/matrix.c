#include "matrix.h"
#include <math.h>

void video_matrix_identity(video_matrix_t* matrix) {
	matrix->m00 = 1;
	matrix->m01 = 0;
	matrix->m02 = 0;
	matrix->m10 = 0;
	matrix->m11 = 1;
	matrix->m12 = 0;
}

void video_matrix_translate(video_matrix_t* matrix, float x, float y) {
	matrix->m02 += x;
	matrix->m12 += y;
}

void video_matrix_scale(video_matrix_t* matrix, float width, float height) {
	matrix->m00 *= width;
	matrix->m01 *= width;
	matrix->m02 *= width;
	matrix->m10 *= height;
	matrix->m11 *= height;
	matrix->m12 *= height;
}

void video_matrix_rotate(video_matrix_t* matrix, float angle) {
	float c = cos(angle);
	float s = sin(angle);
	matrix->m00 = matrix->m00 * c - matrix->m10 * s;
	matrix->m01 = matrix->m01 * c - matrix->m11 * s;
	matrix->m02 = matrix->m02 * c - matrix->m12 * s;
	matrix->m10 = matrix->m10 * c + matrix->m00 * s;
	matrix->m11 = matrix->m11 * c + matrix->m01 * s;
	matrix->m12 = matrix->m12 * c + matrix->m02 * s;
}