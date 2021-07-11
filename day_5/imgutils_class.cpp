/*
  Rodin Fedor m3o-121b-20
*/

#include <iostream>
#include <fstream>
#include <string>

class Image 
{
  private:
    int mx;
    int my;
    int* points;

  public:
    Image() 
    {
      mx = 0;
      my = 0;
    }

    Image(int tmx, int tmy)
    {
      mx = tmx;
      my = tmy;
      points = new int[tmx * tmy]{0};
    }

    void setPointImage(int x, int y, int graycolor)
    {
      points[(y * mx + x)] = graycolor;
    }

    int getPointImage(int x, int y)
    {
      return points[y * mx + x];
    }

    void showImage() {
      for (int i = 0; i < my; i++)
      {
        for (int j = 0; j < mx; j++)
        {
          printf("%d", points[i * mx + j]);
        }
        printf("\n");
      }
    }

    void saveImage(const std::string filename)
    {
      std::fstream out;
      out.open(filename, std::fstream::out);
      
      out << "P1" << std::endl;
      out << mx << " " << my << std::endl;

      for (int i = 0; i < my; i++)
      {
        for (int j = 0; j < mx; j++)
          out << points[i * mx + j] << " ";
        
        out << std::endl;
      }

      out.close();
    }
};


int main()
{
  Image img(10, 10);

  for(int i = 0; i < 10; i++)
    img.setPointImage(i, i, 1);

  img.showImage();

  img.saveImage("hello_image.pnm");

  return 0;
}