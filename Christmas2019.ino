#include <Encoder.h>


#include <FastLED.h>

#include "Timer.h"
#include "ClickButton.h"

Timer t;

#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 100
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
#define LED_TYPE    WS2811
#define COLOR_CORRECTION UncorrectedTemperature
#define BRIGHTNESS  255

#define FPS 250

CRGB leds[NUM_LEDS];


const int buttonPin1 = 23;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);




// Flags and Toggles

bool hdran = false; // Has hue drops run
bool trainran = false;
bool pdran = false;
bool cdran = false; // Has Color Drops Run

// Timers
unsigned long time_now = 0;
unsigned long time_now2 = 0;

// Speed
int period = 100;

// Values That Need Be addressed
int changer = 0;
int changeg = 0;
int changeb = 0;

int raw = 255;
int gaw = 255;
int baw = 255;



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


Encoder myEnc(21, 22);
long oldPosition  = 255;

int clickers = 0;


void setup() {

  // tell FastLED there's 60 NEOPIXEL leds on pin 10, starting at index 0 in the led array
  FastLED.addLeds<LED_TYPE, 1, RGB>(leds, 0, NUM_LEDS_PER_STRIP).setCorrection( COLOR_CORRECTION );

  // tell FastLED there's 60 NEOPIXEL leds on pin 11, starting at index 60 in the led array
  FastLED.addLeds<LED_TYPE, 2, RGB>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection( COLOR_CORRECTION );

  // tell FastLED there's 60 NEOPIXEL leds on pin 12, starting at index 120 in the led array
 FastLED.addLeds<LED_TYPE, 3, RGB>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP).setCorrection( COLOR_CORRECTION );

 Serial.begin(9600);




  
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
  //whitey();
  //colordrops();
  //calibrator();
  train();
}

void showleds(void *context)
{
  FastLED.show();
  button1.Update();
  if (button1.clicks != 0) clickers = button1.clicks;
} 




/* Color Drops  Color Drops  Color Drops  Color Drops  Color Drops  Color Drops  Color Drops  Color Drops */

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



/* Calibrator  Calibrator  Calibrator  Calibrator  Calibrator  Calibrator  Calibrator  Calibrator  Calibrator */

void calibrator() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
if (button1.clicks == 0) {
raw = newPosition;
}
if (button1.clicks == 1) {
gaw = newPosition;
}
if (button1.clicks == 2) {
baw = newPosition;
}
if (button1.clicks == -1) {
newPosition = 255;
}

//fill_solid(leds, 300, CRGB(raw, gaw, baw));
  
fill_solid(leds, 300, CRGB::White);
  


}



// Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  Train  

void train() {

hdran = false;
cdran = false;


if(millis() > time_now + period){
    time_now = millis();
    fade++;
}


for (int i = 0; i < 300; i++) {
  leds[i] = blend(CRGB(rchaos1[(i+2)], gchaos1[(i+2)], bchaos1[(i+2)]), CRGB(rchaos1[(i+1)], gchaos1[(i+1)], bchaos1[(i+1)]), ease8InOutQuad(fade));
}

if (fade == 255) { 
  fade = 0;
rchaos1[0] = random8();
gchaos1[0] = random8();
bchaos1[0] = random8();
for (int i = 301; i > 0; i--) {
  rchaos1[i] = rchaos1[(i - 1)];
  gchaos1[i] = gchaos1[(i - 1)];
  bchaos1[i] = bchaos1[(i - 1)];
}
}


}


void whitey() {


fill_solid(leds,300, CRGB::White);
  
}


  
