#pragma once

#include "CGALWrapper.h"
#include "Geometry2.h"
#include "Arrangement2.h"

extern "C"
{
	CGALWRAPPER_API void* Arrangement2_EEK_Create();

	CGALWRAPPER_API void Arrangement2_EEK_Release(void* ptr);

	CGALWRAPPER_API BOOL Arrangement2_EEK_IsValid(void* ptr);

	CGALWRAPPER_API void Arrangement2_EEK_Clear(void* ptr);

	CGALWRAPPER_API BOOL Arrangement2_EEK_IsEmpty(void* ptr);

	CGALWRAPPER_API void Arrangement2_EEK_Assign(void* ptr, void* ptrOther);

	CGALWRAPPER_API void* Arrangement2_EEK_Overlay(void* ptr, void* ptrOther);

	CGALWRAPPER_API int Arrangement2_EEK_VertexCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_IsolatedVerticesCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_VerticesAtInfinityCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_HalfEdgeCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_FaceCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_EdgeCount(void* ptr);

	CGALWRAPPER_API int Arrangement2_EEK_UnboundedFaceCount(void* ptr);

	CGALWRAPPER_API void Arrangement2_EEK_GetPoints(void* ptr, Point2d* points, int startIndex, int count);

	CGALWRAPPER_API void Arrangement2_EEK_GetSegments(void* ptr, Segment2d* segments, int startIndex, int count);

	CGALWRAPPER_API void Arrangement2_EEK_GetVertices(void* ptr, ArrVertex2* vertices, int startIndex, int count);

	CGALWRAPPER_API void Arrangement2_EEK_GetHalfEdges(void* ptr, ArrHalfEdge2* edges, int startIndex, int count);

	CGALWRAPPER_API void Arrangement2_EEK_GetFaces(void* ptr, ArrFace2* faces, int startIndex, int count);

	CGALWRAPPER_API void Arrangement2_EEK_CreateLocator(void* ptr, ARR_LOCATOR type);

	CGALWRAPPER_API void Arrangement2_EEK_ReleaseLocator(void* ptr);

	CGALWRAPPER_API BOOL Arrangement2_EEK_PointQuery(void* ptr, Point2d point, ArrQuery& result);

	CGALWRAPPER_API BOOL Arrangement2_EEK_BatchedPointQuery(void* ptr, Point2d* points, ArrQuery* results, int startIndex, int count);

	CGALWRAPPER_API BOOL Arrangement2_EEK_RayQuery(void* ptr, Point2d point, BOOL up, ArrQuery& result);

	CGALWRAPPER_API BOOL Arrangement2_EEK_IntersectsSegment(void* ptr, Segment2d segment);

	CGALWRAPPER_API void Arrangement2_EEK_InsertPoint(void* ptr, Point2d point);

	CGALWRAPPER_API void Arrangement2_EEK_InsertPolygon(void* ptr, void* polyPtr, BOOL nonItersecting);

	CGALWRAPPER_API void Arrangement2_EEK_InsertSegment(void* ptr, Segment2d segment, BOOL nonItersecting);

	CGALWRAPPER_API void Arrangement2_EEK_InsertSegments(void* ptr, Segment2d* segments, int startIndex, int count, BOOL nonItersecting);

	CGALWRAPPER_API BOOL Arrangement2_EEK_RemoveVertexByIndex(void* ptr, int index);

	CGALWRAPPER_API BOOL Arrangement2_EEK_RemoveVertexByPoint(void* ptr, Point2d point);

	CGALWRAPPER_API BOOL Arrangement2_EEK_RemoveEdgeByIndex(void* ptr, int index);

	CGALWRAPPER_API BOOL Arrangement2_EEK_RemoveEdgeBySegment(void* ptr, Segment2d segment);

}
