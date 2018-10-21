#include "input.h"
#include <stdio.h>

int main() {
	FILE* test = fopen("test.txt", "wb");
	unsigned char data[] = {'A', 'B', 'C', 'D', 0xFF};
	fwrite(data, 1, sizeof(data), test);
	fclose(test);

	wheel_input_init("test.txt");

	char c;
	while ((c = wheel_input_next()) != 0) {
		printf("%c\n", c);
	}
}