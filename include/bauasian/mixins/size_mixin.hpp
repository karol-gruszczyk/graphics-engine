#ifndef BAUASIAN_SIZE_MIXIN_HPP
#define BAUASIAN_SIZE_MIXIN_HPP


namespace bauasian
{
	template <typename T>
	class SizeMixin;
}

template <typename T>
class bauasian::SizeMixin
{
public:
	virtual const T& getSize() const
	{ return m_size; }

	virtual void setSize(const T& size)
	{ m_size = size; };

protected:
	T m_size;

};

#endif /* BAUASIAN_SIZE_MIXIN_HPP */
