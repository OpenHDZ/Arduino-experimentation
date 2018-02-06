/*

Open Hardware Algerie

Sujet : experimentation manipulation des pixels des ecrans tft lcd avec la librairie Adafruit GFX

auteur : Areour Mohamed Cherif (OHA)

ce code source est sous licence Gpl v3

outils nécessaire : - une carte arduino
                    - ecrans 2.8" tft lcd shield de chez Adafruit industrie
*/
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// définition des pins de connexion pour l'écrans 
#define TFT_DC 9
#define TFT_CS 10

// définition des dimension de l'écrans 
#define x_center 160
#define y_center 120

// création d'une instance de la classe Adafruit_ILI9341 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

float x,y;
int xf,yf,n,d;

void setup() {
  
  // initialisation de l'ecrans 
  tft.begin();

  // rotation de l'écrans en mode paysage 
  tft.setRotation(1);

  // background en noir
  tft.fillScreen(ILI9341_BLACK);
  
  for (int i=1; i <= 13; i++){
      draw_rose(i,7); 
      delay(500);
      tft.fillScreen(ILI9341_BLACK);   
        
  }

  
}

void loop() {
  
}

void draw_rose(int n,int d){
  if (n==d);
  else{
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(2);
    tft.print("n = ");
    tft.println(n);
   /* tft.print("d = ");
    tft.println(d);
  */
    float k = n/float(d);
    for (float i=0.0 ; i < (6.28*d) ; i+=0.001)
    {
      x= 100*cos(k*i) * cos(i);
      y= 100*cos(k*i) * sin(i);
    
      xf = int(x) + x_center;
      yf = int(y) + y_center;
      tft.drawPixel(xf, yf, ILI9341_BLUE);
    }
  }
}
