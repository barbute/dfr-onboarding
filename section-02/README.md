# sec-02/ex-01 - Custom HAL GPIO implementations

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

This exercise just showed how to use the external interrupt handler callback function could be used to handle inputs for external peripherals.`

## Part 2 - Callback function

Followed [this tutorial](https://community.st.com/stm32-mcus-60/how-to-use-register-callbacks-in-stm32-119508).

> NOTE I was unable to set the `HCLK` frequency to $250$ MHz as specified in the tutorial. I left it at $48$ MHz as that was the max that CubeMX would let me set it to. I have not yet made any other major changes to the tutorial's instructions.

I followed the tutorial to the best of my abilities, and in the end, the program mostly worked. There were some problems however, namely the fact that the board I am using primarily supports [USART](https://en.wikipedia.org/wiki/Universal_synchronous_and_asynchronous_receiver-transmitter) (which is like [UART](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter) but also supports synchronous communication). STMCubeMX would only let me configure my pins to be USART, meaning that every function definition and parameter that involved UART in the tutorial had to be changed to USART. Additionally the Register CallBack (found under Project Manager > Advanaced Settings > Register CallBack Panel) for USART was not enabled as I had only set it to UART. I had to fix this by going to [`exercise-03-dfr-onboarding-clbk/Core/Inc/stm32f0xx_hal_conf.h`](exercise-03-dfr-onboarding-clbk/Core/Inc/stm32f0xx_hal_conf.h) and defining `USE_HAL_USART_REGISTER_CALLBACKS` to be `1U` (instead of regenerating the entire program again).

I actually found this experience to be moderately enlightening, as I now see that CubeMX is basiaclly a GUI wrapper for configuring your board. All of the include definitions are based on some variables set in this config file (IE the program only includes certain HAL files if enabled in CubeMX when generating the code). I do think the bloat is kinda of annoying, as in including all of these unnecessary files with each project is a bit of a waste, but it's useful if you want to enable certain functionality late.

For actually viewing the messages coming in via USART over USB, I had to download [PuTTY](https://en.wikipedia.org/wiki/PuTTY) and simply used it to view the serial connection. CubeIDE didn't have a Serial Terminal that I could use, which is why I went with PuTTY (lowk though PuTTY makes it a lot easier). Just don't forget to set the baud rate to what you set USART to in CubeMX (for this project it was $115200$ Bits/s 8n1).

Also since I was not able to set `HCLK` to $250$ MHz, the messages were firing at a much slower rate than they should have been.

This entire exercise was literally just looking at how the headers wanted callbacks defined, and then defining those callback functions in `main.c`. To register your own clbk functions, just lookup which clbk IDs are relevant for your use case. In this exercise we used `HAL_USART_TX_COMPLETE_CB_ID` to fire the LED whenever USART completed a transmission and `HAL_TIM_PERIOD_ELAPSED_CB_ID` to fire off the USART message that the timer period was over (the timer period was defined in the `TIM1` timer parameter settings in CubeMX).

Anyways I'm going to go eat dinner now.

# sec-02/ex-04

i'm doing this late b/c i'm on mac rn