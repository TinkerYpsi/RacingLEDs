#include <TT_Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 13
#define NUMPIXELS 45

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
TT_Adafruit_NeoPixel strip = TT_Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int first_player;
int second_player;
const int wait = 30;
const int button1 = 6;
const int button2 = 7;
int position1 = 0;          // where player 1 starts the race
int position2 = NUMPIXELS;  // where player 2 starts the race
int color1 = RED;
int color2 = BLUE;


void setup()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Ready, Set, Go!
  strip.theaterChase(RED, wait + 10);
  strip.theaterChase(YELLOW, wait);
  strip.theaterChase(GREEN, wait - 10);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

}

void loop()
{
  first_player = digitalRead(button1);
  second_player = digitalRead(button2);
  while(position1 < position2)
  {
    // both players pressed button simulataneously
    if(first_player == LOW && second_player == LOW)
    {
      strip.setPixelColor(position1, color1);
      ++position1;
      strip.setPixelColor(position2, color2);
      --position2;
    }
    else if(first_player == LOW)
    {
      strip.setPixelColor(position1, color1);
      ++position1;
    }
    else if(second_player == LOW)
    {
      strip.setPixelColor(position2, color2);
      --position2;
    }
  }

  // if player 1 won
  if(position1 > (NUMPIXELS / 2))
  {
    strip.theaterChase(color1, wait);
  }
  // if player 2 won
  else
  {
    strip.theaterChase(color2, wait);
  }
}
