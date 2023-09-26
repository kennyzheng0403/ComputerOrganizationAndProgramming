;; =============================================================
;; CS 2110 - Fall 2022
;; Project 3 - Bit Shifting, Multiplication, Division, and GCD
;; =============================================================
;; Name: Kenny Zheng
;; =============================================================

;; PART 1: Bit Shifting

;; Left Shift Suggested Pseudocode (see PDF for explanation)
;;
;; val = R0;
;; amt = R1;
;; 
;; while (amt > 0) {
;;     val = val + val;
;;     amt = amt - 1;
;; }
;; 
;; R0 = val;

.orig x3600
LeftShift

	ADD R6, R6, -1	;;
	STR R1, R6, 0 	;; push R1

WHILE
	ADD R1, R1, 0	;; set condition code (amt > 0)
	BRnz END
	ADD R0, R0, R0	;; val = val + val
	ADD R1, R1, -1	;; amt = amt - 1
	BR WHILE

 END   
	LDR R1, R6, 0 	;;	pop R1
	ADD R6, R6, 1	;;

	
	RET
.end

;; Right Shift Suggested Pseudocode (see PDF for explanation)
;;
;; val = R0;
;; amt = R1;
;; 
;; result = 0;
;; 
;; while (amt < 16) {
;;     result = result + result;
;;     if (val < 0) { // check if the MSB is set
;;         result = result + 1;
;;     }
;;     val = val + val;
;;     amt = amt + 1;
;; }
;; 
;; R0 = result;

.orig x3800
RightShift

	ADD R6, R6, -1
	STR R1, R6, 0 ; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 ; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 ; push R3

	AND R2, R2, 0	;; push
WHILE3
	ADD R3, R1, 0	;;
	ADD R3, R3, -16	;; set condition code (amt < 16)
	BRzp END2
	ADD R2, R2, R2	;;
	ADD R0, R0, 0	;;
	BRzp SKIP 
	ADD R2, R2, 1 	;; result = result + 1
SKIP	

	ADD R0, R0, R0	;; val = val + val
	ADD R1, R1, 1	;; amt = amt + 1
	BR WHILE3

 END2  
    	ADD R0, R2, 0	;; R0 = result
		LDR R3, R6, 0 ; POP R3
	    ADD R6, R6, 1

		LDR R2, R6, 0 ; POP R2
	    ADD R6, R6, 1

		LDR R1, R6, 0 ; POP R1
	    ADD R6, R6, 1
		
    RET
.end

;; PART 2: Multiplication and Division

;; Multiply Suggested Pseudocode (see PDF for explanation)
;; 
;; a = R0;
;; b = R1;
;; 
;; result = 0;
;; for (i = 0; i < 16; i++) {
;;     mask = 1 << i;
;;     if (b & mask != 0) {
;;         result = result + (a << i);
;;     }
;; }
;;
;; R0 = result;

.orig x3200
Multiply

	ADD R6, R6, -1
	STR R7, R6, 0 ; PUSH R7

	AND R2, R2, 0	;;
	ADD R2, R0, 0 	;; R2 = a
	AND R4, R4, 0	;;
	ADD R4, R4, R1 	;; R5 = R1 = b
	AND R1, R1, 0 	;; R1 = i = 0
	AND R5, R5, 0 	;; R5 = 0 for result

FOR	;; i < 16 --> i - 16 < 0
	ADD R0, R1, -16	;; set condition code (FOR LOOP)
	BRzp END3

	AND R0, R0, 0	;; R0 = 0
	ADD R0, R0, 1	;; R0 = 1, R1 = i

	ADD R6, R6, -1
	STR R1, R6, 0 ; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 ; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 ; push R3

	ADD R6, R6, -1
	STR R4, R6, 0 ; push R4

	ADD R6, R6, -1
	STR R5, R6, 0 ; push R5

	JSR LeftShift	;; call left shift 

	LDR R5, R6, 0 ; pop R5
	ADD R6, R6, 1
	
	LDR R4, R6, 0 ; pop R4
	ADD R6, R6, 1

	LDR R3, R6, 0 ; pop R3
	ADD R6, R6, 1

	LDR R2, R6, 0 ; pop R2
	ADD R6, R6, 1

	LDR R1, R6, 0 ; pop R1
	ADD R6, R6, 1

	AND R3, R4, R0	;; (b & mask)
	BRz SKIP2

    AND R0, R0, 0 ; R0 = 0 
	ADD R0, R0, R2 ; R0 = a and R1 = i

	ADD R6, R6, -1
	STR R1, R6, 0 ; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 ; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 ; push R3

	ADD R6, R6, -1
	STR R4, R6, 0 ; push R4

	ADD R6, R6, -1
	STR R5, R6, 0 ; push R5
	
	JSR LeftShift	;; call left shift 

	LDR R5, R6, 0 ; pop R5
	ADD R6, R6, 1
	
	LDR R4, R6, 0 ; pop R4
	ADD R6, R6, 1

	LDR R3, R6, 0 ; pop R3
	ADD R6, R6, 1

	LDR R2, R6, 0 ; pop R2
	ADD R6, R6, 1

	LDR R1, R6, 0 ; pop R1
	ADD R6, R6, 1

	ADD R5, R5, R0	;; result = result + (a << i)
	
SKIP2	
	ADD R1, R1, 1	;; increment i
	BR FOR
	
		
	
	
END3	
	AND R0, R0, 0 ; R0 = 0
	ADD R0, R0, R5 ; R5 = R0 = result;

		
	LDR R7, R6, 0 	;; 
	ADD R6, R6, 1	;; pop R7
	
    RET
.end

;; Divide Suggested Pseudocode (see PDF for explanation)
;;
;; a = R0;
;; b = R1;
;; 
;; quotient = 0;
;; remainder = 0;
;; 
;; for (i = 15; i >= 0; i--) {
;;     quotient = quotient + quotient;
;;     remainder = remainder + remainder;
;;     remainder = remainder + ((a >> i) & 1);
;;     
;;     if (remainder >= b) {
;;         remainder = remainder - b;
;;         quotient = quotient + 1;
;;     }
;; }
;; 
;; R0 = quotient;

.orig x3400
Divide

    ADD R6, R6, -1
	STR R7, R6, 0 	;; push R7
	
	AND R2, R2, 0 	;; stores quotient = 0 in R2
	AND R3, R3, 0 	;; stores remainder = 0 in R2

	AND R4, R4, 0 	;; zero out R4
	ADD R4, R4, R1 	;; store R4 + R1 into R4
	NOT R4, R4 		;; not b
	ADD R4, R4, 1 	;; add 1 to -b because of 2's complement

	AND R1, R1, 0 	;; zero out R1 = i
	ADD R1, R1, 15 	;; R1 = 15

FOR2
	ADD R1, R1, 0 	;; end condition of for loop
	BRn END4 		;; branch to END if we've hit our 16 iterations

	ADD R2, R2, R2 	;; quotient = quotient + quotient;
	ADD R3, R3, R3 	;; remainder = remainder + remainder

	ADD R6, R6, -1
	STR R0, R6, 0 	;; push R0

	ADD R6, R6, -1
	STR R1, R6, 0 	;; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 	;; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 	;; push R3

	ADD R6, R6, -1
	STR R4, R6, 0 	;; push R4

	ADD R6, R6, -1
	STR R5, R6, 0 	;; push R5

	JSR RightShift	;; call RightShift

	LDR R5, R6, 0 	;; pop R5
	ADD R6, R6, 1
	
	LDR R4, R6, 0 	;; pop R4
	ADD R6, R6, 1

	LDR R3, R6, 0 	;; pop R3
	ADD R6, R6, 1

	LDR R2, R6, 0 	;; pop R2
	ADD R6, R6, 1

	LDR R1, R6, 0 	;; pop R1
	ADD R6, R6, 1

	AND R5, R0, 1 	;; ((a >> i) & 1)
	ADD R3, R3, R5	;; remainder = remainder + ((a >> i) & 1)

	LDR R0, R6, 0 	;; pop R0
	ADD R6, R6, 1

	ADD R5, R3, R4 	;; remainder - b >= 0
	BRn SKIP3 		;; skip only if above condition outputs a negative
	ADD R3, R3, R4 	;; remainder = remainder - b
	ADD R2, R2, 1 	;; quotient = quotient + 1
		
	
SKIP3
	ADD R1, R1, -1 	;; decrement i by 1
	BR FOR2			;; branch back to for loop

END4
	AND R0, R0, 0 	;; zero out R0
	ADD R0, R2, 0 	;; R0 = R2 = quotient
		
	LDR R7, R6, 0 	;; pop R7
	ADD R6, R6, 1
	
    RET
.end

;; PART 3: GCD

;; Suggested Pseudocode (see PDF for explanation)
;;
;; a = mem[A];
;; b = mem[B];
;; 
;; R6 = mem[STACK];
;;
;; while (b > 0) {
;;     quotient = a / b;
;;     remainder = a - quotient * b;
;;     a = b;
;;     b = remainder;
;; }
;; 
;; mem[RESULT] = a;

.orig x3000

    ;; Your code here!!
	AND R2, R2, 0 	;; zero out R2 -> remainder
	LD R3, A 		;; load A into R3
	LD R1, B 		;; load B into R1
	LD R6, STACK 	;; R6 = stack pointer
	LD R4, B 		;; load B into R4
WHILE4
	BRnz END5

	ADD R6, R6, -1
	STR R1, R6, 0 	;; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 	;; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 	;; push R3

	ADD R6, R6, -1
	STR R4, R6, 0 	;; push R4

	ADD R6, R6, -1
	STR R5, R6, 0 	;; push R5

	ADD R0, R3, 0 	;; add R3 + 0 and store in R0

	JSR Divide 		;; call Divide, quotient = a/b

	LDR R5, R6, 0 	;; pop R5
	ADD R6, R6, 1
	
	LDR R4, R6, 0 	;; pop R4
	ADD R6, R6, 1

	LDR R3, R6, 0 	;; pop R3
	ADD R6, R6, 1

	LDR R2, R6, 0 	;; pop R2
	ADD R6, R6, 1

	LDR R1, R6, 0 	;; pop R1
	ADD R6, R6, 1
		
	ADD R6, R6, -1
	STR R1, R6, 0 	;; push R1

	ADD R6, R6, -1
	STR R2, R6, 0 	;; push R2		

	ADD R6, R6, -1
	STR R3, R6, 0 	;; push R3

	ADD R6, R6, -1
	STR R4, R6, 0 	;; push R4

	ADD R6, R6, -1
	STR R5, R6, 0 	;; push R5

	JSR Multiply 	;; call Multiply, R0 = a/b * b
		
	LDR R5, R6, 0 	;; pop R5
	ADD R6, R6, 1
	
	LDR R4, R6, 0 	;; pop R4
	ADD R6, R6, 1

	LDR R3, R6, 0 	;; pop R3
	ADD R6, R6, 1

	LDR R2, R6, 0 	;; pop R2
	ADD R6, R6, 1

	LDR R1, R6, 0 	;; pop R1
	ADD R6, R6, 1
		
	NOT R0, R0		;; -quotient
	ADD R0, R0, 1	;; - quotient * b
	ADD R2, R3, R0 	;; remainder = a - quotient * b
	ADD R3, R1, 0 	;; a = b
	ADD R1, R2, 0 	;; b = remainder
	BR WHILE4 		;; go back to while loop

END5
	ST R3, RESULT 	;; mem[RESULT] = a;

    HALT

;; Do not rename or remove any existing labels
;; You may change the values of A and B for debugging
STACK   .fill xF000
A       .fill 7
B       .fill 10
RESULT  .blkw 1
.end
