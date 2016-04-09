#include "inode.h"

#include "coordmap.h"

int iNode::m_winWidth = 0;     // window width
int iNode::m_winHeight = 0;    // window height

iNode::iNode(bool isOpened)
    : m_parent(nullptr)
    , m_isOpened(isOpened)
    , m_status(status_none)
{

}

iNode::~iNode()
{
}

std::size_t iNode::getHeight() const
{
    return lim_node_full_height;
}

void iNode::setParent(iNode* parent)
{
    m_parent = parent;
}

void iNode::setName(std::string name)
{
    m_name = name;
}

void iNode::addChild(std::shared_ptr<iNode> child)
{
    // add if not empty
    if (child.get() != nullptr)
        m_childrens.push_back(child);
}

std::size_t iNode::getVisibleChildrenCount() const
{
    int count = 0;
    if (m_isOpened || m_status == status_needOpen)
    {
        for (std::size_t i = 0; i < m_childrens.size(); i++)
            count += m_childrens[i]->getVisibleChildrenCount() + 1;
    }
    return count;
}

bool iNode::isOpened() const
{
    return (m_isOpened || m_status == status_needOpen);
}

bool iNode::hasChildrens() const
{
    return !m_childrens.empty();
}

std::shared_ptr<iNode> iNode::getLastChild()
{
    std::shared_ptr<iNode> node;
    if (!m_childrens.empty())
        node = *m_childrens.rbegin();
    return node;
}

Point iNode::getCoords() const
{
    return m_topCoord;
}

bool iNode::contains(Point point)
{
    return (m_topCoord.y <= point.y && m_topCoord.y+lim_square_size >= point.y);
}

// caching windows params and draw self and every child
Point iNode::draw(int winWidth, int winHeight, Point point)
{
    m_winWidth = winWidth;
    m_winHeight = winHeight;
    return draw(point);
}
