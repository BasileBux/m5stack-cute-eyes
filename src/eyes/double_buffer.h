#pragma once
#include <M5GFX.h>

#include "../constants.h"
#include "../types.h"

struct DoubleBuffer {
	i32 width, height;
	u32 pos_x, pos_y;
	m5gfx::M5Canvas canvas[2];
	uint16_t *buffer[2] = { nullptr, nullptr };
	int draw_buffer = 0;

	DoubleBuffer(i32 width, i32 height, u32 pos_x, u32 pos_y) {
		this->init(width, height, pos_x, pos_y);
	}

	// Centers the double buffer on the screen of the given display
	DoubleBuffer(M5GFX display, i32 width, i32 height) {
		u32 pos_x = (display.width() / 2) - (width / 2);
		u32 pos_y = (display.height() / 2) - (height / 2);
		this->init(width, height, pos_x, pos_y);
	}

	void init(i32 width, i32 height, u32 pos_x, u32 pos_y) {
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
		this->pos_x = pos_x;
		this->pos_y = pos_y;
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
	void center_on_screen(u32 screen_width, u32 screen_height) {
		this->pos_x = (screen_width / 2) - (this->pos_x / 2);
		this->pos_y = (screen_height / 2) - (this->pos_y / 2);
	}
	void draw_to_display(M5GFX &display) {
		display.pushImageDMA(this->pos_x, this->pos_y, this->width, this->height,
							 (uint16_t *)this->get_display_buffer().getBuffer());
	}
};
