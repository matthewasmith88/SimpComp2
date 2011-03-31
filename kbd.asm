;kbd.asm

.ORIG X3000

	IN   KBD

	MOVB R1, R0

	IN   KBD
	
	MOVB R2, R0

 	IN   KBD

	OUT  VID

	MOVB R0, R2

	OUT  VID
 
	MOVB R0, R1

	OUT  VID

	HALT
.END

