#pragma once

#include <M5GFX.h>

#include "../types.h"
#include "constants.h"

struct Eye {
	i32 pos_x, pos_y;
	i32 width, height;
	Eye(i32 pos_x, i32 pos_y, i32 width, i32 height);

	void draw_normal(m5gfx::M5Canvas &canvas, float radius, u16 color, bool blinking) const;
	void draw_small(m5gfx::M5Canvas &canvas, float radius, u16 color, bool blinking) const;
	void draw_down(m5gfx::M5Canvas &canvas, float radius, u16 color, bool blinking,
				   i32 angle = AngledEye::ANGLE) const;
	void draw_up(m5gfx::M5Canvas &canvas, float radius, u16 color, bool blinking,
				 i32 angle = AngledEye::ANGLE) const;
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
