MAIN: add r3, LIST
LOOP: prn #48
      macr macr_p
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
      macr_p
      dec K
      jmp LOOP
      hi
END:  stop
STR: .string “abcd”
LIST: .data 6, -9
      .data -100
 K:   .data 31
