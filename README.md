# virtual_8086

## Log:
(Scroll down for older entries)

-- 2026-01-09 --
- Started implementing HandleInst() function so I could generalize what happens when an instruction is complete
instead of always printing to console in the while loop
- Also implemented another function R_GetReg that gets only a single register from the Reg field and sets
the full_inst struct with the correct value, this caused a linker issue that took me a while to figure out
- I was getting an unreferenced symbol error for R_GetReg despite being declared in a header and defined in a file that was compiled.
- The linker error was eliminated after I added another reference to the function inside of the function definition 
file.
- Given this, I'm pretty sure what happened was that, since the function was only referenced inside 
of some nested conditional statements inside of another function, the function call was maybe optimized away.
- Still want to inspect the assembly to investigate this because it seems liek a good learning opportunity,
but I'm pretty sure that's what happened, and completing more of the code so that the R_GetReg()
function is required will probably fix the issue/.
- **LESSON: When the code structure gets complex enough the optimizer can do unexpected things.**

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