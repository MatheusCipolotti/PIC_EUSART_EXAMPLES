#include "config.h"
#include "defines.h"
#include "EUSART.h"
#include <xc.h>
#include <string.h>

char uart_rd;

void main(void){
    CMCON = 0x07;
    ADCON0 = 0x00;                  //Desabilita os conversores AD
    ADCON1 = 0x06;                  //Torna todo ADC digital
    
    TRISB = 0x00;
    TRISC = 0x80;
    PORTB = 0x00;
    PORTC = 0x00;
    
    //UART Init - BaudRate 9600
    SPBRG = 31;             //(Assincrono) Baud Rate = Fosc/(64(X+1))
    TXSTAbits.SYNC = 0;     //Configura modo assincrono
    TXSTAbits.TXEN = 1;     //Ativa envio de dados
    RCSTAbits.SPEN = 1;     //Ativar a porta Serial
    RCSTAbits.CREN = 1;     //Ativa o recebimento de dados
    
    while(1){
        uart_rd = UART_Read();
        if(uart_rd == 'A'){
            UART_Write_ln(uart_rd);
            UART_Write_Text_ln("LIGADO");
            uart_rd = 0;
            BOARDLED = 1;
        }
        else if(uart_rd == 'B'){
            UART_Write_ln(uart_rd);
            UART_Write_Text_ln("DESLIGADO");
            uart_rd = 0;
            BOARDLED = 0;
        }    
    }
}