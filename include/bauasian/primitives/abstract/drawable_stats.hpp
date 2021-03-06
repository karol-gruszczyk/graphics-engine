#ifndef BAUASIAN_DRAWABLE_STATS_HPP
#define BAUASIAN_DRAWABLE_STATS_HPP


namespace bauasian
{
	class DrawableStats;
}

class bauasian::DrawableStats
{
public:
	DrawableStats(unsigned num_vertices, unsigned num_faces);

	unsigned getNumVertices() const
	{ return m_num_vertices; }
	unsigned getNumFaces() const
	{ return m_num_faces; }

private:
	unsigned m_num_vertices;
	unsigned m_num_faces;

};

#endif /* BAUASIAN_DRAWABLE_STATS_HPP */
