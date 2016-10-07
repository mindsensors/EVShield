/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*
For beginners tutorial (and user guide) visit:
http://www.openelectrons.com/docs/viewdoc/25
*/

#include <Wire.h>
#include <EVShield.h>
#define GLOBAL_DELAY 2

/**
  This is a simple example of blinking
	the EVShield LED with multiple colors.
*/
EVShield evshield(0x34,0x36);

void setup()
{
  Serial.begin(115200);

  evshield.init(SH_HardwareI2C);

  Serial.println ("Watch the LED on EVShield ...");
}

void loop()
{
    Serial.println ("into loop: Watch the LED on EVShield ...");
    multi_color_blink();
}

void multi_color_blink(){
 for (int i=255; i>=0; i--){
   if (i<=127) evshield.ledSetRGB(i,127-i,0);
   else    evshield.ledSetRGB(i,0,0);
   delay(GLOBAL_DELAY);
 }
 
 for (int i=128; i<=255; i++){
   evshield.ledSetRGB(0,i,0);
   delay(GLOBAL_DELAY/2);
 }

 for (int i=255; i>=0; i--){
   if (i<=127) evshield.ledSetRGB(0,i,127-i);
   else    evshield.ledSetRGB(0,i,0);
   delay(GLOBAL_DELAY);
 }

 for (int i=128; i<=255; i++){
   evshield.ledSetRGB(0,0,i);
   delay(GLOBAL_DELAY/2);
 }

 for (int i=255; i>=0; i--){
   if (i<=127) evshield.ledSetRGB(127-i,0,i);
   else    evshield.ledSetRGB(0,0,i);
   delay(GLOBAL_DELAY);
 }

 for (int i=128; i<=255; i++){
   evshield.ledSetRGB(i,0,0);
   delay(GLOBAL_DELAY/2);
 } 
}
