# virtual_8086

## Log:

-- 2026-01-03 --
- Finished refactor where I changed from reading in 16 bits at a time to dealing with the bytes one at a time 
for several reasons:
- isntructions will not always be 16 bits
- I was using uint16_t to store the two bytes and was then being messed up by endian interpretations
- This allows for dynamic length instructions, since whether we need more bytes for the instruction 
is determined by the early byte values