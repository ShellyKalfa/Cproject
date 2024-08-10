MAIN: add r3, LIST
LOOP: prn #48
      macr maco
      cmp r3, #-6
      bne END
      endmacr 
      lea STR, r6
      inc r6
      mov *r6,K
      macr hi
      cmp r8, #-7
      cmp r8, #-7
      cmp r8, #-7
      cmp r8, #-7
      cmp r8, #-7
      endmacr 
      sub r1, r4
      maco
      dec K
      jmp LOOP
      hi
END:  stop
STR: .string “abcd”
hi:   kjkkjjk
LIST: .data 6, -9
      .data -100
 K:   .data 31
