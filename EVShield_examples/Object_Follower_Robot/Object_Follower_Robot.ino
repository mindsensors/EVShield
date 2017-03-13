#include <Wire.h>
#include <EVShield.h>
#include <EVs_NXTCam.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include <EVs_UIModule.h>
#define GLOBAL_DELAY 75

int Processtype=1;
uint8_t motor_status;
uint8_t stalled;

int             nblobs;
uint8_t         color[8];
uint8_t         left[8];
uint8_t         top[8];
uint8_t         bottom[8];
uint8_t         right[8];
byte  found = 1;


EVShield  evshield(0x34,0x36);
EVs_NXTCam myCam; 
EVs_UIModule uim = EVs_UIModule( 7, 8, 9 );

//NXShieldAGS ags[4];
void setup(){
  Serial.begin(115200);
  evshield.init(SH_HardwareI2C);
  uim.begin();
  evshield.bank_a.centerLedSetRGB(100,100,0);
  evshield.bank_a.ledSetRGB(100,100,0);
  evshield.bank_b.ledSetRGB(100,100,0);
  testText();
  delay(2000);
  uim.clearScreen();
  Serial.println("\nPress the GO Button to start program...\n");
  uim.writeLine(0,6,"Press Go to start Tracking",true,EVs_UIM_WHITE); 
 
  while(!evshield.getButtonState(BTN_GO)) 
{
  if(evshield.getButtonState(BTN_LEFT)) Processtype=1;
  if(evshield.getButtonState(BTN_RIGHT)) Processtype=2;
}

  myCam.init( &evshield, SH_BAS1 );
  myCam.disableTracking();
  myCam.selectObjectMode();
  myCam.sortSize();
  myCam.enableTracking();
  delay(1000);
  evshield.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
 // evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
  
  evshield.ledSetRGB(0,0,0);
        
  Serial.println("GO PRESSED, Program Started\n");
  uim.clearScreen();
  uim.writeLine(100,6,"Tracking",true,EVs_UIM_WHITE); 
  
}

#define DELAY_T 0

unsigned char x,y,w,h;
unsigned int area;
unsigned char  last_x = 0;
 

unsigned long testText() {
    uim.clearScreen();
    unsigned long start = micros();
    //uim.setCursor(0,15);
    //uim.println("EVShield");

    uim.setCursor(0,75);
    uim.setTextColor(EVs_UIM_WHITE);  uim.setTextSize(4);
    uim.println("EVShield");
    uim.setTextColor(EVs_UIM_YELLOW); uim.setTextSize(2);
    uim.println("OpenElectrons.com");
    uim.setTextColor(EVs_UIM_GREEN);    uim.setTextSize(2);
    uim.println("Arduino Shield for");
    uim.setTextColor(EVs_UIM_RED);    uim.setTextSize(2);
    uim.println("LEGO EV3 Sensors & Motors");
    uim.println();
    delay(500);
    return micros() - start;
}
/*
void loop1()
{
   myCam.getBlobs(&nblobs, color, left, top, right, bottom);
   if(nblobs > 0)
   {
     Serial.print("found "); Serial.println(nblobs);
     //delay(500); 
      
     x = (left[0]+right[0])/2;    //Center coordinates of the object
     y = (top[0]-bottom[0])/2;    //Center coordinates of the object
     w = (bottom[0]-top[0]);      //width of the object
     h = (right[0]-left[0]);      //height of the object
     area = w*h;
   } 
  else
  {
       Serial.println("Error: No blobs detected");
       //delay(500);
       evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
       evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
   } 
}

*/
void loop()
{
 char aa[80];
 char str[256];
 uint8_t  result;
 char str2[20];
   
   myCam.getBlobs(&nblobs, color, left, top, right, bottom);
   if(nblobs > 0)
   {
     found = 1;
     x = (left[0]+right[0])/2;    //Center coordinates of the object
     y = (top[0]-bottom[0])/2;    //Center coordinates of the object
     w = (bottom[0]-top[0]);      //width of the object
     h = (right[0]-left[0]);      //height of the object
     area = w*h;
     
     /*if(x > last_x){
       if(x - last_x < 10){
         x = last_x;
       }
     }
     else if(x < last_x){
       if(last_x - x < 10){
         x = last_x;
       }
     }
     else{
       x = x;
     }*/
          
     //uim.fillRect(x+80, y-150, w+20, h+20, EVs_UIM_YELLOW);
     
     if(x>100)    //5F=95
     {
       Serial.println("X is GREATER than center");
       Serial.println(x);
       
       evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, 1);
       evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Forward, 1); 
     }
 
     else if(0<x && x<60)  //0x41=65
     {
       Serial.println("X is LESS than center");
       Serial.println(x);
       
       evshield.bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 1);    
       evshield.bank_a.motorRunUnlimited(SH_Motor_2, SH_Direction_Reverse, 1); 
     }
     
     else      //(center is 80)
     {
       
       Serial.println("x is at center");
       Serial.print("area: ");
       Serial.println(area);
       
       if(area<450)
       {
          evshield.bank_a.motorRunUnlimited(SH_Motor_Both, SH_Direction_Reverse, 1);
          //evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Reverse, 1);     
       }
       else if(area>550)
       {
          evshield.bank_a.motorRunUnlimited(SH_Motor_Both, SH_Direction_Forward, 1);
          //evshield.bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, 1);     
       }
       else
       {
          evshield.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
          //evshield.bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
       }
      }
    }
    else
    {
      if(found == 1){
     
       Serial.println("Error: No blobs detected");
       evshield.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
      // evshield.bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);
       found = 0;  
       }  
    }
    last_x = x;
  
  // if the GO button is pressed, end the program
  if (evshield.getButtonState(BTN_GO)) {
    // reset the motors so the don't keep trying to follow the object
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();
    // indefinitely do nothing, until the reset button is pressed (on the Arduino) 
    while (1) ;
  }
}
 
