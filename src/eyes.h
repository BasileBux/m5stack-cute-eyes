#pragma once

#include <M5GFX.h>

#include "types.h"

// #define EYE_WIDTH 46
// #define EYE_HEIGHT 60
// #define EYE_RADIUS 8

#define EYE_WIDTH 66
#define EYE_HEIGHT 90
#define EYE_RADIUS 12

#define BEZIER_CIRCLE 0.488
#define BEZIER_SEGMENTS 0.25

struct Eye {
	i32 pos_x, pos_y;
	i32 width, height;
	float radius, bezier_circle, bezier_segment;
	u16 color;

	Eye(i32 pos_x, i32 pos_y, i32 width, i32 height, float radius, float bezier_circle,
		float bezier_segment, u16 color);

	void draw_normal(m5gfx::M5Canvas canvas) const;
};

void draw_eyes(m5gfx::M5Canvas &canvas, unsigned long tick_count);
