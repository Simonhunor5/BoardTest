/*
 * udpserver.c
 *
 *  Created on: Apr 5, 2025
 *      Author: Huni
 */

#include "udpserver.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "uarttest.h"
#include <string.h>
#include <stdio.h>

ServoValues_t g_servo_values = {1500, 1500, 1500};  // Default neutral values

static struct udp_pcb *upcb;

static void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p,
                                 const ip_addr_t *addr, u16_t port) {
    if (p->len == 6) {
        int16_t values[3];
        memcpy(values, p->payload, sizeof(values));

        // Save globally
        g_servo_values.roll = values[0];
        g_servo_values.pitch = values[1];
        g_servo_values.yaw = values[2];

        // Optional debug print
        char msg[100];
        snprintf(msg, sizeof(msg), "Updated servo vals: R=%d P=%d Y=%d\r\n",
                 g_servo_values.roll, g_servo_values.pitch, g_servo_values.yaw);
        UART_Send_String(msg);
    } else {
        UART_Send_String("Invalid data length\r\n");
    }

    pbuf_free(p);
}

void udp_server_start() {
    upcb = udp_new();
    if (!upcb) {
        UART_Send_String("Failed to create UDP PCB\r\n");
        return;
    }

    ip_addr_t myIPADDR;
    IP_ADDR4(&myIPADDR, 192, 168, 69, 123);
    if (udp_bind(upcb, &myIPADDR, 7) != ERR_OK) {
        UART_Send_String("UDP bind failed\r\n");
        udp_remove(upcb);
        return;
    }

    UART_Send_String("UDP server listening on port 7\r\n");
    udp_recv(upcb, udp_receive_callback, NULL);
}



