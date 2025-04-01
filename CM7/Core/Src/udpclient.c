/*
 * udpclient.c
 *
 *  Created on: Apr 1, 2025
 *      Author: Huni
 */


#include "udpclient.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "string.h"
#include "uarttest.h"
#include <stdio.h>

struct udp_pcb *upcb;

char buffer[100];

int counter = 0;

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port){
    strncpy(buffer, (char*)p->payload, p->len);
    buffer[p->len] = 0;
    UART_Send_Data("Received from server: %s\r\n", buffer);
    pbuf_free(p);
}

static void udp_client_send(){
    struct pbuf *txBuf;
    char data[100];

    int len = sprintf(data, "Sending UDP client message %d\r\n", counter++);
    txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    if(txBuf != NULL){
        pbuf_take(txBuf, data, len);
        udp_send(upcb, txBuf);
        pbuf_free(txBuf);
    }
}

void udp_client_periodic(){
    udp_client_send();
}

void udp_client_connect(){
    err_t err;

    upcb = udp_new();
    if (upcb == NULL) {
    	UART_Send_String("Failed to create UDP control block\r\n");
        return;
    }

    ip_addr_t myIPADDR;
    IP_ADDR4(&myIPADDR, 192, 168, 69, 123);
    udp_bind(upcb, &myIPADDR, 8);

    ip_addr_t destIPADDR;
    IP_ADDR4(&destIPADDR, 192, 168, 69, 100);

    err = udp_connect(upcb, &destIPADDR, 7);

    if(err == ERR_OK){
    	UART_Send_String("UDP client connected to server\r\n");
        udp_client_send();
        udp_recv(upcb, udp_receive_callback, NULL);
    } else {
    	UART_Send_String("UDP connect failed\r\n");
        udp_remove(upcb);
    }
}

