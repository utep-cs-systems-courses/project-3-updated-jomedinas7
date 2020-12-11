	.arch msp430g2553
	.p2align 1,0
	.text			



	.extern assySong
	.extern scaleNote
	.extern buzzer_set_period
	.extern note

	.global convert

convert:

	MOV &scaleNote, R12	;
	CALL #assySong
	MOV R12, &note
	MOV &note, R12
	CALL #buzzer_set_period

end:
	POP R0
