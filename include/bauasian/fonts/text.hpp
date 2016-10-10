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
	Text(Font* font, const std::string& text = "", const unsigned& font_size = 0, const glm::vec3& color = { 0.f, 0.f, 0.f });

	const std::string& getText() const;
	void setText(const std::string& text);
	const glm::vec3& getTextColor() const;
	void setTextColor(const glm::vec3& text_color);
	const unsigned& getFontSize() const;
	void setFontSize(const unsigned& font_size);

	void setScale(const glm::vec2& scale) override;
	void render() const override;

private:
	Font* m_font;
	std::string m_text;
	glm::vec3 m_color;
	unsigned m_font_size;

	GLint m_location_text_color;
	GLint m_location_model_matrix;

	void updateBufferObjects();
};

#endif /* BAUASIAN_TEXT_HPP */
