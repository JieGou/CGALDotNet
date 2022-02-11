#pragma once
#include "../CGALWrapper.h"
#include "../Geometry/Geometry2.h"
#include <CGAL/enum.h>

extern "C"
{

	CGALWRAPPER_API void* Point2_EEK_Create();

	CGALWRAPPER_API void* Point2_EEK_CreateFromPoint(const Point2d& point);

	CGALWRAPPER_API void Point2_EEK_Release(void* ptr);

	CGALWRAPPER_API Point2d Point2_EEK_GetPoint(void* ptr);

	CGALWRAPPER_API void Point2_EEK_SetPoint(void* ptr, const Point2d& point);

}
