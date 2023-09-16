# Description
Emulating Ben Eater's [8 bit breadboard computer](https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared).

# Assembler
The assembler executes at runtime, assembling a `.asm` file and loading it directly in memory. No need to pre assemble your program in a `.bin` file.

### Comments
Anything following `;` is ignored.

### Decimal, hexadecimal and binary numbers
Write in hexadecimal base with prefix `0x`.<br>
Write in binary base with prefix `0b`.

### Writing values to a specific address
When writing a program that needs to access values from memory, instead of writing a bunch of NOP intructions until you reach the right line, the assembler comes with a shortcut: `@`
```
@13 1 0 5 ; This line tells the assembler to write these values starting at address 13

; When executing, the program will then find the numbers
; 1 at address 13, 0 at address 14 and 5 at address 15
```

## Example program
A simple program adding the numbers 28 and 14 would look something like this:
```
LDA 14
ADD 15
OUT

@14 28
@15 14
```