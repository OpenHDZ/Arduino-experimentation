#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

float x=0.01;
float y,z;

float a = 10.;
float b = 28.;
float c = 2.66;
float dt =0.01;
float dx,dy,dz;

int xs,ys,old_x=160,old_y=120,n=250, m=250;

void setup(){
  Serial.begin(9600);
  tft.begin();  
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  delay(2000);
}

void loop(){
  dx = (a * (y -x)) * dt;
  x = x + dx;
  
  dy = (x*(b-z)-y)  * dt;
  y = y + dy;
  
  dz = ((x*y)-(c*z))* dt;
  z = z + dz;
  
  xs = int(((x)*4)+160);
  ys = int(((y)*4)+120);
  
  tft.drawLine(old_x,old_y,xs,ys,tft.color565(100,m,n));
  n=n-10;
  if (n == 0){
    n=0;
    m=m-20;
  }
  if (m > 256) {
    m=0;
  }
  
  Serial.print(x);
  Serial.print(y);
  Serial.println(z);
  old_x = xs;
  old_y = ys;
}

