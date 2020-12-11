	.arch msp430g2553
	.p2align 1,0
	.text			



	.extern assySong
	.extern scaleNote
	.extern buzzer_set_period
	.extern note

	.global convert

convert:
	
	MOV &scaleNote, R12	; scaleNote as param
	CALL #assySong		; assySong(scaleNote)
	MOV R12, &note		; note = assySong(scaleNote);incoming return value
	MOV &note, R12		;note as param
	CALL #buzzer_set_period	; buzzer_set_period(note)

end:
	POP R0
