;; =============================================================
;; CS 2110 - Fall 2022
;; Project 3 - Fibonacci
;; =============================================================
;; Name:
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;;
;; n = mem[N];
;; result = mem[RESULT];
;; 
;; if (n == 1) {
;;     mem[result] = 0;
;; } else if (n > 1) {
;;     mem[result] = 0;
;;     mem[result + 1] = 1;
;;     for (i = 2; i < n; i++) {
;;         x = mem[result + i - 1];
;;         y = mem[result + i - 2];
;;         mem[result + i] = x + y;
;;     }
;; }

.orig x3000
	
	LD R0, N      	;; loading n value into R0
	LD R6, RESULT	;; loading result value into R6
	AND R7, R7, 0 	;; zeroing out R7
	AND R1, R1, 0 	;; zeroing out R1
	;;ADD R1, R1, 1 	 adding value 1 to R1
	ADD R1, R0, -1	;; adding -1 to R0 and then stores to R1
	BRnp EL		;; if the value stored in R1 is pos or neg then go to else statement
	AND R7, R7, 0 	;; mem[result] = 0
	STR R7, R6, 0	;; storing value of R7 into mem[result]
	BR SKIP		;; skip else statement

EL
	AND R1, R1, 0 	;; zeroing out R1
	ADD R1, R0, -1	;; adding -1 to R0 and storing into temp var/ register R1
	BRnz SKIP
	AND R7, R7, 0 	;; zeroed R7
	STR R7, R6, 0	;; mem[result] = 0
	ADD R7, R7, 1	;; set R7 = 1
	STR R7, R6, 1	;; me [result + 1] = 1
	

	AND R3, R3, 0	;; zero out R3
	ADD R3, R3, 2	;; add 2 to R3 (i value in for loop)
	AND R4, R4, 0	;; zero R4
	AND R5, R5, 0	;; zero R5
	NOT R4, R0	;; -n
	ADD R4, R4, 1	;; add 1 to R4 BC OF 2's complement

WHILE
	ADD R5, R3, R4	;; storing value of i-n into R5
	BRzp ENDwhile	;; branch to end of while loop
	AND R0, R0, 0	;; store x
	AND R2, R2, 0	;; store y
	AND R1, R1, 0	
	ADD R1, R6, R3	;; result + i
	ADD R1, R1, -1	;; result of (result + i) - 1
	LDR R0, R1, 0	;; this equals x
	ADD R1, R1, -1	;; (result + i - 2)
	LDR R2, R1, 0	;; this equals y
	AND R1, R1, 0	
	ADD R1, R6, R3	;; result + i
	ADD R0, R0, R2	;; x + y
	STR R0, R1, 0	;; mem[result + i] = x + y
	
	
	ADD R3, R3, 1	;; incrementing i
	
	BRnzp WHILE
	



	
ENDwhile
	

SKIP
	
	
	

    HALT

;; Do not rename or remove any existing labels
;; You may change the value of N for debugging
N       .fill 5
RESULT  .fill x4000
.end

.orig x4000
.blkw 100
.end
