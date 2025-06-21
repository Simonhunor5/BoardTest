/*
 * udpserver.h
 *
 *  Created on: Apr 5, 2025
 *      Author: Huni
 */

#ifndef INC_UDPSERVER_H_
#define INC_UDPSERVER_H_

#include "stdint.h"
#include "lwip/udp.h"

typedef struct {
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
} ServoValues_t;

extern ServoValues_t g_servo_values;

void udp_server_start(void);



#endif /* INC_UDPSERVER_H_ */
