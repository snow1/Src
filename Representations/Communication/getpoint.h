#pragma once
#include "Tools/Streams/Enum.h"
#include "Tools/Math/Eigen.h"
#include "Tools/Streams/AutoStreamable.h"
#include <vector>
STREAMABLE(GetPoints,
{
	Vector2f keeperNeedpointa ,
	//(Vector2f) keeperNeedpoint,
	(Vector2f) oneNeedpoint = Vector2f(static_cast<float>(-4400), static_cast<float>(0)),
	(Vector2f) fourNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(1100)),
	(Vector2f) fiveNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(-1100)),//Õâ¸öºÜÆæ¹Ö
});
