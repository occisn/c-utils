#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

bool stb_save_image(const char *filename,
                           int height,
                           int width,
                           uint8_t **r_array,
                           uint8_t **g_array,
                           uint8_t **b_array)
{
  const int channels = 3;
  uint8_t *rgb = malloc(width * height * channels);
  if (!rgb) {
    fprintf(stderr, "Failed to allocate RGB buffer for saving");
    return false;
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int idx = (y * width + x) * channels;
      rgb[idx + 0] = r_array[y][x];
      rgb[idx + 1] = g_array[y][x];
      rgb[idx + 2] = b_array[y][x];
    }
  }

  // stbi_write_bmp(filename, width, height, channels, rgb);

  // stbi_write_png(filename,
  //                width,
  //                height,
  //                channels,
  //                rgb,
  //                width * channels);

  const int quality = 90;
  stbi_write_jpg(filename,
                 width,
                 height,
                 channels,
                 rgb,
                 quality);

  free(rgb);
  return true;
}

/**
 * Saves RGB image data as a 24-bit BMP file.
 *
 * Creates an uncompressed BMP image file from separate red, green, and blue
 * channel arrays. The BMP format uses BGR pixel order and stores rows in
 * bottom-up order (last row first). Row data is padded to 4-byte boundaries
 * as required by the BMP specification.
 *
 * @param filename  Output file path for the BMP image
 * @param height    Image height in pixels
 * @param width     Image width in pixels
 * @param r_array   2D array of red channel values [height][width], range 0-255
 * @param g_array   2D array of green channel values [height][width], range 0-255
 * @param b_array   2D array of blue channel values [height][width], range 0-255
 *
 * @note Arrays are indexed as [y][x] where y increases downward from 0 to height-1
 * @note Function prints an error message and returns early if file cannot be opened
 * @note Prints success message with filename upon completion
 *
 * (function proposed by AI)
 */
void save_bmp(const char *filename, int height, int width, uint8_t **r_array, uint8_t **g_array, uint8_t **b_array)
{
  FILE *f = fopen(filename, "wb");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file for writing");
    return;
  }

  // BMP file header (14 bytes)
  uint8_t file_header[14] = {
      'B', 'M',   // Signature
      0, 0, 0, 0, // File size (we'll update later)
      0, 0,       // Reserved
      0, 0,       // Reserved
      54, 0, 0, 0 // Pixel data offset (54 bytes)
  };

  // BMP info header (40 bytes)
  uint8_t info_header[40] = {
      40, 0, 0, 0, // Header size
      0, 0, 0, 0,  // Image width (we'll update later)
      0, 0, 0, 0,  // Image height (we'll update later)
      1, 0,        // Color planes (1)
      24, 0,       // Bits per pixel (24 for RGB)
      0, 0, 0, 0,  // Compression (none)
      0, 0, 0, 0,  // Image size (we'll update later)
      0, 0, 0, 0,  // Horizontal resolution
      0, 0, 0, 0,  // Vertical resolution
      0, 0, 0, 0   // Colors in palette (0 means no palette)
  };

  // Calculate row size and padding
  int row_size = width * 3;               // 3 bytes per pixel (RGB)
  int padding = (4 - (row_size % 4)) % 4; // Padding to align rows to 4 bytes

  // Calculate the total file size
  int data_size = (row_size + padding) * height; // Pixel data size
  int file_size = 54 + data_size;                // File header + info header + pixel data

  // Update file header with the actual file size
  file_header[2] = (file_size & 0xFF);
  file_header[3] = (file_size >> 8) & 0xFF;
  file_header[4] = (file_size >> 16) & 0xFF;
  file_header[5] = (file_size >> 24) & 0xFF;

  // Update info header with image width and height
  info_header[4] = (width & 0xFF);
  info_header[5] = (width >> 8) & 0xFF;
  info_header[6] = (width >> 16) & 0xFF;
  info_header[7] = (width >> 24) & 0xFF;

  info_header[8] = (height & 0xFF);
  info_header[9] = (height >> 8) & 0xFF;
  info_header[10] = (height >> 16) & 0xFF;
  info_header[11] = (height >> 24) & 0xFF;

  // Write file header and info header to file
  fwrite(file_header, sizeof(uint8_t), 14, f);
  fwrite(info_header, sizeof(uint8_t), 40, f);

  // Write pixel data (bottom-up order)
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x < width; x++) {
      // BMP stores pixels in BGR order, not RGB
      uint8_t b = b_array[y][x];
      uint8_t g = g_array[y][x];
      uint8_t r = r_array[y][x];
      fwrite(&b, sizeof(uint8_t), 1, f);
      fwrite(&g, sizeof(uint8_t), 1, f);
      fwrite(&r, sizeof(uint8_t), 1, f);
    }
    // Add padding to the row if necessary
    for (int i = 0; i < padding; i++) {
      uint8_t pad = 0;
      fwrite(&pad, sizeof(uint8_t), 1, f);
    }
  }

  // Close the file
  fclose(f);
  printf("BMP file saved as %s\n", filename);
}

/**
 * @brief Saves an RGB image to a PNG file without compression.
 *
 * Creates a valid PNG file from separate red, green, and blue channel arrays.
 * The image data is stored in uncompressed zlib format (BTYPE=00) with no
 * filtering applied to scanlines.
 *
 * @param filename  Path to the output PNG file (will be overwritten if exists)
 * @param height    Image height in pixels (number of rows)
 * @param width     Image width in pixels (number of columns)
 * @param r_array   2D array [height][width] of red channel values (0-255)
 * @param g_array   2D array [height][width] of green channel values (0-255)
 * @param b_array   2D array [height][width] of blue channel values (0-255)
 *
 * @note The function silently fails if the file cannot be opened.
 * @note No validation is performed on input parameters or memory allocations.
 * @note The resulting PNG uses 8-bit RGB color (no alpha channel).
 * @note All dynamically allocated memory is freed before returning.
 *
 * @warning Ensure all arrays are properly allocated before calling this function.
 * @warning No error code is returned; check file creation separately if needed.
 *
 * @example
 * uint8_t **r = malloc(height * sizeof(uint8_t *));
 * uint8_t **g = malloc(height * sizeof(uint8_t *));
 * uint8_t **b = malloc(height * sizeof(uint8_t *));
 * for (int y = 0; y < height; y++) {
 *     r[y] = malloc(width);
 *     g[y] = malloc(width);
 *     b[y] = malloc(width);
 *     // ... fill arrays with pixel data ...
 * }
 * save_png("output.png", height, width, r, g, b);
 *
 * (function proposed by AI)
 */
void save_png(const char *filename, int height, int width,
              uint8_t **r_array, uint8_t **g_array, uint8_t **b_array)
{

  uint32_t crc_table[256];

  for (uint32_t n = 0; n < 256; n++) {
    uint32_t c = n;
    for (int k = 0; k < 8; k++)
      c = (c & 1) ? (0xEDB88320U ^ (c >> 1)) : (c >> 1);
    crc_table[n] = c;
  }
  // make_crc_table();

  FILE *f = fopen(filename, "wb");
  if (!f)
    return;

  /* PNG signature */
  static const uint8_t sig[8] = {
      137, 80, 78, 71, 13, 10, 26, 10};
  fwrite(sig, 1, 8, f);

  /* IHDR */
  uint8_t ihdr[13];
  ihdr[0] = (width >> 24) & 0xFF;
  ihdr[1] = (width >> 16) & 0xFF;
  ihdr[2] = (width >> 8) & 0xFF;
  ihdr[3] = width & 0xFF;
  ihdr[4] = (height >> 24) & 0xFF;
  ihdr[5] = (height >> 16) & 0xFF;
  ihdr[6] = (height >> 8) & 0xFF;
  ihdr[7] = height & 0xFF;
  ihdr[8] = 8;  /* bit depth */
  ihdr[9] = 2;  /* color type: RGB */
  ihdr[10] = 0; /* compression */
  ihdr[11] = 0; /* filter */
  ihdr[12] = 0; /* interlace */

  // write_chunk(f, "IHDR", ihdr, 13, crc_table);
  //
  // WRITE CHUNK
  const char *type_1 = "IHDR";
  const uint8_t *data_1 = ihdr;
  const uint32_t length_1 = 13;
  //
  // write_u32:
  uint32_t v_1 = length_1;
  fputc((v_1 >> 24) & 0xFF, f);
  fputc((v_1 >> 16) & 0xFF, f);
  fputc((v_1 >> 8) & 0xFF, f);
  fputc(v_1 & 0xFF, f);
  //
  fwrite(type_1, 1, 4, f);
  if (length_1)
    fwrite(data_1, 1, length_1, f);
  //
  uint8_t *tmp_1 = malloc(4 + length_1);
  memcpy(tmp_1, type_1, 4);
  if (length_1)
    memcpy(tmp_1 + 4, data_1, length_1);
  //
  // crc32:
  uint32_t c_1 = 0xFFFFFFFFU;
  for (size_t i = 0; i < 4 + length_1; i++)
    c_1 = crc_table[(c_1 ^ tmp_1[i]) & 0xFF] ^ (c_1 >> 8);
  uint32_t crc32_1 = c_1 ^ 0xFFFFFFFFU;
  //
  // write_u32:
  v_1 = crc32_1;
  fputc((v_1 >> 24) & 0xFF, f);
  fputc((v_1 >> 16) & 0xFF, f);
  fputc((v_1 >> 8) & 0xFF, f);
  fputc(v_1 & 0xFF, f);
  //
  free(tmp_1);

  /* Raw image data (filter byte + RGB per row) */
  size_t row_size = 1 + 3 * width;
  size_t raw_size = row_size * height;
  uint8_t *raw = malloc(raw_size);

  for (int y = 0; y < height; y++) {
    raw[y * row_size] = 0; /* filter type 0 */
    for (int x = 0; x < width; x++) {
      raw[y * row_size + 1 + 3 * x + 0] = r_array[y][x];
      raw[y * row_size + 1 + 3 * x + 1] = g_array[y][x];
      raw[y * row_size + 1 + 3 * x + 2] = b_array[y][x];
    }
  }

  /* zlib stream (stored / no compression, multi-block safe) */
  size_t max_blocks = (raw_size + 65534) / 65535;
  size_t zsize = 2 + raw_size + max_blocks * 5 + 4;
  uint8_t *z = malloc(zsize);

  size_t p = 0;

  /* zlib header */
  z[p++] = 0x78;
  z[p++] = 0x01;

  size_t offset = 0;
  while (offset < raw_size) {
    uint16_t block_len = (raw_size - offset > 65535)
                             ? 65535
                             : (uint16_t)(raw_size - offset);

    uint8_t final = (offset + block_len == raw_size);

    z[p++] = final ? 0x01 : 0x00; /* BFINAL + BTYPE=00 */
    z[p++] = block_len & 0xFF;
    z[p++] = (block_len >> 8) & 0xFF;
    z[p++] = (~block_len) & 0xFF;
    z[p++] = ((~block_len) >> 8) & 0xFF;

    memcpy(z + p, raw + offset, block_len);
    p += block_len;
    offset += block_len;
  }

  /* Adler-32 */
  uint32_t a = 1, b = 0;
  for (size_t i = 0; i < raw_size; i++) {
    a = (a + raw[i]) % 65521;
    b = (b + a) % 65521;
  }
  uint32_t ad = (b << 16) | a;
  z[p++] = (ad >> 24) & 0xFF;
  z[p++] = (ad >> 16) & 0xFF;
  z[p++] = (ad >> 8) & 0xFF;
  z[p++] = ad & 0xFF;

  // write_chunk(f, "IDAT", z, p, crc_table);
  //
  // WRITE CHUNK
  const char *type_2 = "IDAT";
  const uint8_t *data_2 = z;
  uint32_t length_2 = p;
  //
  // write_u32:
  uint32_t v_2 = length_2;
  fputc((v_2 >> 24) & 0xFF, f);
  fputc((v_2 >> 16) & 0xFF, f);
  fputc((v_2 >> 8) & 0xFF, f);
  fputc(v_2 & 0xFF, f);
  //
  fwrite(type_2, 1, 4, f);
  if (length_2)
    fwrite(data_2, 1, length_2, f);
  //
  uint8_t *tmp_2 = malloc(4 + length_2);
  memcpy(tmp_2, type_2, 4);
  if (length_2)
    memcpy(tmp_2 + 4, data_2, length_2);
  //
  // crc32:
  uint32_t c_2 = 0xFFFFFFFFU;
  for (size_t i = 0; i < 4 + length_2; i++)
    c_2 = crc_table[(c_2 ^ tmp_2[i]) & 0xFF] ^ (c_2 >> 8);
  uint32_t crc32_2 = c_2 ^ 0xFFFFFFFFU;
  //
  // write_u32:
  v_2 = crc32_2;
  fputc((v_2 >> 24) & 0xFF, f);
  fputc((v_2 >> 16) & 0xFF, f);
  fputc((v_2 >> 8) & 0xFF, f);
  fputc(v_2 & 0xFF, f);
  //
  free(tmp_2);

  // write_chunk(f, "IEND", NULL, 0, crc_table);
  //
  // WRITE CHUNK
  const char *type_3 = "IEND";
  // const uint8_t *data_3 = NULL;
  uint32_t length_3 = 0;
  //
  // write_u32:
  uint32_t v_3 = length_3;
  fputc((v_3 >> 24) & 0xFF, f);
  fputc((v_3 >> 16) & 0xFF, f);
  fputc((v_3 >> 8) & 0xFF, f);
  fputc(v_3 & 0xFF, f);
  //
  fwrite(type_3, 1, 4, f);
  //
  uint8_t *tmp_3 = malloc(4 + length_3);
  memcpy(tmp_3, type_3, 4);
  //
  // crc32:
  uint32_t c_3 = 0xFFFFFFFFU;
  for (size_t i = 0; i < 4 + length_3; i++)
    c_3 = crc_table[(c_3 ^ tmp_3[i]) & 0xFF] ^ (c_3 >> 8);
  uint32_t crc32_3 = c_3 ^ 0xFFFFFFFFU;
  //
  // write_u32:
  v_3 = crc32_3;
  fputc((v_3 >> 24) & 0xFF, f);
  fputc((v_3 >> 16) & 0xFF, f);
  fputc((v_3 >> 8) & 0xFF, f);
  fputc(v_3 & 0xFF, f);
  //
  free(tmp_3);

  free(raw);
  free(z);
  fclose(f);
}

/**
 * Helper to convert Hue to RGB component
 */
static double hue_to_rgb(double p, double q, double t)
{
  if (t < 0.0)
    t += 1.0;
  if (t > 1.0)
    t -= 1.0;
  if (t < (1.0 / 6.0))
    return p + (q - p) * 6.0 * t;
  if (t < 0.5)
    return q;
  if (t < (2.0 / 3.0))
    return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
  return p;
}

/**
 * Heatmap Generator
 * @param height        Image height
 * @param width         Image width
 * @param value_array   A pointer to a array of height x width
 * @param export_file   Filename string
 */
bool draw_heatmap_from_values(int height, int width, const double *value_array, const char *export_file)
{
  if (height <= 0 || width <= 0 || !value_array)
    return false;

  // (1) Calculate min, max, and range

  double value_min = value_array[0];
  double value_max = value_array[0];

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      double z = value_array[y * width + x];
      if (z < value_min)
        value_min = z;
      if (z > value_max)
        value_max = z;
    }
  }

  double value_range = value_max - value_min;

  // (2) Calculate RGB values

  uint8_t *rgb_image = (uint8_t *)malloc(width * height * 3);
  if (!rgb_image)
    return false;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      double z = value_array[y * width + x];
      double w = (z - value_min) / value_range;

      double h = (w * 1.2) / 3.6;
      double s = 1.0;
      double l = 0.5;

      double q = l + s - l * s;
      double p = 2.0 * l - q;

      // Calculate flat index for the output buffer
      int pixel_idx = (y * width + x) * 3;
      rgb_image[pixel_idx + 0] = (uint8_t)(fmin(255.0, floor(255.0 * hue_to_rgb(p, q, h + 1.0 / 3.0))));
      rgb_image[pixel_idx + 1] = (uint8_t)(fmin(255.0, floor(255.0 * hue_to_rgb(p, q, h))));
      rgb_image[pixel_idx + 2] = (uint8_t)(fmin(255.0, floor(255.0 * hue_to_rgb(p, q, h - 1.0 / 3.0))));
    }
  }

  // (3) Export to JPG
  const int quality = 90;
  const int channels = 3;
  if (stbi_write_jpg(export_file, width, height, channels, rgb_image, quality) == 0) {
    fprintf(stderr, "Problem in stbi_write_jpg\n");
    free(rgb_image);
    return false;
  }

  free(rgb_image);

  return true;
}

// end
