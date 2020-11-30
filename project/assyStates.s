	.arch msp430g2553
	.p2align 1,0
	.text			;jt is the jmp table

jt:
	.word case0		;
	.word case1		;
	.word case2		;
	.word case3		;
	.word default		;
	
	.extern noteToBuz
	.global assySong

assySong:
	SUB #2,R1		;allocate memory for short
	MOV #0,0(R1)		;note = 0
	CMP #0, R12		;state - 0
	JLO default		;state < 0 (signed comparison)
	CMP #4, R12		;state - 4
	JC  default		;state >= 4 (unsigned comparison)

	ADD R12, R12		;r12 = 2*state
	MOV jt(R12), R0		;jmp jt[state]
case0:

	MOV #500, 0(R1)		;note = 500

	JMP convert		;

case1:

	MOV #440, 0(R1)		;note = 440

	JMP convert		;

case2:

	MOV #523, 0(R1)		;note = 523

	JMP convert		;

case3:

	MOV #598, 0(R1)		;note = 598
	JMP convert		;
default:

	MOV #0, 0(R1)		;note = 0
	JMP end			;

convert:
	MOV 0(R1), R12		;move note into the parameter
	CALL #noteToBuz	;call convertNote(note)
	JMP end			;
end:

	ADD #2, R1		;reset the stack
	POP R0			;return
