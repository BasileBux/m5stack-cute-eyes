#include "bezier.h"

Bezier &Bezier::draw(m5gfx::M5Canvas &canvas, u16 color) {
	canvas.drawBezier(x0, y0, x1, y1, x2, y2, x3, y3, color);
	return *this;
}

Bezier &Bezier::draw_at(m5gfx::M5Canvas &canvas, i32 x, i32 y, u16 color) {
	canvas.drawBezier(x + x0, y + y0, x + x1, y + y1, x + x2, y + y2, x + x3, y + y3, color);
	return *this;
}

Bezier &Bezier::move_to(i32 x, i32 y) {
	this->x0 += x;
	this->y0 += y;
	this->x1 += x;
	this->y1 += y;
	this->x2 += x;
	this->y2 += y;
	this->x3 += x;
	this->y3 += y;
	return *this;
}
