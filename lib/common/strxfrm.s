;
; File generated by cc65 v 2.13.3
;
	.fopt		compiler,"cc65 v 2.13.3"
	.setcpu		"65C02"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	on
	.importzp	sp, sreg, regsave, regbank, tmp1, ptr1, ptr2
	.macpack	longbranch
	.dbg		file, "strxfrm.c", 222, 1361266118
	.dbg		file, "../../include/string.h", 4883, 1361245852
	.dbg		file, "../../include/stddef.h", 2972, 1361245852
	.import		_strlen
	.import		_strncpy
	.export		_strxfrm

; ---------------------------------------------------------------
; unsigned int __near__ __fastcall__ strxfrm (__near__ unsigned char*, __near__ const unsigned char*, unsigned int)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_strxfrm: near

.segment	"CODE"

;
; {
;
	.dbg	line, "strxfrm.c", 14
	jsr     pushax
;
; strncpy (dest, src, count);
;
	.dbg	line, "strxfrm.c", 15
	jsr     decsp4
	ldy     #$09
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	ldy     #$02
	sta     (sp),y
	iny
	txa
	sta     (sp),y
	ldy     #$07
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	sta     (sp)
	ldy     #$01
	txa
	sta     (sp),y
	ldy     #$05
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     _strncpy
;
; return strlen (src);
;
	.dbg	line, "strxfrm.c", 16
	ldy     #$03
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     _strlen
;
; }
;
	.dbg	line, "strxfrm.c", 17
	jmp     incsp6
	.dbg	line

.endproc

