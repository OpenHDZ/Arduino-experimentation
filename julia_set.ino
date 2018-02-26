/*
 * Générateur de fractale de Julia sur plateforme Arduino
 */

/* Includes */
#include <SPI.h>              // Pour la communication avec l'écran
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Fonts/FreeMono9pt7b.h"

#define TFT_DC 9
#define TFT_CS 10

const uint16_t MAX_ITERATION = 300; // Nombre de couleurs
const uint16_t SCREEN_WIDTH  = 320; // 
const uint16_t SCREEN_HEIGHT = 240; // Taille de l'écran
static float zoom = 0.5;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
/* Fonction setup */
void setup() {
/* Initialise l'écran LCD */
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  delay(5000);

  tft.setFont(&FreeMono9pt7b);
}

/* Fonction loop() */
void loop() {
  /* Dessine la fractale */
  draw_Julia(-0.8,+0.156,zoom);
  tft.fillRect(0, 0, 150, 20, ILI9341_BLACK);
  tft.setCursor(0,15);
  tft.setTextColor(ILI9341_BLUE,ILI9341_BLACK);
  tft.print("Zoom = ");
  tft.println(zoom);
  delay(2000);
  zoom+=1.5;
}

/* 
  Dessine une fractale de Julia
 */

void draw_Julia(float c_r, float c_i, float zoom) {

  tft.setCursor(0,0);
  float new_r = 0.0, new_i = 0.0, old_r = 0.0, old_i = 0.0;

  /* Pour chaque pixel en X */

  for(uint16_t x = 0; x < SCREEN_WIDTH; x++) {
    /* Pour chaque pixel en Y */
    for(uint16_t y = 0; y < SCREEN_HEIGHT; y++) {      
      old_r = 1.5 * (x - SCREEN_WIDTH / 2) / (0.5 * zoom * SCREEN_WIDTH);
      old_i = (y - SCREEN_HEIGHT / 2) / (0.5 * zoom * SCREEN_HEIGHT);
      uint16_t i = 0;

      while ((old_r * old_r + old_i * old_i) < 4.0 && i < MAX_ITERATION) {
        new_r = old_r * old_r - old_i * old_i ;
        new_i = 2.0 * old_r * old_i;

        old_r = new_r+c_r;
        old_i = new_i+c_i;
        
        i++;
      }
      /* Affiche le pixel */
      if (i < 100){
        tft.drawPixel(x,y,tft.color565(255,255,map(i,0,50,255,0)));
      }if(i<200){
        tft.drawPixel(x,y,tft.color565(255,map(i,0,50,255,0),0));        
      }else{
        tft.drawPixel(x,y,tft.color565(map(i,0,50,255,0),0,0));
        
      }
    }
  }
}
float mapfloat(uint16_t x, uint16_t in_min, uint16_t in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
