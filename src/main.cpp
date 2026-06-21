#include <M5GFX.h>
#include <M5Unified.h>

M5GFX display;	// 320x240px, ~70Hz

#include "eyes.h"
#include "types.h"

const auto BACKGROUND_COLOR = TFT_BLACK;
const auto FOREGROUND_COLOR = TFT_WHITE;

#define FPS 60
const u32 frame_delay = 1000 / FPS;

void setup() {
	Serial.begin(115200);
	M5.begin();

	display.init();
	display.startWrite();
	display.fillScreen(BACKGROUND_COLOR);

	if (display.isEPD()) {
		display.setEpdMode(epd_mode_t::epd_fastest);
	}
	if (display.width() < display.height()) {
		display.setRotation(display.getRotation() ^ 1);
	}

	display.startWrite();
	display.setColorDepth(8);
	display.fillScreen(BACKGROUND_COLOR);

	m5gfx::M5Canvas canvas(&display);
	// Adjust size relative to what we want to dinamically draw on the display
	// Reducing this is a big improvement in memory usage
	canvas.createSprite(display.width(), display.height());

	canvas.fillSprite(TFT_BLACK);
	draw_eyes(canvas);
	canvas.pushSprite(0, 0);

	display.endWrite();
}

// Function is called FPS times per second
void frame(m5gfx::M5Canvas &canvas) {
	// canvas.fillSprite(TFT_BLACK);
	// draw_eyes(canvas);
	// canvas.pushSprite(0, 0);
}

unsigned long elapsed_time = 0;
unsigned long time_reset = 0;

void loop() {
	static m5gfx::M5Canvas canvas(&display);
	display.waitDisplay();
	elapsed_time = millis();
	if (elapsed_time - time_reset >= frame_delay) {
		time_reset = elapsed_time;
		display.startWrite();
		frame(canvas);
		display.endWrite();
	}
}
