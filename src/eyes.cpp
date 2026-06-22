#include "eyes.h"

#include <cmath>

#include "bezier.h"

Eye::Eye(i32 pos_x, i32 pos_y, i32 width, i32 height, float radius, float bezier_circle,
		 float bezier_segment, u16 color)
	: pos_x(pos_x)
	, pos_y(pos_y)
	, width(width)
	, height(height)
	, radius(radius)
	, bezier_circle(bezier_circle)
	, bezier_segment(bezier_segment)
	, color(color) {
}

void Eye::draw_normal(m5gfx::M5Canvas canvas) const {
	// RED for debug but should be TFT_BLACK and a bit bigger than the current size
	canvas.fillRect(this->pos_x - this->radius, this->pos_y - this->radius,
					this->width + this->radius * 2, this->height + this->radius * 2, TFT_BLACK);

	auto current = Bezier::squared_top_left(this->radius, this->bezier_circle)
					   .move_to(this->pos_x, this->pos_y)
					   .draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(this->radius, this->bezier_segment,
								 this->width - (2 * this->radius), true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_top_right(this->radius, this->bezier_circle)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(this->radius, this->bezier_segment,
							   this->height - (2 * this->radius), true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_right(this->radius, this->bezier_circle)
				  // slight offset as ref point is top left corner of the bounding box of the curve
				  .move_to(current.x3 - this->radius, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(this->radius, this->bezier_segment,
								 this->width - (2 * this->radius), false)
				  // horizontal is left to right, so we need to inverse the x position
				  .move_to(current.x3 - (this->width - 2 * this->radius), current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_left(this->radius, this->bezier_circle)
				  .move_to(current.x0 - this->radius,
						   current.y0 - this->radius)  // horizontal is left to right
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(this->radius, this->bezier_segment,
							   this->height - (2 * this->radius), false)
				  // vertical is top to bottom, so we need to inverse the y position
				  .move_to(current.x3, current.y3 - (this->height - 2 * this->radius))
				  .draw(canvas, TFT_WHITE);

	canvas.floodFill(this->pos_x + this->width / 2, this->pos_y + this->height / 2, TFT_WHITE);
}

const u8 WIDTH_DELTA = 1;
const u32 WIDTH_DURATION = 30;
const float WIDTH_ANGLE = 2.0f * M_PI / (float)WIDTH_DURATION;

const u8 HEIGHT_DELTA = 2;
const u32 HEIGHT_DURATION = 20;
const float HEIGHT_ANGLE = 2.0f * M_PI / (float)HEIGHT_DURATION;

const u8 Y_DELTA = 4;
const u32 Y_DURATION = 30;
const float Y_ANGLE = 2.0f * M_PI / (float)Y_DURATION;

void draw_eyes(m5gfx::M5Canvas &canvas, unsigned long tick_count) {
	float w_angle = (float)tick_count * WIDTH_ANGLE;
	float h_angle = (float)tick_count * HEIGHT_ANGLE;
	float y_angle = (float)tick_count * Y_ANGLE;

	// Scale by delta constants to get the current animation offsets
	i32 w_offset = (i32)(std::sin(w_angle) * (float)WIDTH_DELTA);
	i32 h_offset = (i32)(std::sin(h_angle) * (float)HEIGHT_DELTA);
	i32 y_offset = (i32)(std::sin(y_angle) * (float)Y_DELTA);

	i32 current_width = EYE_WIDTH + w_offset;
	i32 current_height = EYE_HEIGHT + h_offset;

	// Shift the starting positions by half the offset so the eyes grow from their center
	i32 left_x = 80 - w_offset / 2;
	i32 right_x = 80 + EYE_WIDTH + 20 - w_offset / 2;
	i32 pos_y = 50 - h_offset / 2 + y_offset;

	Eye left_eye(left_x, pos_y, current_width, current_height, EYE_RADIUS, BEZIER_CIRCLE,
				 BEZIER_SEGMENTS, TFT_WHITE);
	Eye right_eye(right_x, pos_y, current_width, current_height, EYE_RADIUS, BEZIER_CIRCLE,
				  BEZIER_SEGMENTS, TFT_WHITE);

	left_eye.draw_normal(canvas);
	right_eye.draw_normal(canvas);
}
