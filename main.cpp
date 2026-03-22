# include <iostream>
# include <fstream>
# include <stdio.h>
# include <cstdint>
# include <cmath>

# define WIDTH 255
# define HEIGHT 255

struct double2 {
	double x,y;
};

struct Tri {
	double2 a, b, c;
};

double dotProduct(double2 a, double2 b) {
	return a.x * b.x + a.y * b.y;
}

double crossProduct2D(double2 a, double2 b) {
	return a.x * b.y - a.y * b.x;
}

double2 rotClockwise(double2 a) {
	return double2{a.y, -a.x};
}

double2 normalize(double2 vec) {
	double abs = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	return double2{vec.x/abs, vec.y/abs};
}

double2 vecFromPoints(double2 a, double2 b) {
	return double2{b.x - a.x, b.y - a.y};
}

bool isPointInTri(double2 point, Tri tri) {
	double2 ab = vecFromPoints(tri.a, tri.b);
	double2 bc = vecFromPoints(tri.b, tri.c);
	double2 ca = vecFromPoints(tri.c, tri.a);

	double2 ap = vecFromPoints(tri.a, point);
	double2 bp = vecFromPoints(tri.b, point);
	double2 cp = vecFromPoints(tri.c, point);

	double d1 = crossProduct2D(ab, ap);
	double d2 = crossProduct2D(bc, bp);
	double d3 = crossProduct2D(ca, cp);

	bool is_neg = (d1 < 0) && (d2 < 0) && (d3 < 0);
	bool is_pos = (d1 > 0) && (d2 > 0) && (d3 > 0);

	return is_neg || is_pos;

}

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
	remove("image.tga");
	std::ofstream image_file;
	image_file.open("image.tga");
	writeTargaHeaders(image_file, WIDTH, HEIGHT);

	Tri tri = Tri{{30.0, 20.0}, {240.0, 240.0}, {230.0, 40.0}};

	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			double2 point = double2{(double)j, (double)i};
			if(isPointInTri(point, tri)){
				image_file.put(0xFF);
				image_file.put(0x00);
				image_file.put(0x99);
			}
			else {
				image_file.put(0x00);
				image_file.put(0x00);
				image_file.put(0x00);
			}
		}
	}
	
	image_file.close();
	return 0;
}
