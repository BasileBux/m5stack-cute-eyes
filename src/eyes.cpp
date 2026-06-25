#include "eyes.h"

#include <cmath>

#include "bezier.h"
#include "esp_random.h"

Eye::Eye(i32 pos_x, i32 pos_y, i32 width, i32 height)
	: pos_x(pos_x)
	, pos_y(pos_y)
	, width(width)
	, height(height) {
}

void Eye::draw_normal(m5gfx::M5Canvas &canvas, float radius, u16 color) const {
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

void Eye::draw_down(m5gfx::M5Canvas &canvas, float radius, u16 color, i32 angle) const {
	const i32 diagonal = angle * 2 * 2;
	auto current =
		Bezier::acute_top_left(radius, angle).move_to(pos_x, pos_y).draw(canvas, TFT_WHITE);

	current = Bezier::diagonal(width - (2 * radius), diagonal)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::obtuse_top_right(radius, angle)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::vertical(radius, height - (2 * radius) - diagonal, true)
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

void Eye::draw_up(m5gfx::M5Canvas &canvas, float radius, u16 color, i32 angle) const {
	const i32 diagonal = angle * 2 * 2;
	auto current = Bezier::obtuse_top_left(radius, angle)
					   .move_to(pos_x, pos_y + diagonal)
					   .draw(canvas, TFT_WHITE);

	current = Bezier::diagonal(width - (2 * radius), -diagonal)
				  .move_to(current.x3, current.y3)
				  .draw(canvas, TFT_WHITE);

	current = Bezier::acute_top_right(radius, angle)
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

	current = Bezier::vertical(radius, height - (2 * radius) - diagonal, false)
				  // vertical is top to bottom, so we need to inverse the y position
				  .move_to(current.x3, current.y3 - (height - 2 * radius) + diagonal)
				  .draw(canvas, TFT_WHITE);

	canvas.floodFill(pos_x + width / 2, pos_y + height / 2, TFT_WHITE);
}

Size Face::get_params() const {
	switch (this->expression) {
	case NORMAL: return NormalEye::EYE_SIZE;
	case ANGRY: return NormalEye::EYE_SIZE;
	case SAD: return NormalEye::EYE_SIZE;	   // TODO:
	case WEIRDED: return NormalEye::EYE_SIZE;  // TODO:
	default: return NormalEye::EYE_SIZE;	   // TODO:
	}
}

Face::Face(m5gfx::M5Canvas &canvas, u16 color, float radius) {
	this->canvas = canvas;
	this->color = color;
	this->radius = radius;
	this->expression = NORMAL;
	this->state = State();
	this->ticks_before_blink = esp_random() % BlinkAnimation::MAX_WAIT_TICKS;

	i32 width = this->canvas.width();
	i32 height = this->canvas.height();

	this->left_pos_x = width / 2 - NormalEye::EYE_WIDTH - NormalEye::EYE_DISTANCE / 2;
	this->right_pos_x = this->left_pos_x + NormalEye::EYE_WIDTH + NormalEye::EYE_DISTANCE;

	this->left_pos_y = height / 2 - NormalEye::EYE_HEIGHT / 2;
	this->right_pos_y = this->left_pos_y;
}

float blink_function(float t) {
	float ret = 0.f;
	if (t <= 0.4f) {
		ret = 1 - 2.5f * t;					  // linear decrease from 1 to 0
	} else {								  // t > 0.4f
		ret = 1.f - expf(-8.f * (t - 0.4f));  // exponential increase from 0 to 1
	}
	return ret;
}

// TODO: Fix the artifacts when blinking
void Face::draw(m5gfx::M5Canvas &canvas, unsigned long tick_count) {
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

	i32 angle = AngrySadEye::ANGLE;
	i32 blink_offset = 0;

	if (this->state == State::BLINKING) {
		// reduce the height to simulate blinking
		this->state.transition_ticks++;

		if (this->state.transition_ticks > BlinkAnimation::DURATION) {
			this->state.transition_to(State::IDLE);
		} else {
			float t = (float)this->state.transition_ticks * BlinkAnimation::ANGLE;
			i32 blink_size = (i32)(blink_function(t) * (float)current_height);
			i32 min_blink_size = (i32)(NormalEye::EYE_RADIUS * 2);
			blink_size = std::max(blink_size, min_blink_size);
			blink_offset = current_height - blink_size;
			current_height = blink_size;

			// While blinking in an angled expression, transition to NORMAL while closing
			// and back to the original expression while opening.
			if (this->expression == ANGRY || this->expression == SAD) {
				if (t < 0.2f) {
					angle = AngrySadEye::ANGLE;
				} else if (t <= 0.4f) {
					angle = std::max(BlinkAnimation::MIN_ANGLE,
									 (i32)(AngrySadEye::ANGLE * (1.0f - (t - 0.2f) / 0.2f)));
				} else if (t <= 0.8f) {
					angle = std::max(BlinkAnimation::MIN_ANGLE,
									 (i32)(AngrySadEye::ANGLE * ((t - 0.4f) / 0.4f)));
				} else {
					angle = AngrySadEye::ANGLE;
				}
			}
		}
	}

	if (this->state == State::NORMAL_TO_ANGLED) {
		this->state.transition_ticks++;
		if (this->state.transition_ticks > TransitionAnimation::DURATION) {
			this->state.transition_to(State::IDLE);
		} else {
			angle = (i32)(this->state.transition_ticks * TransitionAnimation::ANGLE);
		}
	} else if (this->state == State::ANGLED_TO_NORMAL) {
		this->state.transition_ticks++;
		if (this->state.transition_ticks > TransitionAnimation::DURATION) {
			this->state.transition_to(State::IDLE);
			this->expression = NORMAL;
		} else {
			angle -= (i32)(this->state.transition_ticks * TransitionAnimation::ANGLE);
		}
	}

	// Shift the starting positions by half the offset so the eyes grow from their center
	i32 left_x = this->left_pos_x - w_offset / 2;
	i32 right_x = this->right_pos_x - w_offset / 2;
	i32 pos_y = this->left_pos_y - h_offset / 2 + y_offset + blink_offset;

	Eye left_eye(left_x, pos_y, current_width, current_height);
	Eye right_eye(right_x, pos_y, current_width, current_height);

	switch (this->expression) {
	case NORMAL:
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	case ANGRY:
		if (angle == 0) {
			left_eye.draw_normal(canvas, this->radius, this->color);
			right_eye.draw_normal(canvas, this->radius, this->color);
		} else {
			left_eye.draw_down(canvas, this->radius, this->color, angle);
			right_eye.draw_up(canvas, this->radius, this->color, angle);
		}
		break;
	case WEIRDED:  // TODO: implement weirded expression
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	case SAD:
		if (angle == 0) {
			left_eye.draw_normal(canvas, this->radius, this->color);
			right_eye.draw_normal(canvas, this->radius, this->color);
		} else {
			left_eye.draw_up(canvas, this->radius, this->color, angle);
			right_eye.draw_down(canvas, this->radius, this->color, angle);
		}
		break;
	default:
		left_eye.draw_normal(canvas, this->radius, this->color);
		right_eye.draw_normal(canvas, this->radius, this->color);
		break;
	}
}

void Face::set_expression(FaceExpression new_expression) {
	switch (new_expression) {
	case NORMAL:
		if (this->expression == ANGRY || this->expression == SAD) {
			this->state.transition_to(State::ANGLED_TO_NORMAL);
		}
		return;	 // Return as we don't want to change the expression immediately, but rather after the transition
	case ANGRY:
	case SAD:
		if (this->expression == NORMAL) {
			this->state.transition_to(State::NORMAL_TO_ANGLED);
		}
		break;
	case WEIRDED:
		// No transition for WEIRDED, just set the expression
		break;
	default: return;  // Invalid expression, do nothing
	}
	this->expression = new_expression;
}
