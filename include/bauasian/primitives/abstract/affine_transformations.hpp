#ifndef BAUASIAN_AFFINE_TRANSFORMATIONS_HPP
#define BAUASIAN_AFFINE_TRANSFORMATIONS_HPP

#include <glm/glm.hpp>


namespace bauasian
{
	class AffineTransformations;
}

class bauasian::AffineTransformations
{
public:
	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);
	void translate(const glm::vec3& position);
	const glm::vec3& getRotation() const;
	void setRotation(const glm::vec3& rotation);
	void rotate(const glm::vec3& rotation);
	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);
	const glm::vec3& getPivot() const;
	void setPivot(const glm::vec3& pivot);

	const glm::mat4& getModelMatrix() const;
	const glm::mat4 getNormalMatrix() const;
protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_pivot;

	glm::mat4 m_model_matrix;

};


#endif /* BAUASIAN_AFFINE_TRANSFORMATIONS_HPP */
