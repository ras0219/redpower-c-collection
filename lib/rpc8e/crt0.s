; ---------------------------------------------------------------------------
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for c65el02

.export   _init, _exit
.import   _main

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __STACK_START__, __STACK_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"

.macro MMU     command
     .byte     $EF
     .byte     command
.endmacro

.macro XCE
     .byte     $FB
.endmacro
 
; ---------------------------------------------------------------------------
; Place the startup code in a special segment

.segment  "STARTUP"

;.byte $DB

; ---------------------------------------------------------------------------
; A little light 6502 housekeeping

_init:    LDX     #$FF                 ; Initialize stack pointer to $01FF
          TXS
          CLD                          ; Clear decimal mode

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

          LDA     #<(__STACK_START__ + __STACK_SIZE__ - 1)
          STA     sp
          LDA     #>(__STACK_START__ + __STACK_SIZE__ - 1)
          STA     sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage

          JSR     zerobss              ; Clear BSS segment
          JSR     copydata             ; Initialize DATA segment
          JSR     initlib              ; Run constructors

; ---------------------------------------------------------------------------
; Initialize redbus

; This below is useless right now, probably will be removed

; from foth boot disk
;000500   18         CLC 
;000501   FB         XCE 
;000502   C2 30      REP #$30
;000504   A9 00 03   LDA #$0300
;000507   EF 01      MMU $01
;000509   EF 02      MMU $02
;00050B   A9 00 04   LDA #$0400
;00050E   EF 03      MMU $03
;000510   EF 04      MMU $04
;000512   A9 00 05   LDA #$0500
;000515   EF 06      MMU $06
;000517   4C 56 1D   JMP $1D56

;LDA       $01                  ; Get the main console ID
;MMU       $00

;LDA       #$00                 ; Select first line
;STA       $0300

;LDA       #$42                 ; Seems to work
;STA       $0310

;.byte $DB




; ---------------------------------------------------------------------------
; Call main()

          JSR     _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):  force a software break

_exit:    JSR     donelib              ; Run destructors
          BRK
