#ifndef GRAPHICS_ENGINE_TEXT_HPP
#define GRAPHICS_ENGINE_TEXT_HPP

#include "font.hpp"


namespace engine
{
	class Text;
}

class engine::Text
{
public:
	Text(Font* font);
	~Text();

	const std::string& getText() const;
	void setText(const std::string& text);
	const glm::vec3& getTextColor() const;
	void setTextColor(const glm::vec3& text_color);
private:
	GLuint m_vao_id, m_vbo_id;
	std::string m_text;
	glm::vec3 m_text_color;
	Font* m_font;
};

#endif /* GRAPHICS_ENGINE_TEXT_HPP */
