#include <Wire.h>             
#include <Adafruit_MCP4725.h> 
#define analogVin A0

const int pwmout = 9;
const int pedalPwm = 2;
volatile unsigned long startTime = 0;
volatile unsigned long endTime = 0;
volatile unsigned long OverflowCounter;
unsigned long SuperMicrosValue;
volatile bool pulseDetected = false;

Adafruit_MCP4725 MCP4725;

ISR(TIMER2_OVF_vect) //overflow interupt
{
  OverflowCounter++;
}

unsigned long SuperMicros() //Thanks to: eRCaGuy & Nick Gammon
{
  uint8_t SREGbackup = SREG; 
  noInterrupts();
  uint8_t tcnt2Snapshot = TCNT2; //snapshot the counter
  boolean OverflowFlag = bitRead(TIFR2,0); //overflow flag
  if (OverflowFlag) { //if overflow is true
    tcnt2Snapshot = TCNT2;
    OverflowCounter++;
    TIFR2 |= 0b00000001; //reset overflow flag
  }
  SuperMicrosValue = OverflowCounter*256 + tcnt2Snapshot; //total count
  SuperMicrosValue = SuperMicrosValue * 10 / 2; //Convert to Micros times 10 to minimize floating points 1.5us = 15
  
  SREG = SREGbackup;
  return SuperMicrosValue;
}

void handleInterrupt() {
  if (digitalRead(pedalPwm) == HIGH) {
    startTime = SuperMicros();
  } else {
    endTime = SuperMicros();
    pulseDetected = true;
  }
}

void setup(void) {
  
  //Serial.begin(9600);
  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board
  pinMode(pedalPwm, INPUT);
  pinMode (pwmout, OUTPUT);

  // set ADC prescaler to 16 for faster analogread
  ADCSRA = bit(ADEN) | bit(ADPS2);
  ADCSRA &= ~_BV(ADPS1);
  ADCSRA &= ~_BV(ADPS0);

  TCCR1A = bit (COM1A1); // pin 9
  TCCR1B = bit (WGM13) | bit (CS10); //mode 8 no prescaler
  OCR1A = 37000; // duty cycle
  ICR1 = 40000; // frequency

  TCCR2A = 0; //clear
  TCCR2B = 0; //clear
  TCCR2B = bit (CS21); //set prescaler to 8
  TIMSK2 |= 0b00000001; //enable overflow interrupt

  OverflowCounter = 0;
  SuperMicrosValue = 0;
  
  attachInterrupt(digitalPinToInterrupt(pedalPwm), handleInterrupt, CHANGE);
}

void loop(void) {

    //float MCP4725_expected_output;
    int MCP4725_output;
    int analogVolt;

  if (pulseDetected) {
    unsigned long pulseDuration = endTime - startTime;
    pulseDuration = 50000 - pulseDuration; //flip flip
    //Serial.println(pulseDuration);
    //pulseDuration = (40000.0/50000) * pulseDuration; //Floating point
      pulseDuration = (40000UL * pulseDuration) / 50000; //Fix
    //Serial.println(pulseDuration);
    pulseDetected = false;
    OCR1A = pulseDuration;
    
  }
      
      
      //MCP4725_expected_output = (5.0/4096.0) * MCP4725_output;
        
        analogVolt = analogRead(analogVin);
        MCP4725_output = (4096.0/1023) * analogVolt; //Floating point
        //MCP4725_output = (4096 * analogVolt) / 1023; //Fix
        MCP4725.setVoltage(MCP4725_output, true);
      



      //Serial.print("MCP4725 Value: ");
      //Serial.print(MCP4725_output);
      
      //Serial.print("\tExpected Voltage: ");
      //Serial.print(MCP4725_expected_output,3);
    
}
