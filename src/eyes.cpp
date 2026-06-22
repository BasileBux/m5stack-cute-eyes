#include "eyes.h"

#include <cmath>

#include "bezier.h"

Eye::Eye(i32 pos_x, i32 pos_y, i32 width, i32 height)
	: pos_x(pos_x)
	, pos_y(pos_y)
	, width(width)
	, height(height) {
}

void Eye::clear(m5gfx::M5Canvas &canvas, float radius) const {
	i32 width_d = MAX_EYE_WIDTH - this->width;
	i32 height_d = MAX_EYE_HEIGHT - this->height;
	canvas.fillRect(this->pos_x - width_d / 2 - (i32)radius,
					this->pos_y - height_d / 2 - (i32)radius, MAX_EYE_WIDTH + (i32)radius * 2,
					MAX_EYE_HEIGHT + (i32)radius * 2, TFT_BLACK);
}

void Eye::draw_normal(m5gfx::M5Canvas &canvas, float radius, u16 color) const {
	this->clear(canvas, radius);

	auto current =
		Bezier::squared_top_left(radius).move_to(this->pos_x, this->pos_y).draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(radius, this->width - (2 * radius), true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current =
		Bezier::squared_top_right(radius).move_to(current.x3, current.y3).draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, this->height - (2 * radius), true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_right(radius)
				  // slight offset as ref point is top left corner of the bounding box of the curve
				  .move_to(current.x3 - radius, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(radius, this->width - (2 * radius), false)
				  // horizontal is left to right, so we need to inverse the x position
				  .move_to(current.x3 - (this->width - 2 * radius), current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_left(radius)
				  .move_to(current.x0 - radius,
						   current.y0 - radius)	 // horizontal is left to right
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, this->height - (2 * radius), false)
				  // vertical is top to bottom, so we need to inverse the y position
				  .move_to(current.x3, current.y3 - (this->height - 2 * radius))
				  .draw(canvas, TFT_WHITE);

	canvas.floodFill(this->pos_x + this->width / 2, this->pos_y + this->height / 2, TFT_WHITE);
}

void Eye::draw_down(m5gfx::M5Canvas &canvas, float radius, u16 color) const {
	const i32 ANGLE = 6;
	const i32 DIAGONAL = radius * 2;

	this->clear(canvas, radius);

	auto current =
		Bezier::acute_top_left(radius, ANGLE).move_to(pos_x, pos_y).draw(canvas, TFT_WHITE);

	current = Bezier::diagonal(width - (2 * radius), DIAGONAL)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::obtuse_top_right(radius, ANGLE)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, height - (2 * radius) - DIAGONAL, true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_right(radius)
				  // slight offset as ref point is top left corner of the bounding box of the curve
				  .move_to(current.x3 - radius, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(radius, width - (2 * radius), false)
				  // horizontal is left to right, so we need to inverse the x position
				  .move_to(current.x3 - (width - 2 * radius), current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_left(radius)
				  .move_to(current.x0 - radius,
						   current.y0 - radius)	 // horizontal is left to right
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, height - (2 * radius), false)
				  // vertical is top to bottom, so we need to inverse the y position
				  .move_to(current.x3, current.y3 - (height - 2 * radius))
				  .draw(canvas, TFT_WHITE);

	canvas.floodFill(pos_x + width / 2, pos_y + height / 2, TFT_WHITE);
}

void Eye::draw_up(m5gfx::M5Canvas &canvas, float radius, u16 color) const {
	const i32 ANGLE = 6;
	const i32 DIAGONAL = radius * 2;

	this->clear(canvas, radius);

	auto current = Bezier::obtuse_top_left(radius, ANGLE)
					   .move_to(pos_x, pos_y + DIAGONAL)
					   .draw(canvas, TFT_WHITE);

	current = Bezier::diagonal(width - (2 * radius), -DIAGONAL)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::acute_top_right(radius, ANGLE)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, height - (2 * radius), true)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_right(radius)
				  // slight offset as ref point is top left corner of the bounding box of the curve
				  .move_to(current.x3 - radius, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::horizontal(radius, width - (2 * radius), false)
				  // horizontal is left to right, so we need to inverse the x position
				  .move_to(current.x3 - (width - 2 * radius), current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::squared_bottom_left(radius)
				  .move_to(current.x0 - radius,
						   current.y0 - radius)	 // horizontal is left to right
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, height - (2 * radius) - DIAGONAL, false)
				  // vertical is top to bottom, so we need to inverse the y position
				  .move_to(current.x3, current.y3 - (height - 2 * radius) + DIAGONAL)
				  .draw(canvas, TFT_WHITE);

	canvas.floodFill(pos_x + width / 2, pos_y + height / 2, TFT_WHITE);
}

Size Face::get_params() const {
	switch (this->expression) {
	case NORMAL: return NormalEye::EYE_SIZE;
	case ANGRY: return AngrySadEye::EYE_SIZE;  // TODO:
	case SAD: return AngrySadEye::EYE_SIZE;	   // TODO:
	case WEIRDED: return NormalEye::EYE_SIZE;  // TODO:
	default: return NormalEye::EYE_SIZE;	   // TODO:
	}
}

Face::Face(m5gfx::M5Canvas &canvas, u16 color, float radius) {
	this->canvas = canvas;
	this->color = color;
	this->radius = radius;
	this->expression = NORMAL;

	i32 width = this->canvas.width();
	i32 height = this->canvas.height();

	this->left_pos_x = width / 2 - NormalEye::EYE_WIDTH - NormalEye::EYE_DISTANCE / 2;
	this->right_pos_x = this->left_pos_x + NormalEye::EYE_WIDTH + NormalEye::EYE_DISTANCE;

	this->left_pos_y = height / 2 - NormalEye::EYE_HEIGHT / 2 - NormalEye::Y_OFFSET;
	this->right_pos_y = this->left_pos_y;
}

void Face::draw(m5gfx::M5Canvas &canvas, unsigned long tick_count) const {
	float w_angle = (float)tick_count * IdleAnimation::WIDTH_ANGLE;
	float h_angle = (float)tick_count * IdleAnimation::HEIGHT_ANGLE;
	float y_angle = (float)tick_count * IdleAnimation::Y_ANGLE;

	// Scale by delta constants to get the current animation offsets
	i32 w_offset = (i32)(std::sin(w_angle) * IdleAnimation::WIDTH_DELTA);
	i32 h_offset = (i32)(std::sin(h_angle) * IdleAnimation::HEIGHT_DELTA);
	i32 y_offset = (i32)(std::sin(y_angle) * IdleAnimation::Y_DELTA);

	Size eye_size = this->get_params();
	i32 current_width = eye_size.width + w_offset;
	i32 current_height = eye_size.height + h_offset;

	// Shift the starting positions by half the offset so the eyes grow from their center
	i32 left_x = this->left_pos_x - w_offset / 2;
	i32 right_x = this->right_pos_x - w_offset / 2;
	i32 pos_y = this->left_pos_y - h_offset / 2 + y_offset;

	Eye left_eye(left_x, pos_y, current_width, current_height);
	Eye right_eye(right_x, pos_y, current_width, current_height);

	switch (this->expression) {
	case NORMAL:
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	case ANGRY:
		left_eye.draw_down(canvas, this->radius, this->color);
		right_eye.draw_up(canvas, this->radius, this->color);
		break;
	case WEIRDED:  // TODO: implement weirded expression
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	case SAD:
		left_eye.draw_up(canvas, this->radius, this->color);
		right_eye.draw_down(canvas, this->radius, this->color);
		break;
	default:
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	}
}
