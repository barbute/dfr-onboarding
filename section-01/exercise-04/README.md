Was able to flash successfully (the little green LED blinks as expected)!

Steps I took:
1. Connect board to computer
2. Verify connection using `st-info --probe`
3. In the `blinky/` directory, run `make` to compile the code and generate the binary
4. Flash the STM by going into the `blinky/` directory and running `st-flash write build/blinky.bin 0x08000000`
  - Use `blinky.bin` rather than `blinky.elf`; idk why the `.elf` file is so large lol but uploading the `.bin` appears to work fine
  - `0x08000000` is the address for the start of the flash memory on the STM