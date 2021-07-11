/*
  Rodin Fedor m3o-121b-20
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

struct Image {
  int mx;
  int my;
  int* points;
};

void createImage(Image* img, int x, int y) {
  img->points = new int[x * y]{0};
  img->mx = x;
  img->my = y;        
}

void showImage(Image* img) {
  for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			printf("%d", img->points[i * img->mx + j]);
		}
		printf("\n");
	}
}

void setPointImage(Image* img, int x, int y, int graycolor) {
  img->points[img->mx * y + x] = graycolor;
}

int getPointImage(Image* img, int x, int y) {
  return img->points[img->mx * y + x];  
}

void saveImage(Image* img, const std::string filename)
{
	std::fstream out;
	out.open(filename, std::fstream::out);

	out << "P1" << std::endl;
	out << img->mx << " " << img->my << std::endl;

	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			out << img->points[i * img->mx + j] << " ";
		}
		out << std::endl;
	}

	out.close();
}
    