#pragma once

#include <M5GFX.h>

#include "types.h"

// 4 points bezier curve
struct Bezier {
	i32 x0, y0;
	i32 x1, y1;
	i32 x2, y2;
	i32 x3, y3;

	Bezier &draw_at(m5gfx::M5Canvas &canvas, i32 x, i32 y, u16 color);
	Bezier &draw(m5gfx::M5Canvas &canvas, u16 color);
	Bezier &move_to(i32 x, i32 y);

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_top_left(float radius, float circle) {
		return Bezier{
			.x0 = 0,
			.y0 = (i32)radius,
			.x1 = 0,
			.y1 = (i32)(circle * radius),
			.x2 = (i32)(circle * radius),
			.y2 = 0,
			.x3 = (i32)radius,
			.y3 = 0,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_top_right(float radius, float circle) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = (i32)(circle * radius),
			.y1 = 0,
			.x2 = (i32)radius,
			.y2 = (i32)(circle * radius),
			.x3 = (i32)radius,
			.y3 = (i32)radius,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_bottom_left(float radius, float circle) {
		return Bezier{
			.x0 = (i32)radius,
			.y0 = (i32)radius,
			.x1 = (i32)(circle * radius),
			.y1 = (i32)radius,
			.x2 = 0,
			.y2 = (i32)(circle * radius),
			.x3 = 0,
			.y3 = 0,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_bottom_right(float radius, float circle) {
		return Bezier{
			.x0 = (i32)radius,
			.y0 = 0,
			.x1 = (i32)radius,
			.y1 = (i32)(circle * radius),
			.x2 = (i32)(circle * radius),
			.y2 = (i32)radius,
			.x3 = 0,
			.y3 = (i32)radius,
		};
	}

	// The line is drawn from left to right
	static Bezier horizontal(float radius, float segment, i32 width, bool up) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = 0 + (i32)radius,
			.y1 = (up ? -1 : 1) * (i32)(segment * radius),
			.x2 = width - (i32)radius,
			.y2 = (up ? -1 : 1) * (i32)(segment * radius),
			.x3 = width,
			.y3 = 0,
		};
	}

	// The line is drawn from top to bottom
	static Bezier vertical(float radius, float segment, i32 height, bool right) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = (right ? 1 : -1) * (i32)(segment * radius),
			.y1 = (i32)radius,
			.x2 = (right ? 1 : -1) * (i32)(segment * radius),
			.y2 = height - (i32)radius,
			.x3 = 0,
			.y3 = height,
		};
	}
};
