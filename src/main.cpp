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
	display.fillScreen(BACKGROUND_COLOR);
	display.endWrite();
}

// Function is called FPS times per second
void frame(m5gfx::M5Canvas &canvas, unsigned long tick_count, Face &face) {
	face.draw(canvas, tick_count);
	canvas.pushSprite(0, 0);
}

void exec(Face &face) {
	if (M5.BtnA.wasPressed()) {
		face.expression = FaceExpression::NORMAL;
	} else if (M5.BtnB.wasPressed()) {
		face.expression = FaceExpression::ANGRY;
	} else if (M5.BtnC.wasPressed()) {
		face.state.transition_to(State::BLINKING);
		// face.expression = FaceExpression::SAD;
	}
}

unsigned long elapsed_time = 0;
unsigned long time_reset = 0;

unsigned long tick_count = 0;

bool loop_init = false;

void loop() {
	M5.update();
	static m5gfx::M5Canvas canvas(&display);

	if (!loop_init) {
		canvas.setColorDepth(16);
		// Adjust size relative to what we want to dinamically draw on the display
		// Reducing this is a big improvement in memory usage
		canvas.createSprite(display.width(), display.height());
		loop_init = true;
	}
	static Face face(canvas, FOREGROUND_COLOR, NormalEye::EYE_RADIUS);

	exec(face);

	display.waitDisplay();
	elapsed_time = millis();
	if (elapsed_time - time_reset >= frame_delay) {
		time_reset = elapsed_time;
		tick_count++;
		display.startWrite();
		frame(canvas, tick_count, face);
		display.endWrite();
	}
}
