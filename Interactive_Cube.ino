//LED/IR Sensor Control | Interactive LED cube
//Author: Brendan Li
//Date: 12/14/2021

//Using FastLED library
//Include and define as necessary
#include <FastLED.h>
#define LED_PIN     5
#define IR_PIN     3
#define NUM_LEDS    1
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

//WS2811 LED Strip
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
//void setup
void setup() {
    delay( 3000 ); // power-up safety delay
    //begin serial monitor and set IR sensor as input
    pinMode(IR_PIN,INPUT);
    Serial.begin(9600);
    //Setup LED strip parameters
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}

//Void loop
void loop()
{
    //Setting up LED strip output (single LED)
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    //If something is sensed, set LED to purple
    if (digitalRead(3)== LOW)
    {
      SetGreen();
      FastLED.show();
      delay(10);
    }
    //If nothing sensed, set LED to blue
    else 
    {
      SetBlue();
      FastLED.show();
      delay(10);
      
    }
}

//Function to set LED to blue
void SetBlue()
{
    CRGB blue = CHSV( HUE_BLUE, 255, 255);
    
    currentPalette = CRGBPalette16(blue);
}
//Function to set LED to green
void SetGreen()
{
    CRGB green = CHSV( HUE_GREEN, 255, 255);
    
    currentPalette = CRGBPalette16(green);
}

//preset function from FastLED
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
