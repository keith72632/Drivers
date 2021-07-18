/*
 * mem.c
 *
 *  Created on: Jul 18, 2021
 *      Author: keith
 */
#include <stdint.h>

void bzero(void *dest, unsigned int bytes)
{
	uint8_t *d = dest;
	while(bytes--)
		*d++ = 0;
}
