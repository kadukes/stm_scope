/**
  ******************************************************************************
  * @file           : hello.c
  * @brief          : Hello World task implementation
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "hello.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f429i_discovery_lcd.h"
#include "lcd.h"
#include "colorcycling.h"


osThreadId helloWorldTaskHandle;

extern image_t fire_image;


uint8_t color_key_for_pixel(image_t *image, size_t col, size_t row) {
  size_t i = col + row * fire_image.width;
  uint8_t color_key = fire_image.data[i];
  return color_key;
}

color_t color_key_to_color(image_t *image, palette_t *palette, uint8_t color_key) {
  uint8_t color_key_mapping = palette->mapping[color_key];
  color_t color = fire_image.colors[color_key_mapping];
  return color;
}

// Helper to free palette linked list
static void free_palette_list(palette_t *head) {
  palette_t *curr = head;
  while (curr != NULL) {
    palette_t *next = curr->next;
    free(curr);
    curr = next;
  }
}

void plot_animation(void) {
  pixel *const fb = lcd_get_fb();
  static palette_t *current_palette = NULL;
  static palette_t *palette_list_head = NULL;
  if (current_palette == NULL) {
    palette_list_head = fire_image.generate_palettes();
    current_palette = palette_list_head;
  }

  palette_t *p = current_palette;

  for (size_t x = 0; x < fire_image.width; x++) {
    for (size_t y = 0; y < fire_image.height; y++) {
      uint8_t color_key = color_key_for_pixel(&fire_image, x, y);
      color_t color = color_key_to_color(&fire_image, p, color_key);
      lcd_set_pixel(fb, x, y, color);
    }
  }

  // Advance to next palette for next iteration
  if (current_palette->next != NULL) {
    current_palette = current_palette->next;
  } else {
    // Free old palette list before restarting
    free_palette_list(palette_list_head);
    palette_list_head = fire_image.generate_palettes();
    current_palette = palette_list_head;
  }
}


/**
  * @brief  Initialize Hello World module
  * @retval None
  */
void hello_init(void)
{
  osThreadDef(helloWorldTask, StartHelloWorldTask, osPriorityNormal, 0, 512);
  helloWorldTaskHandle = osThreadCreate(osThread(helloWorldTask), NULL);
}

/**
  * @brief  Function implementing the helloWorldTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartHelloWorldTask(void const * argument)
{
  uint32_t counter = 0;
  
  /* Infinite loop */
  for(;;)
  {
    printf("Hello World from STM32! Counter: %lu\r\n", counter++);
    plot_animation();
    osDelay(300);
  }
}

