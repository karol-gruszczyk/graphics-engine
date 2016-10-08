#ifndef BAUASIAN_RENDERABLE_STATS_HPP
#define BAUASIAN_RENDERABLE_STATS_HPP


namespace bauasian
{
	class RenderableStats;
}

class bauasian::RenderableStats
{
public:
	RenderableStats(const unsigned& num_vertices, const unsigned& num_faces);

	const unsigned& getNumVertices() const;
	const unsigned& getNumFaces() const;

private:
	unsigned m_num_vertices;
	unsigned m_num_faces;

};

#endif /* BAUASIAN_RENDERABLE_STATS_HPP */
