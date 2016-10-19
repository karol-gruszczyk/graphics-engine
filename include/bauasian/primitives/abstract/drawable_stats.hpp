#ifndef BAUASIAN_DRAWABLE_STATS_HPP
#define BAUASIAN_DRAWABLE_STATS_HPP


namespace bauasian
{
	class DrawableStats;
}

class bauasian::DrawableStats
{
public:
	DrawableStats(const unsigned& num_vertices, const unsigned& num_faces);

	const unsigned& getNumVertices() const;
	const unsigned& getNumFaces() const;

private:
	unsigned m_num_vertices;
	unsigned m_num_faces;

};

#endif /* BAUASIAN_DRAWABLE_STATS_HPP */
