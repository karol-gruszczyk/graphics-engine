#ifndef BAUASIAN_AFFINE_TRANSFORMATIONS_3D_HPP
#define BAUASIAN_AFFINE_TRANSFORMATIONS_3D_HPP

#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace bauasian
{
	class AffineTransformations3D;
}

class bauasian::AffineTransformations3D
{
public:
	virtual const glm::vec3& getPosition() const;
	virtual void setPosition(const glm::vec3& position);
	virtual void translate(const glm::vec3& position);
	virtual const glm::vec3& getRotation() const;
	virtual void setRotation(const glm::vec3& rotation);
	virtual void rotate(const glm::vec3& rotation);
	virtual const glm::vec3& getScale() const;
	virtual void setScale(const glm::vec3& scale);
	virtual const glm::vec3& getPivot() const;
	virtual void setPivot(const glm::vec3& pivot);

	virtual const glm::mat4& getModelMatrix() const;
	virtual void setModelMatrix(const glm::mat4& matrix);
	virtual const glm::mat4 getNormalMatrix() const;

protected:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 m_pivot;

	glm::quat m_rotation_quat;
	glm::mat4 m_model_matrix;

};

#endif /* BAUASIAN_AFFINE_TRANSFORMATIONS_3D_HPP */
