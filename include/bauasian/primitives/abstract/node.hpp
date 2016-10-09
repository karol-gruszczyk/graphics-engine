#ifndef BAUASIAN_NODE_HPP
#define BAUASIAN_NODE_HPP

#include <list>


namespace bauasian
{
	class Node;
}

class bauasian::Node
{
public:
	void addChildren(Node* node);

protected:
	std::list<Node*> m_children;

};

#endif /* BAUASIAN_NODE_HPP */
