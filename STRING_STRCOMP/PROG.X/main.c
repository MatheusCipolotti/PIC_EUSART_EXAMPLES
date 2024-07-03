/*
 * Recepcao de dados via UART - STRING e STRCOMP
 * 
 * MPLABX = V6.05
 * XC8 = V2.46
 * 
 * Autor = Matheus Dantas Cipolotti
 */

#include "config.h"
#include "defines.h"
#include "EUSART.h"
#include <xc.h>
#include <string.h>

char uart_rd[10];

void main(void){
    CMCON = 0x07;
    ADCON0 = 0x00;                                  //Desabilita os conversores AD
    ADCON1 = 0x06;                                  //Torna todo ADC digital
    
    TRISB = 0x00;
    TRISC = 0x80;
    PORTB = 0x00;
    PORTC = 0x00;
    
    //UART Init - BaudRate 9600
    SPBRG = 31;                                     //(Assincrono) Baud Rate = Fosc/(64(X+1))
    TXSTAbits.SYNC = 0;                             //Configura modo assincrono
    TXSTAbits.TXEN = 1;                             //Ativa envio de dados
    RCSTAbits.SPEN = 1;                             //Ativar a porta Serial
    RCSTAbits.CREN = 1;                             //Ativa o recebimento de dados
    
    while(1){
        UART_Read_Text(uart_rd,3);
        if (strcmp(uart_rd, "AAA") == 0){           //Verifica se a string recebida é "AAA"
            UART_Write_Text(uart_rd);               //Envia a string de volta
            BOARDLED = 1;
        }
        else if (strcmp(uart_rd, "DDD") == 0){      //Verifica se a string recebida é "DDD"
            UART_Write_Text(uart_rd);               //Envia a string de volta
            BOARDLED = 0;
        }
    }
}
