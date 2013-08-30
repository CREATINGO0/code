/*

   Working
   - keyboard input is retrieved entirely driven by interrupts from timer2
   - timer0 counts seconds
   - input placed in array
   - lift moves up and down
   - motor turns at constant speed

 *	Connections:
 *	pc0-3 -> led0-3
 *	pc4-7 -> led4-7
 *	pb4-7 -> c0-3 (keypad)
 *	pe5-2 -> r0-3 (keypad)
 *	pd0-7 -> lcd0-7
 *	pa0-3 -> lcdBE-RS
 */

.include "m64def.inc"
.def temp =r16
.def row =r17
.def col =r18
.def mask =r19
.def temp2 =r23
.def del_lo =r24
.def del_hi =r25

.equ PORTBDIR = 0xF0
.equ INITCOLMASK = 0xEF
.equ INITROWMASK = 0x01
.equ ROWMASK = 0x0F
.set ARRAY_SIZE = 10

.MACRO CLEAR ; @0
	ldi YL, low(@0) ; load the memory address to Y
	ldi YH, high(@0)
	clr temp
	st Y+, temp ; clear the two bytes at @0 in SRAM
	st Y, temp
.ENDMACRO

; storing variables in the data memory
.dseg
	TempCounter:    .byte 2
	SecondCounter:  .byte 1
	Floors:			.byte ARRAY_SIZE
	CurrentFloor:	.byte 1
	Stopping:		.byte 1
	Directive:		.byte 1
	LiftWaiting:		.byte 1

.cseg
jmp RESET
jmp Default ; IRQ0 Handler
jmp Default ; IRQ1 Handler
jmp Default ; IRQ2 Handler
jmp Default ; IRQ3 Handler
jmp row0 ; IRQ4 Handler
jmp row1 ; IRQ5 Handler
jmp row2 ; IRQ6 Handler
jmp row3 ; IRQ7 Handler
jmp Default ; Timer2 Compare Handler
jmp timer2 ; Timer2 Overflow Handler
jmp Default ; Timer1 Capture Handler
jmp Default ; Timer1 CompareA Handler
jmp Default ; Timer1 CompareB Handler
jmp Default ; Timer1 Overflow Handler
jmp Default ; Timer0 Compare Handler
jmp timer0 ; Timer0 Overflow Handler

Default: reti

RESET:
	ldi temp, low(RAMEND)
	out SPL, temp
	ldi temp, high(RAMEND)
	out SPH, temp

; KEYPAD ;
	ldi temp, PORTBDIR		; columns are outputs, rows are inputs
	out DDRB, temp

	ldi temp, (3 << ISC70) | (3 << ISC60) | (3 << ISC50) | (3 << ISC40)
        ;setting the interrupts for rising edge
	out EICRB, temp
        ;storing them into EICRB (INT4-7)
	in temp, EIMSK
	ori temp, (1<<INT4 | 1<<INT5 | 1<<INT6 | 1<<INT7)
        ;enabling row interrupts
	out EIMSK, temp 

	ldi mask, INITCOLMASK	; initial column mask
	out PORTB, mask 		; set column to mask value (sets column 0 off)
	clr col

	
; MEMORY SPACE ;
	ldi temp, 0
	ldi temp2, 10
	ldi yl, low(Floors)
	ldi yh, high(Floors)

initArray:					; initialise array to zeros
	st y+, temp
	dec temp2
	brne initArray

	ldi yl, low(CurrentFloor)	; initialise variables
	ldi yh, high(CurrentFloor)
	st y, temp
	
	ldi yl, low(Stopping)
	ldi yh, high(Stopping)
	st y, temp

	ldi yl, low(LiftWaiting)
	ldi yh, high(LiftWaiting)
	st y, temp

; TIMERS ;
	clr temp
	ldi r28, low(TempCounter)
	ldi r29, high(TempCounter)
	st y+, temp
	st y, temp

	ldi r28, low(SecondCounter)
	ldi r29, high(SecondCounter)
	st y, temp

	ldi temp, 2				; prescaling value of 8
	out TCCR0, temp
	ldi temp, 3				; prescaling value of 64
	out TCCR2, temp
	ldi temp, (1<<TOIE2)	; enable timer0 overflow
	out TIMSK, temp



; DISPLAY ;
	ser temp
	out DDRC, temp			; Make PORTC all outputs
	rcall lcd_init
	ldi data, 48
	rcall lcd_wait_busy
	rcall lcd_write_data

	sei			; enable global interrupts	
	rjmp main

going_up:
	ldi temp, 0b10000000
	out PORTC, temp
	ldi yl, low(CurrentFloor)
	ldi yh, high(CurrentFloor)
	ld r20, y

	ldi zl, low(SecondCounter)
	ldi zh, high(SecondCounter)
	ld temp2, z
	cpi temp2, 2
	brne no_floor_change
	inc r20
	st y, r20

	rcall lcd_wait_busy		; Wait until the LCD is ready
	ldi data, LCD_DISP_CLR
	rcall lcd_write_com
	ldi data, 48
	add data, r20
	rcall lcd_wait_busy
	rcall lcd_write_data

	clr temp2
	st z, temp2			; SecondCounter set to 0

	ldi yl, low(Directive)
	ldi yh, high(Directive)		; reload directive
	ld r21, y
	cp r20, r21					; currentfloor v directive
	brne not_dest
	jmp destination

not_dest:
	ldi yl, low(Stopping)
	ldi yh, high(Stopping)
	ld r22, y
	cpi r22, 1				; if stopping, open doors
	brne skip_doors
	rcall operate_doors

no_floor_change:
skip_doors:
	ldi yl, low(Floors)
	ldi yh, high(Floors)
	cpi r20, 0				; dont need, floor 0 not serviced by going_up
	breq skip_check_above

check_above:				; increase the pointer to the current floor
	adiw yh:yl, 1
	dec r20					; current floor
	brne check_above

skip_check_above:
	clr temp
	st y+, temp				; sets Floors[currentfloor]=0
	
	ld temp, y				; check floor above current to see if stopping here
	cpi temp, 1
	brne check_directive
	ldi r22, 1
	ldi zl, low(Stopping)
	ldi zh, high(Stopping)
	st z, r22				; sets stopping to 1

check_directive:
	cpi r21, 9				; if directive is already max, restart
	breq going_up			; else check for higher directive

	ldi zl, low(CurrentFloor)
	ldi zh, high(CurrentFloor)
	ld r20, z				; reload current floor
	
	mov temp, r21
	sub temp, r20			; directive - currentfloor (always >0)
check_above_dir:
	adiw yh:yl, 1
	dec temp
	brne check_above_dir

	ldi temp, 9
	sub temp, r21			; 9-directive

above_dir_loop:
	inc r21

	ld temp2, y
	cpi temp2, 1			; higher directive found
	brne hd_notfound_yet
	ldi zl, low(Directive)
	ldi zh, high(Directive)
	st z, r21				; update directive

hd_notfound_yet:
	adiw yh:yl, 1
	dec temp
	brne above_dir_loop
	jmp going_up

main:	// search array
	
	ldi yl, low(Floors)
	ldi yh, high(Floors)
	ldi temp2, 10
check:
	ld temp, y+
	cpi temp, 1
	breq active
	dec temp2
	brne check
	rjmp main

active:						; number has been pressed
	ldi temp, (1<<TOIE0) | (1<<TOIE2)	; enable timer0 overflow
	out TIMSK, temp

	ldi temp, 10
	sub temp, temp2
	ldi yl, low(Directive)
	ldi yh, high(Directive)
	st y, temp				; store the new directive
	ld r21, y	

	ldi yl, low(CurrentFloor)
	ldi yh, high(CurrentFloor)
	ld r20, y

	cp r21, r20
	breq destination
	brlt going_down
	jmp going_up



destination:

	ldi yl, low(Floors)
	ldi yh, high(Floors)
	clr temp
	add yl, r21				; add directive
	adc yh, temp
	st y, temp				; Floors[directive]=0

	ldi yl, low(Stopping)
	ldi yh, high(Stopping)
	st y, temp				; Stopping=0

	rcall operate_doors
	ldi temp, (0<<TOIE0) | (1<<TOIE2)	; disable timer0 overflow
	out TIMSK, temp
	CLEAR TempCounter

	rjmp main



going_down:
	ldi temp, 0b00000001
	out PORTC, temp
	ldi yl, low(CurrentFloor)
	ldi yh, high(CurrentFloor)
	ld r20, y

	ldi zl, low(SecondCounter)
	ldi zh, high(SecondCounter)
	ld temp2, z
	cpi temp2, 2
	brne no_floor_change_d
	dec r20
	st y, r20

	rcall lcd_wait_busy		; Wait until the LCD is ready
	ldi data, LCD_DISP_CLR
	rcall lcd_write_com
	ldi data, 48
	add data, r20
	rcall lcd_wait_busy
	rcall lcd_write_data

	clr temp2
	st z, temp2			; SecondCounter set to 0

	ldi yl, low(Directive)
	ldi yh, high(Directive)		; reload directive
	ld r21, y
	cp r20, r21					; currentfloor v directive
	breq destination

	ldi yl, low(Stopping)
	ldi yh, high(Stopping)
	ld r22, y
	cpi r22, 1				; if stopping, open doors
	brne skip_doors_d
	rcall operate_doors

no_floor_change_d:
skip_doors_d:
	ldi yl, low(Floors)
	ldi yh, high(Floors)
	cpi r20, 9				; dont need, floor 9 not serviced by going_down
	breq skip_check_below

check_below:				; increase the pointer to the current floor
	adiw yh:yl, 1
	dec r20					; current floor
	brne check_below

skip_check_below:
	clr temp
	st y, temp				; sets Floors[currentfloor]=0
	sbiw y, 1

	ld temp, y				; check floor below current to see if stopping here
	cpi temp, 1
	brne check_directive_d
	ldi r22, 1
	ldi zl, low(Stopping)
	ldi zh, high(Stopping)
	st z, r22				; sets stopping to 1

check_directive_d:
	cpi r21, 0				; if directive is already min, restart
	breq going_down			; else check for lower directive

	ldi zl, low(CurrentFloor)
	ldi zh, high(CurrentFloor)
	ld r20, z				; reload current floor
	
	mov temp, r20
	sub temp, r21			; directive - currentfloor (always >0)
check_below_dir:
	sbiw yh:yl, 1
	dec temp
	brne check_below_dir

	mov temp, r21			; directive (number of places to check below the directive)

below_dir_loop:
	dec r21

	ld temp2, y				; temp2 = Floors[i] for 0 <= i < CurrentFloor
	cpi temp2, 1			; lower directive found
	brne ld_notfound_yet
	ldi zl, low(Directive)
	ldi zh, high(Directive)
	st z, r21

ld_notfound_yet:
	sbiw yh:yl, 1
	dec temp
	brne below_dir_loop
	jmp going_down




operate_doors:
	clr r22
	st y, r22			; sets stopping =0

wait_for_open:
	ldi temp, 0b01100110
	out PORTC, temp

	ldi zl, low(SecondCounter)
	ldi zh, high(SecondCounter)	; could move this above the loop
	ld temp, z
	cpi temp, 1
	brne wait_for_open

	clr temp
	st z, temp
	ldi temp, 0b01000010
	out PORTC, temp

	rcall doors_open_waiting
	rcall doors_closing
	ret


doors_open_waiting:
	ldi yl, low(LiftWaiting)
	ldi yh, high(LiftWaiting)
	ldi temp2, 1
	st y, temp2

	waiting_loop:
		ld temp2, y		; if LiftWaiting is cleared by interrupt, waiting period is exited early
		cpi temp2, 0
		breq early_exit

		ld temp, z
		cpi temp, 3
		brne waiting_loop

	early_exit:
		clr temp
		st z, temp
	ret


doors_closing:
	ldi temp, 0b01100110
	out PORTC, temp

	ld temp, z
	cpi temp, 1
	brne doors_closing
	
	ldi temp, 0b00011000
	out PORTC, temp

	clr temp
	st z, temp
	ret

; Function delay: Pass a number in registers r18:r19 to indicate how many microseconds
; must be delayed. Actual delay will be slightly greater (~1.08us*r18:r19).
; r18:r19 are altered in this function.
delay:
	subi del_lo, 1
	sbci del_hi, 0
	nop
	nop
	nop
	nop
	brne delay
	ret


		; convert function converts the row and column given to a binary number and also outputs the value to PORTC.
		; Inputs come from registers row and col and output is in temp.
convert:
	ldi del_lo, low(0xFF)
	ldi del_hi, high(0xFF)
	rcall delay

	cpi col, 3 		; if column is 3 we have a letter
	breq letters
	cpi row, 3 		; if row is 3 we have a symbol or 0
	breq symbols
	mov temp, row 	; otherwise we have a number (1-9)
	lsl temp 		; temp = row * 2
	add temp, row 	; temp = row * 3
	add temp, col 	; add the column address to get the offset from 1
	inc temp 		; add 1. Value of switch is row*3 + col + 1.
	jmp convert_end
letters:
	ldi temp, 0xA
	add temp, row 	; increment from 0xA by the row value
	jmp convert_end
symbols:
	cpi col, 0 		; check if we have a star
	breq star
	cpi col, 1 		; or if we have zero
	breq zero
	ldi temp, 0xF	; we'll output 0xF for hash
	jmp convert_end
star:
	ldi temp, 0xE 	; we'll output 0xE for star
	jmp convert_end
zero:
	clr temp 		; set to zero
convert_end:
	out PORTC, temp	; write value to PORTC

	ret 			; return to caller



rescan:
	ldi mask, INITCOLMASK	; initial column mask
	clr col 				; initial column
	out PORTB, mask 		; set column to mask value (sets column 0 off)
	ret

colloop:
	ldi del_lo, low(0xFF)
	ldi del_hi, high(0xFF)
	rcall delay
	
	cpi col, 3 		; check if we're on the last column
	breq rescan		; if so, so start again.

	sec 		; else shift the column mask: We must set the carry bit
	rol mask 	; and then rotate left by a bit, shifting the carry into bit zero. We need this to make
				; sure all the rows have pull-up resistors
	inc col 	; increment column value
	out PORTB, mask
	ret


row3:
	ldi row, 3
	rjmp continue

row2:
	ldi row, 2
	rjmp continue

row1:
	ldi row, 1
	rjmp continue

row0:
	ldi row, 0
	rjmp continue

continue:
	cli
	push r29
	push r28
	push temp2
	push temp

	dec col			; col is 1 past where it should be when the interrupt is processed
	rcall convert
	
	ldi yl, low(Floors)
	ldi yh, high(Floors)	; get address of array

	cpi temp, 0
	breq storeF
while:
	adiw yh:yl, 1
	dec temp
	brne while				; get address of floor in array
storeF:
	ldi temp2, 1
	st y, temp2

	ldi del_lo, low(65000)
	ldi del_hi, high(65000)
	rcall delay
	ldi del_lo, low(65000)
	ldi del_hi, high(65000)
	rcall delay
	ldi del_lo, low(65000)
	ldi del_hi, high(65000)
	rcall delay
	
	pop temp
	pop temp2
	pop r28
	pop r29
	sei
	reti

timer0:
	cli
	push temp
	in temp, SREG
	push temp
	push r31
	push r30
	push r29
	push r28
	push r25
	push r24
	push r23

	ldi r28, low(TempCounter)
	ldi r29, high(TempCounter)
	ld r24, Y+
	ld r25, Y
	adiw r25:r24, 1		; increase TempCounter by 1
	cpi r24, low(3597)
	ldi temp, high(3597)
	cpc r25, temp		; check if 1 second elapsed
	brne notSecond
	
	ldi zl, low(SecondCounter)
	ldi zh, high(SecondCounter)
	ld r23, z
	inc r23
	st z, r23
	;out PORTC, r23		; debug prints out second counter

	clr r24				; resets the timer
	clr r25				


notSecond:
	st y, r25
	st -y, r24
	
	pop r23
	pop r24
	pop r25
	pop r28
	pop r29
	pop r30
	pop r31
	pop temp
	out SREG, temp
	pop temp
	sei
	reti

timer2:
	cli
	push temp
	in temp, SREG
	push temp
	rcall colloop		; shift keypad scan
	pop temp
	out SREG, temp
	pop temp
	sei
	reti



/***********************************************************************
							LCD Functions
***********************************************************************/
; It is assumed that the following connections on the board are made:
; LCD D0-D7 -> PD0-PD7
; LCD BE-RS -> PA0-PA3
; These ports can be changed if required by replacing all references to the ports with a
; different port. This means replacing occurences of DDRx, PORTx and PINx.


.def data =r26
;LCD protocol control bits
.equ LCD_RS = 3
.equ LCD_RW = 1
.equ LCD_E = 2
;LCD functions
.equ LCD_FUNC_SET = 0b00110000
.equ LCD_DISP_OFF = 0b00001000
.equ LCD_DISP_CLR = 0b00000001
.equ LCD_DISP_ON = 0b00001100
.equ LCD_ENTRY_SET = 0b00000100
.equ LCD_ADDR_SET = 0b10000000
;LCD function bits and constants
.equ LCD_BF = 7
.equ LCD_N = 3
.equ LCD_F = 2
.equ LCD_ID = 1
.equ LCD_S = 0
.equ LCD_C = 1
.equ LCD_B = 0
.equ LCD_LINE1 = 0
.equ LCD_LINE2 = 0x40
.equ toASCII = 48

;Function lcd_write_com: Write a command to the LCD. The data reg stores the value to be written.
lcd_write_com:
	out PORTD, data ; set the data port's value up
	clr temp
	out PORTA, temp ; RS = 0, RW = 0 for a command write
	nop ; delay to meet timing (Set up time)
	sbi PORTA, LCD_E ; turn on the enable pin
	nop ; delay to meet timing (Enable pulse width)
	nop
	nop
	cbi PORTA, LCD_E ; turn off the enable pin
	nop ; delay to meet timing (Enable cycle time)
	nop
	nop
	ret

;Function lcd_write_data: Write a character to the LCD. The data reg stores the value to be written.
lcd_write_data:
	out PORTD, data ; set the data port's value up
	ldi temp, 1 << LCD_RS
	out PORTA, temp ; RS = 1, RW = 0 for a data write
	nop ; delay to meet timing (Set up time)
	sbi PORTA, LCD_E ; turn on the enable pin
	nop ; delay to meet timing (Enable pulse width)
	nop
	nop
	cbi PORTA, LCD_E ; turn off the enable pin
	nop ; delay to meet timing (Enable cycle time)
	nop
	nop
	ret

;Function lcd_wait_busy: Read the LCD busy flag until it reads as not busy.
lcd_wait_busy:
	clr temp
	out DDRD, temp ; Make PORTD be an input port for now
	out PORTD, temp
	ldi temp, 1 << LCD_RW
	out PORTA, temp ; RS = 0, RW = 1 for a command port read
busy_loop:
	nop ; delay to meet timing (Set up time / Enable cycle time)
	sbi PORTA, LCD_E ; turn on the enable pin
	nop ; delay to meet timing (Data delay time)
	nop
	nop
	in temp, PIND ; read value from LCD
	cbi PORTA, LCD_E ; turn off the enable pin
	sbrc temp, LCD_BF ; if the busy flag is set
	rjmp busy_loop ; repeat command read
	clr temp ; else
	out PORTA, temp ; turn off read mode,
	ser temp
	out DDRD, temp ; make PORTD an output port again
	ret ; and return


;Function lcd_init Initialisation function for LCD.
lcd_init:
	ser temp
	out DDRD, temp 			; PORTD, the data port is usually all otuputs
	out DDRA, temp 			; PORTA, the control port is always all outputs
	ldi del_lo, low(15000)
	ldi del_hi, high(15000)
	rcall delay 			; delay for > 15ms

	; Function set command with N = 1 and F = 0
	ldi data, LCD_FUNC_SET | (1 << LCD_N)
	rcall lcd_write_com		; 1st Function set command with 2 lines and 5*7 font
	ldi del_lo, low(4100)
	ldi del_hi, high(4100)
	rcall delay				; delay for > 4.1ms

	rcall lcd_write_com		; 2nd Function set command with 2 lines and 5*7 font
	ldi del_lo, low(100)
	ldi del_hi, high(100)
	rcall delay				; delay for > 100us

	rcall lcd_write_com		; 3rd Function set command with 2 lines and 5*7 font
	rcall lcd_write_com		; Final Function set command with 2 lines and 5*7 font
	rcall lcd_wait_busy		; Wait until the LCD is ready
	ldi data, LCD_DISP_OFF
	rcall lcd_write_com		; Turn Display off
	rcall lcd_wait_busy		; Wait until the LCD is ready
	ldi data, LCD_DISP_CLR
	rcall lcd_write_com		; Clear Display
	rcall lcd_wait_busy		; Wait until the LCD is ready

	; Entry set command with I/D = 1 and S = 0
	ldi data, LCD_ENTRY_SET | (1 << LCD_ID)
	rcall lcd_write_com		; Set Entry mode: Increment = yes and Shift = no
	rcall lcd_wait_busy		; Wait until the LCD is ready
	; Display on command with C = 0 and B = 1
	ldi data, LCD_DISP_ON | (1 << LCD_C)
	rcall lcd_write_com		; Turn Display on with a cursor that doesn't blink
	ret
