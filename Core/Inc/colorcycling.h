/*!
 * @file colorcycling.h
 * @brief A simple color cycling interface.
 * \ingroup colorcycling
 */


#ifndef _COLORCYCLING_H_
#define _COLORCYCLING_H_

#include <stddef.h>
#include <stdint.h>

/** Color encoding in RGB565 */
typedef uint16_t color_t;

#define COLOR_KEYS 15
#define FRAMES 4

/** A palette is a mapping of a color key to a color. */
typedef struct palette {
	uint8_t mapping[COLOR_KEYS];
	struct palette *next;
} palette_t;

/**
 * \brief Function type to generate NULL-terminated list of palettes.
 *
 * \return Pointer to the first element of a linked list of palettes.
 *
 * NOTE: The returned list must be freed by the caller.
 */
typedef palette_t* (*palette_generator_t)(void);

/** Description of a colorcycling-animated image. */
typedef struct image {
	size_t width;
	size_t height;
	size_t num_colors;
	color_t *colors;
	palette_generator_t generate_palettes;
	uint8_t *data;
} image_t;

/**
 * \brief Returns the color key of a given pixel.
 *
 * Pixels are stored row-wise.
 * The color key for a pixel is stored in 4 bits (a nibble) of data, meaning each byte of the image data stores the color key for two pixels.
 * Image data starts at the top nibble of a byte (starting from the most significant bit).
 *
 * \param image Image to be drawn, storing color key information.
 * \param col Column position of the pixel.
 * \param row Row position of the pixel.
 * \return Color key for the pixel.
 */
uint8_t color_key_for_pixel(image_t *image, size_t col, size_t row);

/**
 * \brief Converts a color key to a color according to the given palette.
 *
 * \param image Image to be drawn, storing the colors of the image.
 * \param palette Color palette of the current frame.
 * \param color_key Color key.
 * \return Color corresponding to the color key in the current palette.
 */
color_t color_key_to_color(image_t *image, palette_t *palette, uint8_t color_key);

#endif
