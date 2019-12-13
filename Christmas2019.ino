

#include <FastLED.h>
#include "Timer.h"

Timer t;

#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 200
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
#define LED_TYPE    WS2811
#define BRIGHTNESS  255

#define FPS 60

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];



// Flags and Toggles

bool hdran = false; // Has hue drops run
bool trainran = false;
bool pdran = false;
bool cdran = false; // Has Color Drops Run

// Timers
unsigned long time_now = 0;
unsigned long time_now2 = 0;

// Speed
int period = 10;

// Values That Need Be addressed
int changer = 0;
int changeg = 0;
int changeb = 0;

int i = 0;



// Chaos Arrays

int rchaos1[NUM_LEDS + 2];
int gchaos1[NUM_LEDS + 2];
int bchaos1[NUM_LEDS + 2];
int rchaos2[NUM_LEDS + 2];
int gchaos2[NUM_LEDS + 2];
int bchaos2[NUM_LEDS + 2];

// Random starting colors
CRGB cola = CRGB(0,0,0);
CRGB colb = CRGB(0,0,0);
CRGB colc = CRGB(0,0,0);
CRGB cold = CRGB(0,0,0);

// Fraction of blend/etc - interpolate
int fade = 0;


void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 10, starting at index 0 in the led array
  FastLED.addLeds<LED_TYPE, 1, RGB>(leds, 0, NUM_LEDS).setCorrection( UncorrectedTemperature );

  // tell FastLED there's 60 NEOPIXEL leds on pin 11, starting at index 60 in the led array
  //FastLED.addLeds<LED_TYPE, 10, RGB>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection( UncorrectedTemperature );

  // tell FastLED there's 60 NEOPIXEL leds on pin 12, starting at index 120 in the led array
  //FastLED.addLeds<NEOPIXEL, 12>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
      FastLED.setBrightness(  BRIGHTNESS );



random16_set_seed(analogRead(A0));

// Fill chaos arrays
for (int i = 0; i < (NUM_LEDS + 2); i++) {
  rchaos1[i] = random8();
  gchaos1[i] = random8();
  bchaos1[i] = random8();
  rchaos2[i] = random8();
  gchaos2[i] = random8();
  bchaos2[i] = random8();
}

cola = CRGB(random8(),random8(),random8());
colb = CRGB(random8(),random8(),random8());
colc = CRGB(random8(),random8(),random8());
cold = CRGB(random8(),random8(),random8());





// Set Up Loop that runs every frame (FPS)      
 t.every((1000/FPS), showleds, (void*)0);
}

void loop() {

   t.update();
  colordrops();
}

void showleds(void *context)
{
  FastLED.show();
}

void colordrops(){
trainran = false;
hdran = false;
pdran = false;



  
if (cdran == false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random8(),random8(),random8());
  }
  cdran = true;
}

if(millis() > time_now + period){ //check to see if a 'tick' has happened
    time_now = millis();
    i = random16(NUM_LEDS); // Choose a random LED

changer = random8();
changeg = random8();
changeb = random8();


    
    cola = CRGB(changer, changeg, changeb);
    }



    
if (millis() > time_now2 + (period/255)) {
  leds[i] = blend(leds[i], cola, fade);
time_now2 = millis();
  fade++;
}
if (fade == 255) fade = 0;

}
