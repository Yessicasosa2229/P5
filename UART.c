#include "lib/include.h"

extern void Configurar_UART4(void)   
{
    SYSCTL->RCGCUART  |= (1<<4);   //Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable    1->Enable // 4 PORQUE ES EL UART4
    SYSCTL->RCGCGPIO |= (1<<2);     //Paso 2 (RCGCGPIO) pag.340 Enable clock port C
    //(GPIOAFSEL) pag.671 Enable alternate function
    GPIOC->AFSEL = (1<<4) | (1<<5); // pines 4 y 5
    //GPIO Port Control (GPIOPCTL) PC4-> U4Rx PC5-> U4Tx pag.688
    GPIOC->PCTL = (GPIOC    ->PCTL&0xFF00FFFF) | 0x00110000;// (1<<16) | (1<<20); //0x00110000 //pag 689 por el PM4 Y PM5
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOC->DEN |= (1<<4) | (1<<5);//PC4 PC5
    //UART4 UART Control (UARTCTL) pag.918 DISABLE!!
    UART4->CTL = (0<<9) | (0<<8) | (0<<0);   // Desabilitar UART

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    //ejemplo profe
    //no puede salir más de 255
    BRD = 20,000,000 / (16 * 9600) = 130.2
    UARTFBRD[DIVFRAC] = integer(0.2 * 64 + 0.5) = 14
    si el brd sale fraccional, solo se toma la parte entera
    
    
    //UART4 10MHz y 4800bps 
    BRD= 10,000,000 / (16 * 4800) = 130.2083
    UARTFBRD[DIVFRAC] = integer(0.2083 * 64 + 0.5) = 13.8 = 14

    */ 
    UART4->IBRD = 130;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART4->FBRD = 14;
    //  UART Line Control (UARTLCRH) pag.916
    UART4->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART4->CC =(0<<0);
    //Disable UART4 UART Control (UARTCTL) pag.918
    UART4->CTL = (1<<0) | (1<<8) | (1<<9);


 
}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART4->FR & (1<<4)) != 0 );
    v = UART4->DR & 0xFF;
    c = v;
    return c;
}
 extern void printChar(char c) // printchar solo imprime un caracter, imprime el valor de c
{
    while((UART4->FR & (1<<5)) != 0 );
    UART4->DR = c;
}
extern void printString(char* string) //printstring imprime una cadena
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern char * readString(char delimitador)
{

   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }

   return string;

}
//Experimento 2

//El envio es su nombre  (rave) 

// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 
// ()

