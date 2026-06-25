#include <M5GFX.h>
#include <M5Unified.h>

#include "esp_random.h"

M5GFX display;	// 320x240px, ~70Hz

#include "constants.h"
#include "double_buffer.h"
#include "eyes.h"
#include "types.h"

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

	display.fillScreen(BACKGROUND_COLOR);
	display.endWrite();
}

// Called every frame, owns the SPI bus due to DMA so don't draw anything else without calling `waitDMA` first.
void frame(DoubleBuffer &double_buff, unsigned long tick_count, Face &face) {
	display.pushImageDMA(0, 0, double_buff.width, double_buff.height,
						 (uint16_t *)double_buff.get_display_buffer().getBuffer());

	if (face.ticks_before_blink == 0) {
		face.ticks_before_blink = esp_random() % BlinkAnimation::MAX_WAIT_TICKS;
		face.state.transition_to(State::BLINKING);
	} else {
		face.ticks_before_blink--;
	}

	double_buff.get_draw_buffer().fillSprite(BACKGROUND_COLOR);
	face.draw(double_buff.get_draw_buffer(), tick_count);
}

// Called on every frame but doesn't own the SPI bus
void hud(M5GFX &display) {
	// Do not use canvas or DMA here as it would likely be too slow and cause the FPS to drop.
}

void exec(Face &face) {
	if (M5.BtnA.wasPressed()) {
		face.set_expression(FaceExpression::NORMAL);
	} else if (M5.BtnB.wasPressed()) {
		face.set_expression(FaceExpression::ANGRY);
	} else if (M5.BtnC.wasPressed()) {
		face.set_expression(FaceExpression::SAD);
	}
}

unsigned long elapsed_time = 0;
unsigned long time_reset = 0;

u64 tick_count = 0;	 // Won't ever overflow at 60FPS, but just in case, we use a 64-bit integer.

bool loop_init = false;

void loop() {
	M5.update();

	static DoubleBuffer double_buf(
		display, MAX_EYE_WIDTH * 2 + NormalEye::EYE_DISTANCE + NormalEye::EYE_RADIUS,
		MAX_EYE_HEIGHT + NormalEye::EYE_RADIUS);
	static Face face(double_buf.get_draw_buffer(), FOREGROUND_COLOR, NormalEye::EYE_RADIUS);

	exec(face);

	display.waitDisplay();
	elapsed_time = millis();
	if (elapsed_time - time_reset >= frame_delay) {
		Serial.printf("FPS: %f\n", 1000.0 / (elapsed_time - time_reset));
		time_reset = elapsed_time;
		tick_count++;

		display.startWrite();

		frame(double_buf, tick_count, face);

		display.waitDMA();

		hud(display);

		display.endWrite();

		double_buf.swap();
	}
}
