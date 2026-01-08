# virtual_8086

## Log:
(Scroll down for older entries)

-- 2026-01-07 ---
- Implemented first versions of HandleByte1() and HandleByte2() on new branch
- The idea is to handle each byte with a separate function and passing relevant reference values and structs to modify as needed
- initial testing works fine, just want to do some more double checking before merging back to main branch.

-- 2026-01-03 --
- Finished refactor where I changed from reading in 16 bits at a time to dealing with the bytes one at a time 
for several reasons:
- instructions will not always be 16 bits
- I was using uint16_t to store the two bytes and was then being messed up by endian interpretations
- This allows for dynamic length instructions, since whether we need more bytes for the instruction 
is determined by the early byte values

--- BEGINNING ----