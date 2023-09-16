LDI 0
;count up loop
OUT
ADD 0xf
JC 6
JMP 1
;count down loop
OUT
SUB 0xf
JZ 1
JMP 5
@0xf 1