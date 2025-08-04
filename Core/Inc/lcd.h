
#ifndef __LCD_H_
#define __LCD_H_

#define LCD_WIDTH  240
#define LCD_HEIGHT 320

typedef uint16_t pixel;

/**
 * \brief Returns a pointer to the beginning of the frame buffer of the LCD.
 *
 * Do not modify the memory directly, use lcd_set_pixel instead.
 */
static pixel* const lcd_get_fb(void);

/**
 * \brief Sets one pixel of the LCD.
 *
 * \param fb Pointer to begin of frame buffer, see lcd_get_fb().
 * \param x  x coordinate of the pixel to set.
 * \param y  y coordinate of the pixel to set.
 * \param r  Red value of the color of the pixel.
 * \param g  Green value of the color of the pixel.
 * \param b  Blue value of the color of the pixel.
 */
static void lcd_set_pixel(pixel *const fb, size_t x, size_t y, pixel color);


static inline __attribute__((always_inline)) pixel* const lcd_get_fb(void) { return (pixel *)LCD_FRAME_BUFFER; }

static inline __attribute__((always_inline)) void lcd_set_pixel(pixel *const fb, size_t x, size_t y, pixel color) {
	fb[x + y * LCD_WIDTH] = color;
}

#endif // __LCD_H_