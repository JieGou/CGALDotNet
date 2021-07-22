#pragma once

#include "CGALWrapper.h"
#include "Geometry2.h"
#include "Polygon2.h"
#include "PolygonWithHoles2.h"
#include "IndexMap.h"

#include <vector>
#include "CGAL/Point_2.h"
#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#define NULL_INDEX -1

struct TriVertex2
{
	Point2d Point;
	BOOL IsInfinite;
	int Degree;
	int Index;
	int FaceIndex;

	static TriVertex2 NullVertex()
	{
		TriVertex2 v;
		v.Point = { 0, 0 };
		v.IsInfinite = false;
		v.Degree = 0;
		v.Index = NULL_INDEX;
		v.FaceIndex = NULL_INDEX;
		return v;
	}
};

struct TriFace2
{
	BOOL IsInfinite;
	int Index;
	int VertexIndices[3];

	static TriFace2 NullFace()
	{
		TriFace2 f;
		f.IsInfinite = false;
		f.Index = NULL_INDEX;
		f.VertexIndices[0] = NULL_INDEX;
		f.VertexIndices[1] = NULL_INDEX;
		f.VertexIndices[2] = NULL_INDEX;
		return f;
	}
};

template<class K>
class Triangulation2
{

public:

	typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
	typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
	typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;

	typedef CGAL::Triangulation_2<K, Tds> Triangulation_2;
	typedef typename Triangulation_2::Point Point_2;

	typedef typename Triangulation_2::Finite_faces_iterator Finite_faces;
	typedef typename Triangulation_2::Finite_vertices_iterator Finite_vertices;
	typedef typename Triangulation_2::Face_handle Face;
	typedef typename Triangulation_2::Vertex_handle Vertex;


private:

	Triangulation_2 model;

	IndexMap<Vertex> vertexMap;

	IndexMap<Face> faceMap;

public:

	Triangulation2()
	{

	}

	~Triangulation2()
	{

	}

	inline static Triangulation2* CastToTriangulation2(void* ptr)
	{
		return static_cast<Triangulation2*>(ptr);
	}

	static void Clear(void* ptr)
	{
		auto tri = CastToTriangulation2(ptr);
		tri->model.clear();
		tri->ClearMaps();
	}

	static void* Copy(void* ptr)
	{
		auto tri = CastToTriangulation2(ptr);

		auto copy = new Triangulation2<K>();
		copy->model = tri->model;

		return copy;
	}

	static BOOL IsValid(void* ptr)
	{
		auto tri = CastToTriangulation2(ptr);
		return tri->model.is_valid();
	}

	static int VertexCount(void* ptr)
	{
		auto tri = CastToTriangulation2(ptr);
		return (int)tri->model.number_of_vertices();
	}

	static int FaceCount(void* ptr)
	{
		auto tri = CastToTriangulation2(ptr);
		return (int)tri->model.number_of_faces();
	}

	static void InsertPoint(void* ptr, Point2d point)
	{
		auto tri = CastToTriangulation2(ptr);
		tri->model.insert(point.ToCGAL<K>());
		tri->OnModelChanged();
	}

	static void InsertPoints(void* ptr, Point2d* points, int startIndex, int count)
	{
		auto tri = CastToTriangulation2(ptr);

		std::vector<Point_2> list(count);
		for (int i = 0; i < count; i++)
			list[i] = points[startIndex + i].ToCGAL<K>();

		tri->model.insert(list.begin(), list.end());
		tri->OnModelChanged();
	}

	static void InsertPolygon(void* triPtr, void* polyPtr)
	{
		auto tri = CastToTriangulation2(triPtr);

		auto polygon = Polygon2<K>::CastToPolygon2(polyPtr);
		tri->model.insert(polygon->vertices_begin(), polygon->vertices_end());
		tri->OnModelChanged();
	}

	static void InsertPolygonWithHoles(void* triPtr, void* pwhPtr)
	{
		auto tri = CastToTriangulation2(triPtr);

		auto pwh = PolygonWithHoles2<K>::CastToPolygonWithHoles2(pwhPtr);

		if(!pwh->is_unbounded())
			tri->model.insert(pwh->outer_boundary().vertices_begin(), pwh->outer_boundary().vertices_end());

		for (auto& hole : pwh->holes())
			tri->model.insert(hole.vertices_begin(), hole.vertices_end());

		tri->OnModelChanged();
	}

	static void GetPoints(void* ptr, Point2d* points, int startIndex, int count)
	{
		auto tri = CastToTriangulation2(ptr);
		int i = startIndex;

		for (const auto& vert : tri->model.finite_vertex_handles())
			points[i++] = Point2d::FromCGAL<K>(vert->point());
	}

	static void GetIndices(void* ptr, int* indices, int startIndex, int count)
	{
		auto tri = CastToTriangulation2(ptr);
		int index = startIndex;

		tri->SetVertexIndices();

		for (auto& face : tri->model.finite_face_handles())
		{
			indices[index * 3 + 0] = face->vertex(0)->info();
			indices[index * 3 + 1] = face->vertex(1)->info();
			indices[index * 3 + 2] = face->vertex(2)->info();

			index++;
		}
	}

	static BOOL GetVertex(void* ptr, int index, TriVertex2& triVert)
	{
		auto tri = CastToTriangulation2(ptr);
		
		auto vert = tri->FindVertex(index);
		if (vert != nullptr)
		{
			triVert = ToTriVertex2(tri, *vert);
			return TRUE;
		}
		else
		{
			triVert = TriVertex2::NullVertex();
			return FALSE;
		}
	}

	static void GetVertices(void* ptr, TriVertex2* vertices, int startIndex, int count)
	{
		auto tri = CastToTriangulation2(ptr);
		int i = startIndex;

		tri->SetVertexIndices();
		tri->SetFaceIndices();

		for (const auto& vert : tri->model.finite_vertex_handles())
			vertices[i++] = ToTriVertex2(tri, vert);
	}

	static BOOL GetFace(void* ptr, int index, TriFace2& triFace)
	{
		auto tri = CastToTriangulation2(ptr);

		auto face = tri->FindFace(index);
		if (face != nullptr)
		{
			triFace = ToTriFace2(tri, *face);
			return TRUE;
		}
		else
		{
			triFace = TriFace2::NullFace();
			return FALSE;
		}
	}

	static void GetFaces(void* ptr, TriFace2* faces, int startIndex, int count)
	{
		auto tri = CastToTriangulation2(ptr);
		int i = startIndex;

		tri->SetVertexIndices();
		tri->SetFaceIndices();

		for (const auto& face : tri->model.finite_face_handles())
			faces[i++] = ToTriFace2(tri, face);
	}

	static BOOL LocateFace(void* ptr, Point2d point, TriFace2& triFace)
	{
		auto tri = CastToTriangulation2(ptr);

		auto face = tri->model.locate(point.ToCGAL<K>());
		if (face != nullptr)
		{
			triFace = ToTriFace2(tri, face);
			return TRUE;
		}
		else
		{
			triFace = TriFace2::NullFace();
			return FALSE;
		}
	}

	static BOOL MoveVertex(void* ptr, int index, Point2d point, BOOL ifNoCollision, TriVertex2& triVert)
	{
		auto tri = CastToTriangulation2(ptr);

		auto vert = tri->FindVertex(index);
		if (vert != nullptr)
		{
			Vertex v; 
			
			if(ifNoCollision)
				v = tri->model.move(*vert, point.ToCGAL<K>());
			else
				v = tri->model.move_if_no_collision(*vert, point.ToCGAL<K>());

			if(v != *vert)
				tri->OnModelChanged();

			triVert = ToTriVertex2(tri, v);
			return TRUE;
		}
		else
		{
			triVert = TriVertex2::NullVertex();
			return FALSE;
		}
	}

	static BOOL RemoveVertex(void* ptr, int index)
	{
		auto tri = CastToTriangulation2(ptr);

		auto vert = tri->FindVertex(index);
		if (vert != nullptr)
		{
			tri->model.remove(*vert);
			tri->OnModelChanged();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	static BOOL FlipEdge(void* ptr, int faceIndex, int neighbourIndex)
	{

		auto tri = CastToTriangulation2(ptr);

		auto face = tri->FindFace(faceIndex);
		auto neighbour = tri->FindFace(neighbourIndex);
		if (face != nullptr && neighbour != nullptr)
		{
			if (tri->model.is_infinite(*face))
				return FALSE;

			int n = NeighbourIndex(*face, *neighbour);
			if (n == NULL_INDEX)
				return FALSE;

			if (tri->model.is_infinite(*neighbour))
				return FALSE;

			tri->model.flip(*face, n);
			tri->OnModelChanged();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	private:

		static int NeighbourIndex(Face face, Face neighbour)
		{
			for (int i = 0; i < 3; i++)
			{
				if (face->neighbor(i) == neighbour)
					return i;
			}

			return NULL_INDEX;
		}

		static TriVertex2 ToTriVertex2(Triangulation2* tri, Vertex vert)
		{
			TriVertex2 triVertex;
			triVertex.Point = Point2d::FromCGAL<K>(vert->point());
			triVertex.IsInfinite = tri->model.is_infinite(vert);
			triVertex.Degree = tri->Degree(tri->model, vert);
			triVertex.Index = vert->info();

			auto face = vert->face();

			if (tri->model.is_infinite(face))
				triVertex.FaceIndex = NULL_INDEX;
			else
				triVertex.FaceIndex = face->info();

			return triVertex;
		}

		static TriFace2 ToTriFace2(Triangulation2* tri, Face face)
		{
			TriFace2 triFace;
			triFace.IsInfinite = tri->model.is_infinite(face);
			triFace.Index = face->info();

			for (int j = 0; j < 3; j++)
			{
				auto vert = face->vertex(j);

				if (tri->model.is_infinite(vert))
					triFace.VertexIndices[j] = NULL_INDEX;
				else
					triFace.VertexIndices[j] = vert->info();
			}

			return triFace;
		}

		int Degree(Triangulation_2& tri, Vertex vert)
		{
			auto face = vert->face();
			auto start = vert->incident_faces(face), end(start);

			int count = 0;

			if (!start.is_empty())
			{
				do
				{
					if (!tri.is_infinite(start))
						++count;

				} while (++start != end);
			}

			return count;
		}

		void ResetFace(const Triangulation_2& tri, Vertex vert)
		{
			auto face = vert->face();
			auto start = vert->incident_faces(face), end(start);

			if (start != nullptr)
			{
				do
				{
					if (!tri.is_infinite(start))
					{
						vert->set_face(start);
						return;
					}
				} while (++start != end);
			}
		}

		void SetVertexIndices()
		{
			if (vertexMap.indicesSet)
				return;

			vertexMap.Clear();

			for (auto& vert : model.finite_vertex_handles())
			{
				if (model.is_infinite(vert->face()))
					ResetFace(model, vert);

				vert->info() = vertexMap.NextIndex();
			}

			vertexMap.indicesSet = true;
		}

		void BuildVertexMap()
		{
			if (vertexMap.mapBuilt)
				return;

			vertexMap.ClearMap();

			for (auto& vert : model.finite_vertex_handles())
				vertexMap.Insert(vert->info(), vert);

			vertexMap.mapBuilt = true;
		}

		void SetFaceIndices()
		{
			if (faceMap.indicesSet)
				return;

			faceMap.Clear();

			for (auto& face : model.finite_face_handles())
				face->info() = faceMap.NextIndex();

			faceMap.indicesSet = true;
		}

		void BuildFaceMap()
		{
			if (faceMap.mapBuilt)
				return;

			faceMap.ClearMap();

			for (auto& face : model.finite_face_handles())
				faceMap.Insert(face->info(), face);

			faceMap.mapBuilt = true;
		}

		void BuildMaps()
		{
			BuildVertexMap();
			BuildFaceMap();
		}

		void ClearMaps()
		{
			vertexMap.Clear();
			faceMap.Clear();
		}

		void OnModelChanged()
		{
			ClearMaps();
		}

		Vertex* FindVertex(int index)
		{
			SetVertexIndices();
			BuildVertexMap();
			return vertexMap.Find(index);
		}

		Face* FindFace(int index)
		{
			SetFaceIndices();
			BuildFaceMap();
			return faceMap.Find(index);
		}

};