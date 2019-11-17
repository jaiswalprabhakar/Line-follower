/*
 * GccApplication2.c
 *
 * Created: 16-11-2019 18:32:04
 * Author : Prabhakar jaiswal
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>


int ir1=0,ir2=0,ir3=0,ir4=0,ir5=0;
int left_motor_line1 = 0;
int left_motor_line2 = 0;
int right_motor_line1 = 0;
int right_motor_line2 = 0;


/* 
	0 - Straight 
	1 - Sharp Left
	2 - Sharp Right
	3 - Smooth Left
	4 - Smooth Right
	5 - Stop

*/ 
// Type 1 - Left || 
// Type 0 - Right

/*

dir 1 - forward
dir 2 - stop
dir 3 - rev

*/
void set_motor(int type,int dir){
	if(type == 1){ // -------------- LEft Motor --------------------
		if(dir == 1){ // Forward Direction [ Left Motor ]
			
			left_motor_line1 = 1;
			left_motor_line2 = 0;
			
			PORTA |= 0b10000000;
			
		}
		
		if(dir == 2){ // Stop Now [ Left Motor ]
			
			left_motor_line1 = 0;
			left_motor_line2 = 0;
			PORTA |= 0b00000000;
		}
		
		if(dir == 3){ // Reverse Direction [ Left Motor ]
			
			left_motor_line1 = 0;
			left_motor_line2 = 1;
			PORTA = 0b01000000;
			}
	}else{ // -------------- Right Motor ------------------
		if(dir == 1){ // Forward Right Motor
			
			right_motor_line1 = 1;
			right_motor_line2 = 0;
			PORTA |= 0b00100000;
		
		}
		
		if(dir == 2){ // Stop Motor
			
			right_motor_line1 = 0;
			right_motor_line2 = 0;
			PORTA = 0b00000000;
		}
		if(dir == 3){ // Reverse Motor
			
			right_motor_line1 = 0;
			right_motor_line2 = 1;
			
			PORTA = 0b00010000;
			
		}
	}
	
	
	
}
int get_motor_state(int ir1,int ir2,int ir3,int ir4,int ir5){
	if(ir1 == 0 || ir2 == 0 || ir3 == 1 || ir4 == 0 || ir5 == 0)
		return 0; // 0 - means Straight Path
	if(ir1 == 1 || ir2 == 1 || ir3 == 1 || ir4 == 0 || ir5 == 0)
		return 1; // 1 - Sharp Left
	if(ir1 == 0 || ir2 == 0 || ir3 == 1 || ir4 == 1 || ir5 == 1)
	return 2;	// 2 - Sharp Right
	if(ir1 == 0 || ir2 == 1 || ir3 == 1 || ir4 == 0 || ir5 == 0)
	return 3; // 3- Smooth Left
	if(ir1 == 0 || ir2 == 0 || ir3 == 1 || ir4 == 1 || ir5 == 0)
	return 4;	// 4 - Smooth Right
	if((ir1 == 0 || ir2 == 1 || ir3 == 1 || ir4 == 0 || ir5 == 1)|| (ir1 == 0 || ir2 == 1 || ir3 == 1 || ir4 == 1 || ir5 == 0)
	||  (ir1 == 0 || ir2 == 1 || ir3 == 1 || ir4 == 1 || ir5 == 1)||(ir1 == 1 || ir2 == 0 || ir3 == 1 || ir4 == 1 || ir5 == 0)
	||	(ir1 == 1 || ir2 == 0 || ir3 == 1 || ir4 == 1 || ir5 == 1)||(ir1 == 1 || ir2 == 1|| ir3 == 1 || ir4 == 0|| ir5 == 1)
	||	(ir1 == 1 || ir2 == 1 || ir3 == 1 || ir4 == 1 || ir5 == 0)||(ir1 == 1|| ir2 == 1|| ir3 == 1 || ir4 == 1 || ir5 == 1)
	)
		return 5;
		
	else
		return 10;
	
}


int main(void)
{
   
   DDRA = 0b11110000;//output(last four pins of A)
   DDRD = 0b01111100;//input (sensor)
   
   

    while (1) 
    {
		
		int interpret = 0;
			// Getting Current State of Each IR Sensor
		if(bit_is_set(PIND,2))
			ir1 = 1;
		if(bit_is_set(PIND,3))
			ir2 = 1;
		if(bit_is_set(PIND,4))
			ir3 = 1;
		if(bit_is_set(PIND,5))
			ir4 = 1;
		if(bit_is_set(PIND,6))
			ir5 = 1;
		
		// Now Checking Logic for Vehicle Running Setup
		interpret = get_motor_state(ir1,ir2,ir3,ir4,ir5);
		/* 
	0 - Straight 
	1 - Sharp Left
	2 - Sharp Right
	3 - Smooth Left
	4 - Smooth Right
	5 - Stop

*/
		if(interpret == 0){ // Straight
			set_motor(1,1);
			set_motor(0,1);
		}
		if(interpret == 1){ // Sharp Left
			set_motor(1,3);
			set_motor(0,1);
		}
		if(interpret == 2){ // Sharp Right
			set_motor(1,1);
			set_motor(0,3);
		}
		if(interpret == 3){ // Smooth Left
			set_motor(1,2);
			set_motor(0,1);
		}
		if(interpret == 4){
			set_motor(1,1);
			set_motor(0,2);
		}
		if(interpret == 5){
			set_motor(1,2);
			set_motor(0,2);
		}
	
}

return 0;	
}

