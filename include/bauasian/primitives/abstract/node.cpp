#include "node.hpp"


using bauasian::Node;

void Node::addChildren(Node* node)
{
	m_children.push_back(node);
}
