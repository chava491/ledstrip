// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN 7

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 300

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); //](max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
    MovingBar(strip.Color(255,153, 204), 1);
    MovingBar(strip.Color(200,50,150), 1); //pinkish color
    MovingBar(strip.Color(255,255,255), 1);
    MovingBar(strip.Color(255, 0, 0), 1);
    MovingBar(strip.Color(0, 255, 0), 1);
    MovingBar(strip.Color(0, 0, 255), 1);
    fun(strip.Color(255,255,255),1);
    fun(strip.Color(255, 0, 0), 1);
    fun(strip.Color(0, 255, 0), 1);
    fun(strip.Color(0, 0, 255), 1);
    MovingBarBACKFORTH(strip.Color(255,255,255),1);
    MovingBarBACKFORTH(strip.Color(255,0,0),1);
    MovingBarBACKFORTH(strip.Color(0,255,0),1);
    MovingBarBACKFORTH(strip.Color(0,0,255),1);
    
}

  void fun(uint32_t color, int wait) {
    for (int i=0; i< strip.numPixels(); i++){
      strip.setPixelColor(i, color);
      strip.setPixelColor(i-1, 0,0,0);
      strip.show();
      if (i == (strip.numPixels()-1)) { //Has to be numPixels()-1 due to the declaration that number of pixels is 300, the index for the
                                        //LEDS however are from 0-299;
        strip.setPixelColor(i, 0,0,0);
      }
      //Following code is to reset the number so it loops --uncomment when it is the only thing running
          //if (i == strip.numPixels()){
            // i = 0;
           //}
    }
  }

 void MovingBar(uint32_t color, int wait) {
  for (int i=0; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, color);
      strip.setPixelColor(i-7, 0, 0, 0); //setPixelColor(index of LED, (R,G,B) VALUE);
      strip.show();

      if (i == (strip.numPixels() - 1)) {
       for (int l = (strip.numPixels() - 1); l > (strip.numPixels() - 8); l--) {
          strip.setPixelColor(l, 0,0,0);
          strip.show();
        }
      }
    }
  }

  void MovingBarBACKFORTH(uint32_t color, int wait){
    for (int n = 0; n < 3; n++){
      if (n == 0) {
        for (int i=0; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, color);
      strip.setPixelColor(i-7, 0, 0, 0); //setPixelColor(index of LED, (R,G,B) VALUE);
      strip.show();

      if (i == (strip.numPixels() - 1)) {
       for (int l = (strip.numPixels() - 1); l > (strip.numPixels() - 8); l--) {
          strip.setPixelColor(l, 0,0,0);
          strip.show();
            }
          }
        }
      }

      else if (n == 1) {
         for (int i = (strip.numPixels() - 1); i > -1; i--) { 
      strip.setPixelColor(i, color);
      strip.setPixelColor(i+7, 0, 0, 0); //setPixelColor(index of LED, (R,G,B) VALUE);
      strip.show();

      if (i == 0) {
       for (int l = 0; l < 8; l++) {
          strip.setPixelColor(l, 0,0,0);
          strip.show();
            }
          }
        }
      }
    }
  }
