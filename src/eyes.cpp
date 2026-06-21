#include "eyes.h"

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
					this->width + this->radius, this->height + this->radius, TFT_BLACK);

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


void draw_eyes(m5gfx::M5Canvas &canvas) {
	Eye left_eye(80, 50, EYE_WIDTH, EYE_HEIGHT, EYE_RADIUS, BEZIER_CIRCLE, BEZIER_SEGMENTS,
				 TFT_WHITE);
	Eye right_eye(80 + EYE_WIDTH + 20, 50, EYE_WIDTH, EYE_HEIGHT, EYE_RADIUS, BEZIER_CIRCLE,
				  BEZIER_SEGMENTS, TFT_WHITE);
	left_eye.draw_normal(canvas);
	right_eye.draw_normal(canvas);
}
