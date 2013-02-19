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
	.dbg		file, "strtok.c", 1493, 1361178487
	.dbg		file, "../../include/string.h", 4883, 1361178487
	.dbg		file, "../../include/stddef.h", 2972, 1361178487
	.import		_strchr
	.export		_strtok

.segment	"DATA"

_Last:
	.word	$0000

; ---------------------------------------------------------------
; __near__ unsigned char* __near__ __fastcall__ strtok (register __near__ unsigned char*, __near__ const unsigned char*)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_strtok: near

.segment	"CODE"

;
; {
;
	.dbg	line, "strtok.c", 31
	jsr     pushax
	ldy     #$02
	ldx     #$04
	jsr     regswap2
;
; if (s1 == 0) {
;
	.dbg	line, "strtok.c", 36
	jsr     decsp3
	lda     regbank+4
	ora     regbank+4+1
	bne     L0004
;
; s1 = Last;
;
	.dbg	line, "strtok.c", 37
	lda     _Last
	sta     regbank+4
	lda     _Last+1
	sta     regbank+4+1
;
; if (*s1 == '\0') {
;
	.dbg	line, "strtok.c", 41
L0004:	lda     (regbank+4)
	bne     L0009
;
; return 0;
;
	.dbg	line, "strtok.c", 42
	tax
	jmp     L0003
;
; while ((c = *s1) && strchr (s2, c) != 0) {
;
	.dbg	line, "strtok.c", 48
L0009:	lda     (regbank+4)
	ldy     #$02
	sta     (sp),y
	tax
	beq     L000D
	ldy     #$04
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     pushax
	ldy     #$04
	lda     (sp),y
	ldx     #$00
	jsr     _strchr
	cpx     #$00
	bne     L000E
	cmp     #$00
	beq     L000D
;
; ++s1;
;
	.dbg	line, "strtok.c", 49
L000E:	inc     regbank+4
	bne     L0009
	inc     regbank+4+1
;
; }
;
	.dbg	line, "strtok.c", 50
	bra     L0009
;
; if (c == '\0') {
;
	.dbg	line, "strtok.c", 51
L000D:	ldy     #$02
	lda     (sp),y
	bne     L0018
;
; Last = s1;
;
	.dbg	line, "strtok.c", 53
	lda     regbank+4
	sta     _Last
	lda     regbank+4+1
	sta     _Last+1
;
; return 0;
;
	.dbg	line, "strtok.c", 54
	txa
	bra     L0003
;
; start = s1;
;
	.dbg	line, "strtok.c", 58
L0018:	lda     regbank+4
	ldx     regbank+4+1
	jsr     stax0sp
;
; while ((c = *s1) && strchr (s2, c) == 0) {
;
	.dbg	line, "strtok.c", 61
L001F:	lda     (regbank+4)
	ldy     #$02
	sta     (sp),y
	tax
	beq     L0020
	ldy     #$04
	lda     (sp),y
	tax
	dey
	lda     (sp),y
	jsr     pushax
	ldy     #$04
	lda     (sp),y
	ldx     #$00
	jsr     _strchr
	cpx     #$00
	bne     L0020
	cmp     #$00
	bne     L0020
;
; ++s1;
;
	.dbg	line, "strtok.c", 62
	inc     regbank+4
	bne     L001F
	inc     regbank+4+1
;
; }
;
	.dbg	line, "strtok.c", 63
	bra     L001F
;
; if (c == '\0') {
;
	.dbg	line, "strtok.c", 64
L0020:	ldy     #$02
	lda     (sp),y
	bne     L002B
;
; Last = s1;
;
	.dbg	line, "strtok.c", 66
	lda     regbank+4
	sta     _Last
	lda     regbank+4+1
	sta     _Last+1
;
; } else {
;
	.dbg	line, "strtok.c", 67
	bra     L002F
;
; *s1 = '\0';
;
	.dbg	line, "strtok.c", 68
L002B:	lda     #$00
	sta     (regbank+4)
;
; Last = s1 + 1;
;
	.dbg	line, "strtok.c", 69
	lda     regbank+4
	ldx     regbank+4+1
	ina
	bne     L0034
	inx
L0034:	sta     _Last
	stx     _Last+1
;
; return start;
;
	.dbg	line, "strtok.c", 73
L002F:	dey
	lda     (sp),y
	tax
	lda     (sp)
;
; }
;
	.dbg	line, "strtok.c", 74
L0003:	pha
	ldy     #$05
	lda     (sp),y
	sta     regbank+4
	iny
	lda     (sp),y
	sta     regbank+5
	pla
	jmp     incsp7
	.dbg	line

.endproc

