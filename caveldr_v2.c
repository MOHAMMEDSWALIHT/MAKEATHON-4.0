#include<avr/io.h>
#include<util/delay.h>

void init_adc()

{
ADCSRA=ADCSRA|(0b00000001<<ADEN);	//enable adc
ADCSRA=ADCSRA|(0b00000001<<ADSC);	//enabling adsc to initiate analog to digital conversion
ADCSRA=ADCSRA|(0b00000001<<ADPS2);	//setting sampling rate
ADMUX=ADMUX|(0b00000001<<REFS0);	//set reference voltage
}

unsigned int read_adc_ldr()		//connected to ldr sensor
{
int p=0b00000001;			//selecting the adc5pin
ADMUX=ADMUX&0b11111000;			//check how to clear admux pin before setting it
ADMUX=ADMUX|p;
ADCSRA=ADCSRA|(0b00000001<<ADSC);
while((ADCSRA&(0b00000001<<ADIF))==0);
ADCSRA|=(0b00000001<<ADIF);
return(ADC);
}

unsigned int read_adc_pot()
{
int p=0b00000000;
ADMUX=ADMUX&0b11111000;
ADMUX=ADMUX|p;
ADCSRA=ADCSRA|(0b00000001<<ADSC);
while((ADCSRA&(0b00000001<<ADIF))==0);
ADCSRA|=(0b00000001<<ADIF);
return(ADC);
}

void main()
{
DDRB=0b11111111;
init_adc();

_delay_ms(500);
unsigned int a,b,q;
unsigned int p;

unsigned int T;
unsigned int TON;
unsigned int TOFF;

while(1)
{
p=read_adc_ldr();
q=read_adc_pot();
b=(q/40);
//a=(p/40);
T=25.6;
TOFF=b;

TON=T-TOFF;
int c = PIND;

if(p<900)	//ldr value < cave value
{
//go normally
if((c&0b00000010)==0b0000000)//common obstaclefor all cases
PORTB=0b00010000;//buzz and stop
if((c&0b00000111)==0b00000010)//no obstacle and going forward
PORTB=0b00001010;//go forward
if((c&0b00000111)==0b00000110)//no obstacle and turn right
PORTB=0b00000110; //turn right
//_delay_ms(100);
if((c&0b00000111)==0b00000011)//no obstacle and turn left
PORTB=0b00001001;//turn left
//_delay_ms(100);
if((c&0b00000111)==0b00000111)//no obstacle and cross road 
//buzz and go forward
PORTB=0b0011010;
}
else
{

if((c&0b00000111)==0b00000010)//no obstacle and going forward
{
PORTB=0b00001010;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
}//go forward
if((c&0b00000111)==0b00000110)//no obstacle and turn right
//turn right
{PORTB=0b00000110;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
}
if((c&0b00000111)==0b00000011)//no obstacle and turn left
//turn left
{PORTB=0b00001001;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
}
if((c&0b00000111)==0b00000111)//no obstacle and cross road 
//buzz and go forward
{
PORTB=0b00011010;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
}
}
/*
if(p<900)
{*/
//code for line follower
/*}
else 
{
{
PORTB=0b00001010;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
}*/
}
}
PORTB=0b00001010;
_delay_ms(TON);
PORTB=0b00000000;
_delay_ms(TOFF);
