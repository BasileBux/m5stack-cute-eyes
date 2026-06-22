#pragma once

#include <M5GFX.h>

#include "types.h"

struct Size {
	i32 width, height;
};

// TODO: For animations reasons, we might need to make all eyes the same size
namespace NormalEye {
	const u32 EYE_WIDTH = 66;
	const u32 EYE_HEIGHT = 95;
	const Size EYE_SIZE = { EYE_WIDTH, EYE_HEIGHT };
	const u32 EYE_RADIUS = 12;
	const u32 EYE_DISTANCE = 30;
	const u32 Y_OFFSET = 20;
}  // namespace NormalEye

namespace AngrySadEye {
	const u32 EYE_HEIGHT = NormalEye::EYE_HEIGHT;
	const Size EYE_SIZE = { NormalEye::EYE_WIDTH, EYE_HEIGHT };
}  // namespace AngrySadEye

namespace IdleAnimation {
	const u8 WIDTH_DELTA = 1;
	const u32 WIDTH_DURATION = 30;
	const float WIDTH_ANGLE = 2.0f * M_PI / (float)WIDTH_DURATION;

	const u8 HEIGHT_DELTA = 2;
	const u32 HEIGHT_DURATION = 20;
	const float HEIGHT_ANGLE = 2.0f * M_PI / (float)HEIGHT_DURATION;

	const u8 Y_DELTA = 3;
	const u32 Y_DURATION = 40;
	const float Y_ANGLE = 2.0f * M_PI / (float)Y_DURATION;
}  // namespace IdleAnimation

const i32 MAX_EYE_WIDTH =
	NormalEye::EYE_WIDTH + IdleAnimation::WIDTH_DELTA + IdleAnimation::WIDTH_DELTA;
const i32 MAX_EYE_HEIGHT =
	AngrySadEye::EYE_HEIGHT + IdleAnimation::HEIGHT_DELTA * 2 + IdleAnimation::Y_DELTA * 2;

struct Eye {
	i32 pos_x, pos_y;
	i32 width, height;
	Eye(i32 pos_x, i32 pos_y, i32 width, i32 height);

	void draw_normal(m5gfx::M5Canvas &canvas, float radius, u16 color) const;
	void draw_down(m5gfx::M5Canvas &canvas, float radius, u16 color) const;
	void draw_up(m5gfx::M5Canvas &canvas, float radius, u16 color) const;
	void clear(m5gfx::M5Canvas &canvas, float radius) const;
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

// Doesn't have position as it will only depend on the canvas
struct Face {
	// Eye left_eye, right_eye; // TODO:
	m5gfx::M5Canvas canvas;
	i32 left_pos_x, left_pos_y, right_pos_x, right_pos_y;
	u16 color;
	float radius;
	FaceExpression expression;

	Face(m5gfx::M5Canvas &canvas, u16 color, float radius);
	void draw(m5gfx::M5Canvas &canvas, unsigned long tick_count) const;
	Size get_params() const;
};
