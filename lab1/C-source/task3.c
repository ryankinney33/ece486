/*
 * Example program to illustrate the use of the ECE 486 interface.
 * 
 * An input waveform is copied to the output DAC.  The waveform is also
 * squared and streamed to the second DAC output.  Each
 * USER button press inverts the signal on the original DAC.
 * 
 * The use of printf(), the pushbutton, and the LCD is also illustrated.
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern FlagStatus KeyPressed;   // Use to detect button presses

int main(void)
{
  int nsamp, i;
  float *input, *output1, *output2;
  static float sign=1.0;
  static int button_count = 0;
  
  char lcd_str[8];

  /*
   * Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
   * 
   * If your discovery board has been modified to support the external 
   * HSE reference, use the (better quality crystal controlled) HSE 
   * configuration.  If not, you can use the MSI reference, and things 
   * should still work -- but your clocks will drift over time.
   * 
   * The MSI (Medium speed internal) reference is the on-chip RC oscillator
   * 
   * The HSE (High speed external) reference is an external clock, either
   * provided through the external connector, or (if your board is modified)
   * from the crystal reference source generated by the other processor
   * on the development board.
   */
  initialize_ece486(FS_50K, MONO_IN, STEREO_OUT, MSI_INTERNAL_RC);
  //initialize_ece486(FS_50K, MONO_IN, STEREO_OUT, HSE_EXTERNAL_8MHz);
  
  /*
   * Allocate Required Memory
   */
  nsamp = getblocksize();
	
  input = (float *)malloc(sizeof(float)*nsamp);
  output1 = (float *)malloc(sizeof(float)*nsamp);
  output2 = (float *)malloc(sizeof(float)*nsamp);
  
  if (input==NULL || output1==NULL || output2==NULL) {
    flagerror(MEMORY_ALLOCATION_ERROR);
    while(1);
  }
  
  /*
   * Normally we avoid printf()... especially once we start actually 
   * processing streaming samples.  This is here to illustrate the 
   * use of printf for debugging programs.
   * 
   * To see the printf output, connect to the ST-Link serial port.
   * Use: 115200 8N1
   */
  printf("Starting execution using %d samples per input block.\n",nsamp);
  
  /*
   * Infinite Loop to process the data stream, "nsamp" samples at a time
   */
  while(1){
    /*
     * Ask for a block of ADC samples to be put into the working buffer
     *   getblock() will wait here until the input buffer is filled...  On return
     *   we work on the new data buffer... then return here to wait for 
     *   the next block
     */
    getblock(input);	

    /*
     * signal processing code to calculate the required output buffers
     */
    
    DIGITAL_IO_SET(); 	// Use a scope on PD0 to measure execution time
    for (i=0; i<nsamp; i++) {
      output1[i] = sign * input[i];
      output2[i] = input[i]*input[i];
    }  
    DIGITAL_IO_RESET();	// (falling edge....  done processing data )
    
    /*
     * pass the processed working buffer back for DAC output
     */
    putblockstereo(output1, output2);
    
    if (KeyPressed) {
      KeyPressed = RESET;
      sign *= -1.0;		// Invert output1
      
      /*
       * On each press, modify the LCD display, and toggle an LED
       * (LED4=red, LED5=green) (Red is used to show error conditions)
       * 
       * Don't be surprised when these cause a Sample Overrun error, 
       * depending on your sample rate.
       */
      button_count++;
      sprintf(lcd_str, "BTN %2d", button_count);
      BSP_LCD_GLASS_DisplayString( (uint8_t *)lcd_str);
      BSP_LED_Toggle(LED5);
    }
  }
}