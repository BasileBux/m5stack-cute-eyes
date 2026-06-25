#pragma once

#include <M5GFX.h>

#include "types.h"

struct Size {
	i32 width, height;
};

namespace NormalEye {
	// const u32 EYE_WIDTH = 66;
	// const u32 EYE_HEIGHT = 95;
	const u32 EYE_WIDTH = 56;
	const u32 EYE_HEIGHT = 85;
	const Size EYE_SIZE = { EYE_WIDTH, EYE_HEIGHT };
	const u32 EYE_RADIUS = 12;
	const u32 EYE_DISTANCE = 30;
}  // namespace NormalEye

namespace AngrySadEye {
	const i32 ANGLE = 6;
	const i32 DIAGONAL = ANGLE * 2 * 2;
}  // namespace AngrySadEye

namespace TransitionAnimation {
	const u32 DURATION = 8;	 // ticks
	const float ANGLE = (float)AngrySadEye::ANGLE / (float)DURATION;
}  // namespace TransitionAnimation

namespace IdleAnimation {
	const u8 WIDTH_DELTA = 1;
	const u32 WIDTH_DURATION = 90;	// ticks
	const float WIDTH_ANGLE = 2.0f * M_PI / (float)WIDTH_DURATION;

	const u8 HEIGHT_DELTA = 2;
	const u32 HEIGHT_DURATION = 60;	 // ticks
	const float HEIGHT_ANGLE = 2.0f * M_PI / (float)HEIGHT_DURATION;

	const u8 Y_DELTA = 3;
	const u32 Y_DURATION = 120;
	const float Y_ANGLE = 2.0f * M_PI / (float)Y_DURATION;
}  // namespace IdleAnimation

namespace BlinkAnimation {
	const u32 MAX_WAIT_TICKS = 600;
	const u32 DURATION = 20;  // ticks
	const float ANGLE = 1.f / (float)DURATION;
}  // namespace BlinkAnimation

const i32 MAX_EYE_WIDTH =
	NormalEye::EYE_WIDTH + IdleAnimation::WIDTH_DELTA + IdleAnimation::WIDTH_DELTA;
const i32 MAX_EYE_HEIGHT =
	NormalEye::EYE_HEIGHT + IdleAnimation::HEIGHT_DELTA * 2 + IdleAnimation::Y_DELTA * 2;

struct Eye {
	i32 pos_x, pos_y;
	i32 width, height;
	Eye(i32 pos_x, i32 pos_y, i32 width, i32 height);

	void draw_normal(m5gfx::M5Canvas &canvas, float radius, u16 color) const;
	void draw_down(m5gfx::M5Canvas &canvas, float radius, u16 color,
				   i32 angle = AngrySadEye::ANGLE) const;
	void draw_up(m5gfx::M5Canvas &canvas, float radius, u16 color,
				 i32 angle = AngrySadEye::ANGLE) const;
};

void test_bezier(m5gfx::M5Canvas &canvas);

enum FaceExpression {
	NORMAL,
	ANGRY,
	WEIRDED,
	SAD,
	// SQUINT,
	// HAPPY,
	// WICKED,
};

class State {
   public:
	unsigned long transition_ticks;

	enum Value : uint8_t {
		IDLE,
		BLINKING,
		NORMAL_TO_ANGLED,
		ANGLED_TO_NORMAL,
	};

	State()
		: value(IDLE)
		, transition_ticks(0) {}
	State(Value aState)
		: value(aState)
		, transition_ticks(0) {}

	// Allow switch and comparisons.
	constexpr operator Value() const { return value; }
	// Prevent usage: if(fruit)
	explicit operator bool() const = delete;

	// TODO: block new transitions if already transitioning
	void transition_to(Value newState) {
		value = newState;
		transition_ticks = 0;
	}

   private:
	Value value;
};

// Doesn't have position as it will only depend on the canvas
struct Face {
	m5gfx::M5Canvas canvas;
	i32 left_pos_x, left_pos_y, right_pos_x, right_pos_y;
	u16 color;
	float radius;
	FaceExpression expression;
	State state;
	u32 ticks_before_blink;

	Face(m5gfx::M5Canvas &canvas, u16 color, float radius);
	void draw(m5gfx::M5Canvas &canvas, unsigned long tick_count);
	void set_expression(FaceExpression new_expression);
	Size get_params() const;
};
