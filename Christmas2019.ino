#include <FastLED.h>
#include "Timer.h"

Timer t;


#define LED_PIN     5
#define NUM_LEDS    100
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 250





void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    t.every((1000/UPDATES_PER_SECOND), showleds, (void*)0);



  
}

void loop() {


  for (int l=0; l < 255; l++) {
    t.update();
  for (int i=0; i< NUM_LEDS; i++) {
    leds[i]= CHSV( (i*2.55)+l, 255 , 255);
  }
  }

}

void showleds(void *context)
{
  FastLED.show();
}
