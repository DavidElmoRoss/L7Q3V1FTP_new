/*
    Modify this code so that when motion is NOT detected, the LCD
    shows a CYAN background, and when it is detected it shows a
    MAROON background. Refer to chart on Page 3 of Lab 6
    
    You should  get the message StoP Covid19   on the 4 digit display      
*/

// Include Section
#include "mbed.h"                   
#include "DigitDisplay.h" 
#include "Grove_LCD_RGB_Backlight.h"          

// Hardware definitions
DigitDisplay segment(D2,D3);
Grove_LCD_RGB_Backlight fred(D14,D15);          

// Global variables
unsigned char mess[]= {0x00,0x00,0x00,0x00,           
                       0x39,0x5c,0x1c,0x04,0x5e,0x06,0x67,                 
                       0x00,0x00,0x00,0x00}; 
unsigned short i;
InterruptIn PIR(D6);                          
// Global Variables
short bob=0;                      

// Asynchronous Interrupt Service Routine
void LOW(void)
{
   bob=1;                       
} 
int main(void)
{  
    PIR.fall(&LOW);                       
    segment.clear();                
    segment.setColon(0);            
    segment.setBrightness(4);
           
    
    for(;;)
    { 
                                                       // Statement to set LCD to CYAN
       if(bob==1)        
       {  
                                                      // Statement to set LCD to MAROON                             
          segment.writeRaw(0,0x6d);    
          segment.writeRaw(1,0x78);
          segment.writeRaw(2,0x3f);
          segment.writeRaw(3,0x73);  
          wait_ms(500);
          for(i=0;i<=11;++i)             
          {
             segment.writeRaw(&mess[i]); 
               wait_ms(250);
          }
          wait_ms(1000);                
          bob=0;
                                          // Statement to set LCD to CYAN  
        }
    }                       
}