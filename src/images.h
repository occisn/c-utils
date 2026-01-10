#pragma once

void save_bmp(const char *filename, int height, int width, uint8_t **r_array, uint8_t **g_array, uint8_t **b_array);
void save_png(const char *const filename, const int height, const int width, uint8_t **r_array, uint8_t **g_array, uint8_t **b_array);

// end

