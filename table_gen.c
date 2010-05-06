/*
 *  table_gen.c
 *  sin16
 *
 *  Created by Dave Dribin on 5/6/10.
 *  Copyright 2010 Bit Maki, Inc. All rights reserved.
 *
 */


#include <stdio.h>
#include <math.h>
#include "dd_sin8.h"

void trigint_sin8_table_gen()
{
    char * sep = "";
    int sine_table_size = trigint_sin8u_table_size();
	for (int i = 0; i < sine_table_size; i++) {
		double radians = i * M_PI_2 / (sine_table_size - 1);
		double sinValue = 127.0 * sin(radians) + 128.0;
		uint8_t tableValue = round(sinValue);
		printf("%s%3d", sep, tableValue);
        if (((i+1) % 8) == 0) {
            sep = ",\n";
        } else {
            sep = ", ";
        }
	}
    printf("\n");
}

int main(int argc, char * argv[])
{
    trigint_sin8_table_gen();
    return 0;
}