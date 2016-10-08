#include "renderable_stats.hpp"


using bauasian::RenderableStats;

RenderableStats::RenderableStats(const unsigned& num_vertices, const unsigned& num_faces)
		: m_num_vertices(num_vertices), m_num_faces(num_faces)
{}

const unsigned& RenderableStats::getNumVertices() const
{
	return m_num_vertices;
}

const unsigned& RenderableStats::getNumFaces() const
{
	return m_num_faces;
}
