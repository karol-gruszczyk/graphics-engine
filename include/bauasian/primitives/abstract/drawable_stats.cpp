#include "drawable_stats.hpp"


using bauasian::DrawableStats;

DrawableStats::DrawableStats(unsigned num_vertices, unsigned num_faces)
		: m_num_vertices(num_vertices), m_num_faces(num_faces)
{}

unsigned DrawableStats::getNumVertices() const
{
	return m_num_vertices;
}

unsigned DrawableStats::getNumFaces() const
{
	return m_num_faces;
}
