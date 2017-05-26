/********************************************
*
*  @Author: Ricardo Flores
*  Date: 30 March 2017
*  Program - Morse Code (Arduino)
*  Email: rfloresc@icloud.com
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#define DOT_LENGTH  250  /* Define the length of a "dot" time in msec */

void dot(void);
void dash(void);
void makeOutput(char);
char checkInput(char);

int main(void)
{

    // Initialize appropriate DDR and PORT registers
    DDRB |= (1 << PB0);
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4); 

    while (1) {  // Loop Forever
    	if (checkInput(PB2) == 0){
    		dot();
    		dot();
    		dash(); 
    	}
    	else if (checkInput(PB3) == 0){
    		dot();
    		dot();
    		dot();
    	}
    	else if (checkInput(PB4) == 0){
    		dash();
    		dot();
    		dash();
    		dot();
    	}               
    }

    return 0;   /* never reached */
}

/*
  dot() - Makes the output LED blink a "dot".
*/
void dot()
{
	PORTB |= (1 << PB0);
	_delay_ms(DOT_LENGTH);
	PORTB &= ~(1 << PB0);
	_delay_ms(DOT_LENGTH);
}

/*
  dash() - Makes the output LED blink a "dash".
*/
void dash()
{
	PORTB |= (1 << PB0 ); 
	_delay_ms(DOT_LENGTH * 3);
	PORTB &= ~(1 << PB0);
	_delay_ms(DOT_LENGTH);

}

/*
  makeOutput() - Changes the output bit to either a zero or one.
  If the argument is zero, the bit is cleared to zero,
  otherwise it is set to a one.
*/
void makeOutput(char value)
{
    if (value == 0)
        PORTB &= ~(1 << PB0);
    else
        PORTB |= (1 << PB0);
}

/*
  checkInput(bit) - Checks the state of the input bit given as
  the argument (0-7), and returns either 0 or 1 depending on its state.
*/
char checkInput(char bit)
{
    if ((PIND & (1 << bit)) != 0)
        return(1);
    else
        return(0);
}