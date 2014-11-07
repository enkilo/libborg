#warning "obsolete"
#include <cmath>
#include <iostream>
#include "gdmm.hpp"
#include <trash/gdmm.hpp>
#include "drawtest.hpp"

const int width = 200;
const int height = 200;

/*void draw(gd::Image &drawable)
{
//  std::cout << "clip: " << drawable.getClip() << std::endl;
  
  drawable.setAntiAliased(false);
  
  drawable.setFillColor(gd::Color(255,255,255));
  drawable.fillRect(0,0,width+2, height - 1);
  drawable.getFillColor();
  
  drawable.setFillColor(gd::Color(255,0,0));
  drawable.moveTo(0,0);
  drawable.lineTo(200,200);
  drawable.getFillColor();
  
  drawable.setFillColor(gd::Color(255,160,0));
  drawable.moveTo(100,100);
  drawable.lineTo(0,200);
  drawable.getFillColor();
  
  drawable.setFillColor(gd::Color(0,160,255));
  drawable.moveTo(50,100);
  drawable.lineTo(150,0);
  drawable.getFillColor();

  drawable.setFillColor(gd::Color(64,255,0));
  drawable.drawRect(50, 50, 100, 100);
  
  drawable.setFillColor(gd::Color(255,0,128));
  drawable.drawEllipse(50, 125, 150, 200);

  drawable.setFontColor(gd::Color(0,0,0));
  drawable.setFillColor(gd::Color(0,0,255));
  drawable.setFont(gd::fontVeryBig);
  drawable.drawString(20, 0, "test!");
  drawable.getFontColor();
  
  drawable.setFillColor(gd::Color(64,0,255));
  
#define deg(a) ((a) * M_PI / 180)
  
  drawable.fillArc(25, 100, 100, 80, 45, 135);
}*/

int main()
{
  gd::Image img(width, height, gd::TrueColor);
  wrap::dc<wrap::gdmm> draw(img);

  drawtest<wrap::dc<wrap::gdmm> >(draw);
  
  FILE *gif = fopen("test.gif", "wb");
  FILE *png = fopen("test.png", "wb");
  FILE *jpg = fopen("test.jpg", "wb");
  
//  draw(img);
  
  img.png(png);
  img.gif(gif);
  img.jpeg(jpg, 100);
  fclose(png);
  fclose(gif);
  fclose(jpg);
}
