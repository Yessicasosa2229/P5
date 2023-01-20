#include "lib/include.h"

int main(void)
{

    //uint16_t Result[2];
   // uint16_t duty[2];
   Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
   // Configurar_PLL(_20MHZ);
    //Configura_Reg_ADC0();
    Configurar_UART4();
    Configura_Reg_PWM1(50);//Configuro a 10khz el pwm
    while(1)
    {
       /* ADC0_InSeq2(Result,duty); //llamada a la conversion por procesador
        PWM0->_1_CMPB = duty[0];
        PWM0->_1_CMPA = duty[1];
        PWM0->_0_CMPA = 15000;*/
       
    }

}