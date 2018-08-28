/*
 * This Firmware keeps track of how many times a limit switch is triggered and displays it on 
 * a 16X2 LCD. 
 * 
 * Pinout
 * LCD VSS > Arduino UNO GND
 * LCD VDD > Arduino UNO 5V
 * LCD VO > Trimmer Potentiometer Wiper
 * LCD RS > Arduino UNO D12
 * LCD RW > Arduino UNO GND
 * LCD E > Arduino UNO D11
 * LCD D0 > N/A //Used for 8 bit
 * LCD D1 > N/A //Used for 8 bit
 * LCD D2 > N/A //Used for 8 bit
 * LCD D3 > N/A //Used for 8 bit
 * LCD D4 > Arduino UNO D10
 * LCD D5 > Arduino UNO D9
 * LCd D6 > Arduino UNO D8
 * LCD D7 > Arduino UNO D7
 * LCD A > 630 Ohm Resistor > Arduino UNO 5V
 * LCD K > Arduino UNO GND
 * 
 * LimitSwitch COM > Arduino UNO A0
 * Limit Switch N.O. > Arduino UNO 3.3V
 * Limit Switch N.C. > Arduino UNO GND
 * 
 * Reset Button Pin 1 > Arduino UNO GND
 * Reset Button Pin 2 > Arduino UNO RESET
 * 
 * Created by Lynton Brown 08/09/2018
 */
 
#include <LiquidCrystal.h> //Load Library for 16X2 LCD Screen

uint8_t LCD_RS=12,LCD_E=11,LCD_D4=10,LCD_D5=9,LCD_D6=8,LCD_D7=7,Limit_Switch=A0,limitSwitchReading,currentState,previousState; //Define unsigned int(s)
uint32_t count=0; //Define unsigned Long int(s)

LiquidCrystal LCDDisplay(LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7); //Define Pins for LCD

void setup() {
    Serial.begin(115200); //Open Serial Port with Baud Rate of 115200
    Serial.println("Counter"); //Send "Counter" to Serial Port
    
    LCDDisplay.begin(16, 2); //Begin and define LCDDisplay as a 16X2 LCD
    LCDDisplay.clear(); //Clear LCD Display
    LCDDisplay.print("Counter"); //Send "Counter" to LCD Display
    
    pinMode(Limit_Switch,INPUT); //Define pinmode for Limit Switch
    }

void loop() {
    limitSwitchReading = digitalRead(Limit_Switch); //Hold reading from Limit Switch as a variable
    if(limitSwitchReading==HIGH){ //If power is detected over limitSwitchReading Variable
        currentState=true; //Turn currentState to True
        }
    else{ //else if no power is detected over limitSwitchReading Variable
        currentState=false; //Turn currentState Variable to False
        }
    if(currentState!=previousState){ //If currentState Variable is not equal to previousState Variable 
        if(currentState==true){ //If currentState is True
            count++; //Increase count by 1
//            Serial.println(count); //Send Value of count Variable  to Serial Port //Debug
            LCDDisplay.clear(); //Clear LCD Display
            LCDDisplay.setCursor(0,1); //Set Start Point of LCD to column 0 row 1
            LCDDisplay.print(count); //Send Value of count to LCD Display
            }
        }
    previousState=currentState; //previousState is now the value of currentState before restarting loop
    }
