#pragma once
#include <M5GFX.h>

#include "types.h"
#include "constants.h"

struct DoubleBuffer {
	i32 width, height;
	m5gfx::M5Canvas canvas[2];
	uint16_t *buffer[2] = { nullptr, nullptr };
	int draw_buffer = 0;

	DoubleBuffer(M5GFX &display, i32 width, i32 height) {
		(void)
			display;  // canvases are default-constructed; parent not needed for display.pushImageDMA

		size_t buffer_size = (size_t)width * (size_t)height * sizeof(uint16_t);
		this->buffer[0] = (uint16_t *)lgfx::heap_alloc_dma(buffer_size);
		this->buffer[1] = (uint16_t *)lgfx::heap_alloc_dma(buffer_size);

		if (!this->buffer[0] || !this->buffer[1]) {
			Serial.println("Failed to allocate DMA-capable buffers!");
		}

		canvas_setup(this->canvas[0], this->buffer[0], width, height);
		canvas_setup(this->canvas[1], this->buffer[1], width, height);

		this->draw_buffer = 0;
		this->width = width;
		this->height = height;
	}

	~DoubleBuffer() {
		lgfx::heap_free(this->buffer[0]);
		lgfx::heap_free(this->buffer[1]);
	}

	void swap() { draw_buffer ^= 1; }
	m5gfx::M5Canvas &get_draw_buffer() { return canvas[draw_buffer]; }
	m5gfx::M5Canvas &get_display_buffer() { return canvas[draw_buffer ^ 1]; }
	static void canvas_setup(m5gfx::M5Canvas &canvas, uint16_t *buffer, i32 width, i32 height) {
		canvas.setColorDepth(16);
		canvas.setBuffer(buffer, width, height, 16);
		canvas.fillSprite(BACKGROUND_COLOR);
	}
};
