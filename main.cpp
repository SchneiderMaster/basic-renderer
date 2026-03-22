# include <iostream>
# include <fstream>
# include <stdio.h>
# include <cstdint>

# define WIDTH 255
# define HEIGHT 255

void writeTargaHeaders(std::ofstream& file, uint16_t width, uint16_t height) {
	// 1 byte ID length
	file.put(0x00);

	// 1 byte color map type 
	file.put(0x00);

	// 1 byte image type
	file.put(0x02);

	// 2 bytes palette start (none)
	file.put(0x00);
	file.put(0x00);

	// 2 bytes palette size (none)
	file.put(0x00);
	file.put(0x00);

	// 1 byte palette entry size (none)
	file.put(0x00);

	// 2 bytes x-start
	file.put(0x00);
	file.put(0x00);

	// 2 bytes y-start
	file.put(0x00);
	file.put(0x00);

	// 2 bytes width (little endian)
	file.put((char)(width & 0xFF));
	file.put((char)((width >> 8) & 0xFF));

	// 2 bytes height (little endian)
	file.put((char)(height & 0xFF));
	file.put((char)((height >> 8) & 0xFF));

	// 1 byte bits per pixel
	file.put(24);

	// 1 byte some attributes
	file.put(0x00);
}

int main() {
	std::cout << "Hello World" << std::endl;

	remove("image.tga");
	std::ofstream image_file;
	image_file.open("image.tga");
	writeTargaHeaders(image_file, WIDTH, HEIGHT);

	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			image_file.put(0x00);	// Blue
			image_file.put(((float)j/HEIGHT)*256);	// Green
			image_file.put(((float)i/WIDTH)*256);	// Red
		}
	}
	image_file.close();
	return 0;
}
