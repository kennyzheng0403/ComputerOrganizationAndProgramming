;; =============================================================
;; CS 2110 - Fall 2022
;; Project 3 - ToLowercase
;; =============================================================
;; Name: Kenny Zheng
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;; 
;; length = mem[LENGTH];
;; 
;; i = 0;
;; while (i < length) {
;;     ready = mem[mem[KBSR]] & x8000;
;;     if (ready == 0) {
;;         continue;
;;     }
;;     currentChar = mem[mem[KBDR]];
;;     if (currentChar == `\0') {
;;         break;
;;     }
;;     currentChar = currentChar | 32; // Use DeMorgan's law!
;;     mem[TEMP + i] = currentChar;
;;     i++;
;; }
;; 
;; i = 0;
;; while (i < length) {
;;     ready = mem[mem[DSR]] & x8000;
;;     if (ready == 0) {
;;         continue;
;;     }
;;     currentChar = mem[TEMP + i];
;;     mem[mem[DDR]] = currentChar;
;;     i++;
;; }

.orig x3000

	LD R0, LENGTH	;; stores length
	AND R1, R1, 0	;; stores i
	NOT R0, R0	;; negative length
	ADD R0, R0, 1	;; ADD 1 BC OF 2'S COMPLEMENT
WHILE
	ADD R2, R1, R0	;; (i < length)
	BRzp LABEL

	LDI R3, KBSR	;; mem[mem[KBSR]]
	LD R4, Bit15Mask	;; load KBSR into R4
	AND R3, R3, R4 	;; mem[mem[KBSR]] & x8000
	BRz WHILE

	LDI R5, KBDR	;; mem[mem[KBDR]]
	BRz LABEL

	LD R4, ThirtyTwo	;; load 32 into R4
	NOT R5, R5	;; make currentChar negative
	NOT R4, R4	;; make 32 negative
	AND R5, R5, R4	;; (-currentChar & -32)
	NOT R5, R5	;; -(-currentChar & -32)

	LD R7, TEMP	;;
	ADD R6, R1, R7 	;;
	STR R5, R6, 0	;; mem[TEMP + I] = currentChar
	ADD R1, R1, 1	;; increment i by 1
	BR WHILE
	
LABEL	
	LD R0, LENGTH	;; stores length
	AND R1, R1, 0	;; stores i
	NOT R0, R0	;; negative length
	ADD R0, R0, 1	;; ADD 1 BC OF 2'S COMPLEMENT
	

WHILE2	
	AND R2, R2, 0	;;
	ADD R2, R1, R0	;; (i < length)
	BRzp END

	AND R3, R3, 0	;; ready
	LDI R3, DSR	;; mem[mem[DSR]]
	LD R4, Bit15Mask	;; load DSR into R4
	AND R3, R3, R4 	;; mem[mem[DSR]] & x8000
	BRz WHILE2
	AND R5, R5, 0	
	AND R6, R6, 0	;;
	AND R7, R7, 0	;;

	LD R7, TEMP	;;
	ADD R6, R1, R7 	;;
	LDR R5, R6, 0	;; mem[TEMP + i]
	STI R5, DDR	;;
	ADD R1, R1, 1	;; increment i by 1
	BR WHILE2
	
	
	

	
	
END

    HALT

;; Do not rename or remove any existing labels
Bit15Mask   .fill x8000
ThirtyTwo   .fill 32
KBSR        .fill xFE00
KBDR        .fill xFE02
DSR         .fill xFE04
DDR         .fill xFE06

LENGTH      .fill 8
TEMP        .blkw 100
.end