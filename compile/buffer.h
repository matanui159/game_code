#ifndef WHEEL_BUFFER_H_
#define WHEEL_BUFFER_H_

void* wheel_buffer_resize(void* ptr, int size);
void wheel_buffer_destroy(void* ptr);

#endif