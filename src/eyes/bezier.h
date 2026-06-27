#pragma once

#include <M5GFX.h>

#include "../types.h"
#include "constants.h"

using namespace BezierConstants;

// 4 points bezier curve
struct Bezier {
	i32 x0, y0;
	i32 x1, y1;
	i32 x2, y2;
	i32 x3, y3;

	Bezier &draw_at(m5gfx::M5Canvas &canvas, i32 x, i32 y, u16 color);
	Bezier &draw(m5gfx::M5Canvas &canvas, u16 color);
	Bezier &move_to(i32 x, i32 y);

	// -- Angled corners --

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier obtuse_top_left(float radius, i32 angle) {
		return Bezier{
			.x0 = 0,
			.y0 = (i32)radius,

			.x1 = (i32)(radius * ANGLED_CORNER_CIRCLE),
			.y1 = (i32)radius - angle,

			.x2 = (i32)(radius * ANGLED_CORNER_CIRCLE * 2),
			.y2 = (i32)radius - angle + (i32)(radius * ANGLED_CORNER_CIRCLE),

			.x3 = (i32)radius,
			.y3 = 0,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier obtuse_top_right(float radius, i32 angle) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,

			.x1 = (i32)(radius - radius * ANGLED_CORNER_CIRCLE * 2),
			.y1 = (i32)radius - angle + +(i32)(radius * ANGLED_CORNER_CIRCLE),

			.x2 = (i32)(radius - radius * ANGLED_CORNER_CIRCLE),
			.y2 = (i32)radius - angle,

			.x3 = (i32)radius,
			.y3 = (i32)radius,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier acute_top_left(float radius, i32 angle) {
		return Bezier{
			.x0 = 0,
			.y0 = (i32)radius,

			.x1 = 0,
			.y1 = -angle,

			.x2 = (i32)(radius * ANGLED_CORNER_CIRCLE),
			.y2 = -angle - (i32)(radius * ANGLED_CORNER_CIRCLE),

			.x3 = (i32)radius,
			.y3 = 0,
		};
	}

	static Bezier acute_top_right(float radius, i32 angle) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,

			.x1 = (i32)(radius - radius * ANGLED_CORNER_CIRCLE),
			.y1 = -angle - (i32)(radius * ANGLED_CORNER_CIRCLE),

			.x2 = (i32)radius,
			.y2 = -angle,

			.x3 = (i32)radius,
			.y3 = (i32)radius,
		};
	}

	// -- Normal squared --

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_top_left(float radius) {
		return Bezier{
			.x0 = 0,
			.y0 = (i32)radius,
			.x1 = 0,
			.y1 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.x2 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.y2 = 0,
			.x3 = (i32)radius,
			.y3 = 0,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_top_right(float radius) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.y1 = 0,
			.x2 = (i32)radius,
			.y2 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.x3 = (i32)radius,
			.y3 = (i32)radius,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_bottom_left(float radius) {
		return Bezier{
			.x0 = (i32)radius,
			.y0 = (i32)radius,
			.x1 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.y1 = (i32)radius,
			.x2 = 0,
			.y2 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.x3 = 0,
			.y3 = 0,
		};
	}

	// Reference point is the top left corner of the bounding box of the curve.
	// The curve is drawn clockwise
	static Bezier squared_bottom_right(float radius) {
		return Bezier{
			.x0 = (i32)radius,
			.y0 = 0,
			.x1 = (i32)radius,
			.y1 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.x2 = (i32)(SQUARE_CORNER_CIRCLE * radius),
			.y2 = (i32)radius,
			.x3 = 0,
			.y3 = (i32)radius,
		};
	}

	// -- Straight segments --

	// The line is drawn from left to right. Smoothness is often the same as the radius of the corners.
	static Bezier horizontal(float smoothness, i32 width, bool up) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = 0 + (i32)smoothness,
			.y1 = (up ? -1 : 1) * (i32)(STRAIGHT_SEGMENT * smoothness),
			.x2 = width - (i32)smoothness,
			.y2 = (up ? -1 : 1) * (i32)(STRAIGHT_SEGMENT * smoothness),
			.x3 = width,
			.y3 = 0,
		};
	}

	// The line is drawn from top to bottom. Smoothness is often the same as the radius of the corners.
	static Bezier vertical(float smoothness, i32 height, bool right) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = (right ? 1 : -1) * (i32)(STRAIGHT_SEGMENT * smoothness),
			.y1 = (i32)smoothness,
			.x2 = (right ? 1 : -1) * (i32)(STRAIGHT_SEGMENT * smoothness),
			.y2 = height - (i32)smoothness,
			.x3 = 0,
			.y3 = height,
		};
	}

	static Bezier diagonal(i32 width, i32 height) {
		return Bezier{
			.x0 = 0,
			.y0 = 0,
			.x1 = 0,
			.y1 = 0,
			.x2 = width,
			.y2 = height,
			.x3 = width,
			.y3 = height,
		};
	}
};
