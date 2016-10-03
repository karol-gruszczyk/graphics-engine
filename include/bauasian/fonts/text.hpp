#ifndef BAUASIAN_TEXT_HPP
#define BAUASIAN_TEXT_HPP

#include "font.hpp"


namespace bauasian
{
	class Text;
}

class bauasian::Text : public Entity2D
{
public:
	Text(Font* font, const std::string& text = "", const glm::vec3& color = { 0.f, 0.f, 0.f });

	const std::string& getText() const;
	void setText(const std::string& text);
	const glm::vec3& getTextColor() const;
	void setTextColor(const glm::vec3& text_color);
	void render() const override;

private:
	std::string m_text;
	glm::vec3 m_color;
	Font* m_font;

	void updateBufferObjects();
};

#endif /* BAUASIAN_TEXT_HPP */
