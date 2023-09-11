# PROGRAM WRITING

A simple way to program the 8bit cpu from a command prompt, supports hexadecimal numbers, comments and writing a value to a specific address.

See [Ben Eater's videos](https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared) for a list of instructions and their meaning.

## EXAMPLE
```
LDA 0x0e ; same thing as 'LDA 14'
ADD 15
OUT

@14 32 ; writes a 32 at address 14
@0x0f 28 ; same thing as '@15 28'

\ ; EOF command
```

### SPECIAL COMMANDS
#### @adr
* <b>Note that it is <i>NOT</i> the same as a STA instruction. It is a compile-time command only.</b>
* The `@adr` command treats the following values as numbers to write at a specific address. 
```
@1 LDA 14 ; Is not a valid command

28 ; Will not write a 28 at address 0 even if it's the first instruction received

@0 28 ; But this will

@0 42 ; Will overwrite the 28 with a 42
```

* It also supports multiple numbers inline.
```
@0 19 20 21 ; Will write a 19 at address 0, 20 at address 1 and 21 at address 2.
```