# virtual_8086

## Log:
(Scroll down for older entries)

-- 2026-01-23 --
- It looks like in some cases the disp bytes in the instruction encoding table (table 4-12) are not included? 
For example, in listing 40, the bytes 0xc60307 should decode to MV [BP + DI], byte 7. 7 is the data byte there, but the table seems to suggest there should be two disp bytes before that. 
- update: I realized that the MOD field still indicated whether displacements are present, so in this case the mod field is 00, indicating no displacement bytes, but I still need the data byte(s)
- update: fixed this issue now immediate to regmem moves seem to work with explicit sizes
- HandleInst() function is getting more unwieldy, maybe should refactor later if I can make it more generalizable

-- 2026-01-17 --
- For immediate to memory, I realized I should have been more careful differentiating between "disp" fields and "data fields", so some of the earlier decodes may use one in place of the other, but should only be the case when both are not needed, only one.
- Starting to think about rewriting the GetReg family of functiions to make them more modular and generalizable, which would enable fewer functions. Right now I'm usually having to write a new function for each different opcode.

-- 2026-01-16 --
- Struggled a lot today with dealing with sign extensions. Working on listing 40, which had signed displacements, made me realize I was maybe dealing with previous values incorrectly, or at least not thinking about them correctly.
- Getting a better understanding of this required a lot of playing around with typecasting.
- Because I am reading one byte in at a time, and I'm trying to in some cases combine two bytes into one 16-bit value, I have to be careful that no unintentional conversions happen in the process, and per the manual I need to make sure that 8-bit displacements are sign-extended to 16 bits.
- I think most of the difficulty here is just wrapping my head around it, and I'm still trying to do that. But I think it's important for me to do.
- This has also been a good opportunity to learn two's complement better
- **LESSON: Be careful when converting between signed/unsigned and variable of different numbers of bytes (e.g. uint8_t to int16_t), make sure you understand when sign extension is happening**

-- 2026-01-13 --
- Completed I believe all effective address moves (REGMEM_TF_REG where MOD bytes are any value)
- I hade to add some options in the HandleInst() function, mainly to deal with the fact that displacements
need to go inside the square brackets if they exist. This was a good tradeoff that enabled me to reuse
the GetRegMOD_00() function for the other mod values, since they can use the same table of register values, 
as long as I can add the displacement values later.
- Because of this I should maybe rename to GetRegMOD(), since I can use for other mod values than 00

-- 2026-01-12 --
- Wrote more decoding in HandleByte_2 for MOD = 00 (Memory mode, no displacement follows*)
- Added another GetReg() function to apply for MOD = 00, this one I think is better than the first RR_GetReg()
function because instead of duplicating the process for both d-bit positions, it just assumed the d bit is 1,
then flips the operands at the end if the d-bit is 0
- Note: I should think about redoing RR_GetReg() in a similar fashion
- I should also maybe think about a better way to implement these decoding tables other than these long
explicit functions with large switch statements; maybe I can implement some kind of key:value type structure
- Speaking of the big switch statements I changed the formatting on them a lot, in a way that makes 
them easier to read at a glance since they are basically lookup tables.

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
- Still want to inspect the assembly to investigate this because it seems like a good learning opportunity,
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