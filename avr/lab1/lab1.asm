.include "m64def.inc"

.def nl=r24
.def nh=r25
.def c=r16
.def ten=r17

.cseg

main:
    ldi YL,low(RAMEND-2)    ;reserve 2 bytes to return int number
    ldi YH,high(RAMEND-2)
    out SPL,YL                ;set stack pointer
    out SPH,YH

    rcall atoi                ;call atoi()

    std Y+1,r22                ;store return value on stack
    std Y+2,r23

end:
    rjmp end
    ;end of main function

atoi:
        ;function prologue;
    push YL
    push YH
    push r16        ;c
    push r17        ;ten
    push r18
    push r19
    in YL,SPL
    in YH,SPH
    sbiw YH:YL,2    ;reserve 2bytes for local n
    out SPL,YL
    out SPH,YH
        ;end prologue;

    clr nl            ;initialise n
    clr nh

    std Y+1,nl        ;store n on the stack frame
    std Y+2,nh

    ldi ten, 10

    ldi ZH,high(string<<1)    ;initialise Z
    ldi ZL,low(string<<1)

    loop:
        lpm c, Z+            ;load c and increment Z pointer
        cpi c, '0'
        brlt done            ;branch less than (signed)
        cpi c, ':'
        brge done
        mul nl,ten            ;multiplication of n(2bytes) by 10
        movw r19:r18,r1:r0
        mul nh,ten
        add r19,r0
        movw nh:nl,r19:r18
        subi c, '0'            ;adding c (current char)
        add nl, c
        brcc nocarry        ;branch on carry flag clear (0)
        inc nh                ;else add carry
    nocarry:
        std Y+1,nl
        std Y+2,nh
        rjmp loop

    done:
        ;function epilogue;
        movw r23:r22,nh:nl    ;copy to return location
        
        adiw YH:YL,2
        out SPH,YH
        out SPL,YL
        pop r19
        pop r18
        pop r17
        pop r16
        pop YH
        pop YL
        ret
        ;end of epilogue;

string:        .db    "12345"
