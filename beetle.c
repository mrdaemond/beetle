/////////////////////////////////////////////////////////////////////////////////////
// D4 - левый зеленый светодиод
// D1 - правый зеленый светодиод
// MR1 - B7
// MR2 - B6
// ML1 - B5
// ML2 - B4

//#include <avr/interrupt.h>
#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/iotn2313.h>
#define i 16
char	LED, temp;
// *********************************************************************************
void LMS()		// Левый мотор СТОП
{
	PORTB = PORTB&207;
}
// *********************************************************************************
void LMF ()		// Левый мотор ВПЕРЕД
{
	PORTB = PORTB|16;
}
// *********************************************************************************
void LMR ()		// Левый мотор НАЗАД
{
	PORTB = PORTB|32;
}
// *********************************************************************************
void RMS ()		// Правый мотор СТОП
{
	PORTB = PORTB&63;
}
// *********************************************************************************
void RMF ()		// Правый мотор ВПЕРЕД
{
	PORTB = PORTB|64;
}
// *********************************************************************************
void RMR ()		// Правый мотор НАЗАД
{
	PORTB = PORTB|128;
}

// *********************************************************************************
// External Interrupt 0 service routine
// *********************************************************************************
SIGNAL	(SIG_INT0)	// правый сенсор
{
	PORTD = PORTD^16;
	LMF();
}
// *********************************************************************************
// External Interrupt 1 service routine
// *********************************************************************************
//SIGNAL	(SIG_INT1)
//{
//	PORTD = PORTD^2;
//}
// *********************************************************************************
void Init_interrupts()		//
{
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Any change
	// INT1: On
	// INT1 Mode: Any change
	// Interrupt on any change on pins PCINT0-7: Off
	GIMSK=0xC0;
	MCUCR=0x0A;
	EIFR=0xC0;


	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// Interrupt on any change on pins PCINT0-7: Off
	GIMSK=0x00;
	MCUCR=0x00;
}

// *********************************************************************************
// *********************************************************************************
// *********************************************************************************
void main(void)
{
CLKPR=0x80;
CLKPR=0x00;

PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=0 State5=0 State4=0 State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0xF0;

PORTB=0x08;
DDRB=0xFF;

// Port D initialization
// Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=Out Func0=Out 
// State6=0 State5=0 State4=1 State3=P State2=P State1=1 State0=0 
PORTD=0xff;
DDRD=0x0;

TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

Init_interrupts();

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Universal Serial Interface initialization
// Mode: Disabled
// Clock source: Register & Counter=no clk.
// USI Counter Overflow Interrupt: Off
USICR=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;

// Global enable interrupts
//sei ();		// общее разрешение прерываний
//D2, D3 - входы сенсоров
//D4, D1 - зеленые светодиоды
	
while (1)
{
	//temp = PIND;
	if ((PIND&4)>0)
	{
		LMS();
	}
	else
	{
		LMR();
	}


	if ((PIND&8)>0)
	{
		RMS();
	}
	else
	{
		RMR();
	}

}
}
