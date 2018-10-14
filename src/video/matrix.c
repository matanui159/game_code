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
	matrix->m02 += matrix->m00 * x + matrix->m01 * y;
	matrix->m12 += matrix->m10 * x + matrix->m11 * y;
}

void video_matrix_scale(video_matrix_t* matrix, float width, float height) {
	matrix->m00 *= width;
	matrix->m01 *= height;
	matrix->m10 *= width;
	matrix->m11 *= height;
}

void video_matrix_rotate(video_matrix_t* matrix, float angle) {
	float c = cos(angle);
	float s = sin(angle);
	video_matrix_t temp = *matrix;

	matrix->m00 = temp.m00 * c + temp.m01 * s;
	matrix->m01 = temp.m01 * c - temp.m00 * s;
	matrix->m10 = temp.m10 * c + temp.m11 * s;
	matrix->m11 = temp.m11 * c - temp.m10 * s;
}