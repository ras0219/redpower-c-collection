;from cc65.org, all rights to them
; ---------------------------------------------------------------------------
; wait.s
; ---------------------------------------------------------------------------
;
; Wait for interrupt and return

.export  _wait

; ---------------------------------------------------------------------------
; Wait for interrupt:  Forces the assembler to emit a WAI opcode ($CB)
; ---------------------------------------------------------------------------
.code

_wait:
	.byte      $CB                    ; Inserts a WAI opcode
	rts


