#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 64;
float angle = PI/60;

float cube3d[8][3] = {
  {xOff - cSize,yOff + cSize,zOff - cSize},
  {xOff + cSize,yOff + cSize,zOff - cSize},
  {xOff - cSize,yOff - cSize,zOff - cSize},
  {xOff + cSize,yOff - cSize,zOff - cSize},
  {xOff - cSize,yOff + cSize,zOff + cSize},
  {xOff + cSize,yOff + cSize,zOff + cSize},
  {xOff - cSize,yOff - cSize,zOff + cSize},
  {xOff + cSize,yOff - cSize,zOff + cSize}
};
unsigned char cube2d[8][2];

void setup() {
  Serial.begin(9600);
  Serial.println("Cube Test!"); 
 
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  delay(5000);
}

void loop() {
  
  int rsteps = random(10,60);
  switch(random(6)) {
    case 0:
      for (int i = 0; i < rsteps; i++) {
        zrotate(angle);
        printcube();
        
      }
      break;
    case 1:
      for (int i = 0; i < rsteps; i++) {
        zrotate(2*PI - angle);
        printcube();
      }
      break;
    case 2:
      for (int i = 0; i < rsteps; i++) {
        xrotate(angle);
        printcube();
      }
      break;
    case 3:
      for (int i = 0; i < rsteps; i++) {
        xrotate(2*PI - angle);
        printcube();
      }
      break;
    case 4:
      for (int i = 0; i < rsteps; i++) {
        yrotate(angle);
        printcube();
      }
      break;
    case 5:
      for (int i = 0; i < rsteps; i++) {
        yrotate(2*PI - angle);
        printcube();
      }
      break;
  }

}
void printcube() {
  //calculate 2d points
  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + (240/2));
    cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + (320/2));
  }
  //TV.delay_frame(1);
  
  tft.fillRect(40, 40, 200, 200,ILI9341_BLACK);
  draw_cube();
}

void zrotate(float q) {
  float tx,ty,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    ty = cube3d[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][1] = ty + yOff;
  }
}

void yrotate(float q) {
  float tx,tz,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    tz = cube3d[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][2] = tz + zOff;
  }
}

void xrotate(float q) {
  float ty,tz,temp;
  for(byte i = 0; i < 8; i++) {
    ty = cube3d[i][1] - yOff;
    tz = cube3d[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3d[i][1] = ty + yOff;
    cube3d[i][2] = tz + zOff;
  }
}

void draw_cube() {
  tft.drawLine(cube2d[0][0],cube2d[0][1],cube2d[1][0],cube2d[1][1],ILI9341_RED);
  tft.drawLine(cube2d[0][0],cube2d[0][1],cube2d[2][0],cube2d[2][1],ILI9341_RED);
  tft.drawLine(cube2d[0][0],cube2d[0][1],cube2d[4][0],cube2d[4][1],ILI9341_RED);
  tft.drawLine(cube2d[1][0],cube2d[1][1],cube2d[5][0],cube2d[5][1],ILI9341_RED);
  tft.drawLine(cube2d[1][0],cube2d[1][1],cube2d[3][0],cube2d[3][1],ILI9341_RED);
  tft.drawLine(cube2d[2][0],cube2d[2][1],cube2d[6][0],cube2d[6][1],ILI9341_RED);
  tft.drawLine(cube2d[2][0],cube2d[2][1],cube2d[3][0],cube2d[3][1],ILI9341_RED);
  tft.drawLine(cube2d[4][0],cube2d[4][1],cube2d[6][0],cube2d[6][1],ILI9341_RED);
  tft.drawLine(cube2d[4][0],cube2d[4][1],cube2d[5][0],cube2d[5][1],ILI9341_RED);
  tft.drawLine(cube2d[7][0],cube2d[7][1],cube2d[6][0],cube2d[6][1],ILI9341_RED);
  tft.drawLine(cube2d[7][0],cube2d[7][1],cube2d[3][0],cube2d[3][1],ILI9341_RED);
  tft.drawLine(cube2d[7][0],cube2d[7][1],cube2d[5][0],cube2d[5][1],ILI9341_RED);
  //delay(500);
}


