> Decided to keep all the code for this section in a single project directory since regen-ing projects is genuinely blowing up my blob sizes lmao

# sec-02/ex-01 - Custom HAL GPIO implementations

Fairly simple exercise. I was sort of being dumb at first though as I had forgot that `main.h` contains the defines for the pins that I renamed in CubeMX:

`main.h`:

```h
#define BLUE_PB_Pin GPIO_PIN_13   // I renamed that blue push button pin to `BLUE_PB`
#define BLUE_PB_GPIO_Port GPIOC   // It changed here as well
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define GREEN_LED_Pin GPIO_PIN_5   // I renamed GPIO5 (the green LED) to `GREEN_LED_Pin`
#define GREEN_LED_GPIO_Port GPIOA  // It changed here as well
```

Afterwards it was trivial to write the code that satisfies the exercise:

`main.c`:

```c
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // idk why but for some reason SET means the button is not being pushed and 
    // RESET means that it is being pushed
    if (HAL_GPIO_ReadPin(BLUE_PB_GPIO_Port, BLUE_PB_Pin) == GPIO_PIN_RESET) {
      // LED_state = !LED_state;
      HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
```