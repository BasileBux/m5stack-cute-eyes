#pragma once

#include <cmath>

#include "../types.h"

namespace BezierConstants {
	constexpr float SQUARE_CORNER_CIRCLE = 0.488;
	constexpr float STRAIGHT_SEGMENT = 0.25;
	constexpr float ANGLED_CORNER_CIRCLE = 0.06;
};	// namespace BezierConstants

struct Size {
	i32 width, height;
};

namespace EyeGeometry {
	constexpr u32 EYE_WIDTH = 66;
	constexpr u32 EYE_HEIGHT = 86;

	constexpr Size EYE_SIZE = { EYE_WIDTH, EYE_HEIGHT };
	constexpr u32 EYE_RADIUS = 12;
	constexpr u32 EYE_DISTANCE = 30;
}  // namespace EyeGeometry

namespace AngledEye {
	constexpr i32 ANGLE = 6;
	constexpr i32 DIAGONAL = ANGLE * 2 * 2;
}  // namespace AngledEye

namespace SmallEye {
	constexpr float SCALE = 0.75f;
};

namespace TransitionAnimation {
	constexpr u32 DURATION = 8;	 // ticks
	constexpr float ANGLE = (float)AngledEye::ANGLE / (float)DURATION;
}  // namespace TransitionAnimation

namespace IdleAnimation {
	constexpr u8 WIDTH_DELTA = 1;
	constexpr u32 WIDTH_DURATION = 90;	// ticks
	constexpr float WIDTH_ANGLE = 2.0f * M_PI / (float)WIDTH_DURATION;

	constexpr u8 HEIGHT_DELTA = 2;
	constexpr u32 HEIGHT_DURATION = 60;	 // ticks
	constexpr float HEIGHT_ANGLE = 2.0f * M_PI / (float)HEIGHT_DURATION;

	constexpr u8 Y_DELTA = 3;
	constexpr u32 Y_DURATION = 120;	 // ticks
	constexpr float Y_ANGLE = 2.0f * M_PI / (float)Y_DURATION;
}  // namespace IdleAnimation

namespace BlinkAnimation {
	constexpr u32 MAX_WAIT_TICKS = 900;
	constexpr i32 MIN_ANGLE = 2;
	constexpr u32 DURATION = 20;  // ticks
	constexpr float ANGLE = 1.f / (float)DURATION;
}  // namespace BlinkAnimation

constexpr i32 MAX_EYE_WIDTH =
	EyeGeometry::EYE_WIDTH + IdleAnimation::WIDTH_DELTA + IdleAnimation::WIDTH_DELTA;
constexpr i32 MAX_EYE_HEIGHT =
	EyeGeometry::EYE_HEIGHT + IdleAnimation::HEIGHT_DELTA * 2 + IdleAnimation::Y_DELTA * 2;
