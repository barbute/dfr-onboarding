# sec-02/ex-03 - Custom HAL GPIO implementations

for sec-02/ex-01 John said to only do the last two:

> Do the exact same for `void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)` and `void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`

Notes over `HAL_GPIO_WritePin` portion:

> These notes are written to the best of my understanding of the system at the current moment.

Here I "wrote" this code to blink allow for writing to a GPIO pin (no it is not perfect though it just about functions):

```c
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                       GPIO_PinState PinState) {
  if (PinState == GPIO_PIN_SET) {
    GPIOx->BSRR = GPIO_Pin;
  } else {
    GPIOx->BRR = GPIO_Pin;
  }
}
```

At first this code may not make any sense. We are setting the `BSRR` register to the bit-value that is the `GPIO_Pin` (it's actual bit address at the hardware level). How does that make any sense? Aren't we trying to write directly to the pin? Well yes, this is exactly what the code is doing in fact.

Recall that at the hardware level, GPIO pins are mapped to some address represented in binary (e.g. `GPIO_Pin_5` may mapped to `0x05`). `BSRR` is a special GPIO register on the STM32; when we write the GPIO pin's address to it, we are telling the hardware to operate on that specific pin. `BSRR` will then go ahead and write a digital high signal to specified pin (`PIN_SET`). However if we want to reset the pin we must instead use the `BRR` register as that will trigger a write-digital-low operation to the specified pin that it is set to.

I could also be making all of this stuff up b/c yeah ts is hard but I think this is what is happening on the STM at a high level.

# sec-02/ex-03 - Register custom callback functions for specific peripherals

## Part 1 - EXTI

for sec-02/ex-03 I had to follow [this tutorial](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_EXTI). Note that after creating the project for the board in STM32CubeMX, to set the correct build system (the default is EWARM for whatever reason, use Make or CMake since that's what we've set up).

After setting the pin configurations I then opened the project in the STM32CubeIDE and pasted in the `GPIO_EXTI` callback function. I then built and deployed the code from the IDE. Pressing the blue button turns the green LED on, and reset turns it off.

## Part 2 - Callback function

Followed [this tutorial](https://community.st.com/stm32-mcus-60/how-to-use-register-callbacks-in-stm32-119508).

> NOTE I was unable to set the `HCLK` frequency to $250$ MHz as specified in the tutorial. I left it at $48$ MHz as that was the max that CubeMX would let me set it to. I have not yet made any other major changes to the tutorial's instructions.