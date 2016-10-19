#include "drawable_stats.hpp"


using bauasian::DrawableStats;

DrawableStats::DrawableStats(const unsigned& num_vertices, const unsigned& num_faces)
		: m_num_vertices(num_vertices), m_num_faces(num_faces)
{}

const unsigned& DrawableStats::getNumVertices() const
{
	return m_num_vertices;
}

const unsigned& DrawableStats::getNumFaces() const
{
	return m_num_faces;
}
