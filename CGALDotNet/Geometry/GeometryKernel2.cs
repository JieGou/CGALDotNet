﻿using System;
using System.Collections.Generic;
using System.Text;

using CGALDotNetGeometry.Numerics;

namespace CGALDotNet.Geometry
{
    internal abstract class GeometryKernel2 : CGALObjectKernel
    {

        //Point2
        internal abstract IntPtr Point2_Create();

        internal abstract IntPtr Point2_CreateFromPoint(Point2d point);

	    internal abstract void Point2_Release(IntPtr ptr);

        internal abstract double Point2_GetX(IntPtr ptr);

        internal abstract double Point2_GetY(IntPtr ptr);

        internal abstract Point2d Point2_GetPoint(IntPtr ptr);

        internal abstract void Point2_SetX(IntPtr ptr, double x);

        internal abstract void Point2_SetY(IntPtr ptr, double y);

        internal abstract void Point2_SetPoint(IntPtr ptr, Point2d point);

        //Vector2

        internal abstract IntPtr Vector2_Create();

        internal abstract IntPtr Vector2_CreateFromVector( Vector2d vector);

	    internal abstract void Vector2_Release(IntPtr ptr);

        internal abstract double Vector2_GetX(IntPtr ptr);

        internal abstract double Vector2_GetY(IntPtr ptr);

        internal abstract Vector2d Vector2_GetVector(IntPtr ptr);

        internal abstract void Vector2_SetX(IntPtr ptr, double x);

        internal abstract void Vector2_SetY(IntPtr ptr, double y);

        internal abstract void Vector2_SetVector(IntPtr ptr,  Vector2d vector);

	    internal abstract double Vector2_SqrLength(IntPtr ptr);

        internal abstract IntPtr Vector2_Perpendicular(IntPtr ptr, ORIENTATION orientation);

        internal abstract void Vector2_Normalize(IntPtr ptr);

        //HPoint2

        internal abstract IntPtr HPoint2_Create();

        internal abstract IntPtr HPoint2_CreateFromPoint( HPoint2d point);

	    internal abstract void HPoint2_Release(IntPtr ptr);

        internal abstract double HPoint2_GetX(IntPtr ptr);

        internal abstract double HPoint2_GetY(IntPtr ptr);

        internal abstract double HPoint2_GetW(IntPtr ptr);

        internal abstract HPoint2d HPoint2_GetPoint(IntPtr ptr);

        internal abstract void HPoint2_SetX(IntPtr ptr, double x);

        internal abstract void HPoint2_SetY(IntPtr ptr, double y);

        internal abstract void HPoint2_SetW(IntPtr ptr, double y);

        internal abstract void HPoint2_SetPoint(IntPtr ptr,  HPoint2d point);

        //Line2
        internal abstract IntPtr Line2_Create(double a, double b, double c);

        internal abstract IntPtr CreateFromPoints(Point2d p1, Point2d p2);

	    internal abstract IntPtr CreateFromPointVector(Point2d p, Vector2d v);

        internal abstract void Line2_Release(IntPtr ptr);

        internal abstract double Line2_GetA(IntPtr ptr);

        internal abstract double Line2_GetB(IntPtr ptr);

        internal abstract double Line2_GetC(IntPtr ptr);

        internal abstract bool Line2_IsDegenerate(IntPtr ptr);

        internal abstract bool Line2_IsHorizontal(IntPtr ptr);

        internal abstract bool Line2_IsVertical(IntPtr ptr);

        internal abstract bool Line2_HasOn(IntPtr linePtr, Point2d point);

        internal abstract bool Line2_HasOnNegativeSide(IntPtr linePtr, Point2d point);

        internal abstract bool Line2_HasOnPositiveSide(IntPtr linePtr, Point2d point);

        internal abstract IntPtr Line2_Opposite(IntPtr ptr);

        internal abstract IntPtr Line2_Perpendicular(IntPtr ptr, Point2d point);

        internal abstract double Line2_X_On_Y(IntPtr ptr, double y);

        internal abstract double Line2_Y_On_X(IntPtr ptr, double x);

        internal abstract Vector2d Line2_Vector(IntPtr ptr);

        internal abstract IntPtr Line2_Transform(IntPtr ptr, Point2d translation, double rotation, double scale);

        //Ray2
        internal abstract IntPtr Ray2_Create(Point2d position, Vector2d direction);

        internal abstract void Ray2_Release(IntPtr ptr);

        internal abstract bool Ray2_IsDegenerate(IntPtr ptr);

        internal abstract bool Ray2_IsHorizontal(IntPtr ptr);

        internal abstract bool Ray2_IsVertical(IntPtr ptr);

        internal abstract bool Ray2_HasOn(IntPtr rayPtr,  Point2d point);

	    internal abstract Point2d Ray2_Source(IntPtr ptr);

        internal abstract Vector2d Ray2_Vector(IntPtr ptr);

        internal abstract IntPtr Ray2_Opposite(IntPtr ptr);

        internal abstract IntPtr Ray2_Line(IntPtr ptr);

        internal abstract IntPtr Ray2_Transform(IntPtr ptr,  Point2d translation, double rotation, double scale);

        //Segment2
        internal abstract IntPtr Segment2_Create(Point2d a, Point2d b);

        internal abstract void Segment2_Release(IntPtr ptr);

        internal abstract Point2d Segment2_GetVertex(IntPtr ptr, int i);

        internal abstract void Segment2_SetVertex(IntPtr ptr, int i,  Point2d point);

	    internal abstract Point2d Segment2_Min(IntPtr ptr);

        internal abstract Point2d Segment2_Max(IntPtr ptr);

        internal abstract bool Segment2_IsDegenerate(IntPtr ptr);

        internal abstract bool Segment2_IsHorizontal(IntPtr ptr);

        internal abstract bool Segment2_IsVertical(IntPtr ptr);

        internal abstract bool Segment2_HasOn(IntPtr segPtr,  Point2d point);

	    internal abstract Vector2d Segment2_Vector(IntPtr ptr);

        internal abstract IntPtr Segment2_Line(IntPtr ptr);

        internal abstract double Segment2_SqrLength(IntPtr ptr);

        internal abstract IntPtr Segment2_Transform(IntPtr ptr,  Point2d translation, double rotation, double scale);

        //Triangle2
        internal abstract IntPtr Triangle2_Create(Point2d a, Point2d b, Point2d c);

        internal abstract void Triangle2_Release(IntPtr ptr);

        internal abstract Point2d Triangle2_GetVertex(IntPtr ptr, int i);

        internal abstract void Triangle2_SetVertex(IntPtr ptr, int i,  Point2d point);

	    internal abstract double Triangle2_Area(IntPtr ptr);

        internal abstract BOUNDED_SIDE Triangle2_BoundedSide(IntPtr ptr,  Point2d point);

	    internal abstract ORIENTED_SIDE Triangle2_OrientedSide(IntPtr ptr,  Point2d point);

	    internal abstract ORIENTATION Triangle2_Orientation(IntPtr ptr);

        internal abstract bool Triangle2_IsDegenerate(IntPtr ptr);

        internal abstract IntPtr Triangle2_Transform(IntPtr ptr,  Point2d translation, double rotation, double scale);

        //IsoRectangle2
        internal abstract IntPtr IsoRectangle2_Create(Point2d min, Point2d max);

        internal abstract void IsoRectangle2_Release(IntPtr ptr);

        internal abstract Point2d IsoRectangle2_GetMin(IntPtr ptr);

        internal abstract void IsoRectangle2_SetMin(IntPtr ptr, Point2d point);

        internal abstract Point2d IsoRectangle2_GetMax(IntPtr ptr);

        internal abstract void IsoRectangle2_SetMax(IntPtr ptr, Point2d point);

        internal abstract double IsoRectangle2_Area(IntPtr ptr);

        internal abstract BOUNDED_SIDE IsoRectangle2_BoundedSide(IntPtr ptr, Point2d point);

        internal abstract bool IsoRectangle2_ContainsPoint(IntPtr ptr, Point2d point, bool inculdeBoundary);

        internal abstract bool IsoRectangle2_IsDegenerate(IntPtr ptr);

        internal abstract IntPtr IsoRectangle2_Transform(IntPtr ptr, Point2d translation, double rotation, double scale);

    }
}
