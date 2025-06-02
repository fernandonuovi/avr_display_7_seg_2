#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7seg_init( void )
{
    DDRD  = 0xFF;
    PORTD = 0x00;
    DDRB |= (1<<2);
    DDRB |= (1<<1);
    PORTB &=~(1<<2);
    PORTB &=~(1<<1);
}

void disp7seg_unidade( unsigned char u )
{
    
	PORTB &=~(1<<1); // DESLIGA DEZENA
	PORTD = digitos7seg[u%10];
	PORTB |=(1<<2); // LIGANDO O UNIDADE

}

void disp7seg_dezena( unsigned char d )
{

	PORTB &=~(1<<2); // DESLIGANDO UNIDADE
	PORTD = digitos7seg[(d/10)%10];
	PORTB |=(1<<1); // LIGANDO DEZENA

}

int main(void) 
{
    char i = 0;
    long t = 0;
    disp7seg_init();

    while( 1 )
    {
        if(t%2)
        { 
            disp7seg_unidade (i);
        }

		else
		{
			disp7seg_dezena (i);

		}

        _delay_ms(1);

        // Incremento limitado: 0..15
        ++t;
        if(( t % 1000 )==0){
            i = ++i%100;
		}
    }
}


