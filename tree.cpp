#include "tree.h"

// constructor
Tree::Tree()
{

}

// destructor
Tree::~Tree()
{

}

// add new node
void Tree::push_back(std::shared_ptr<iNode> node)
{
    m_nodeList.push_back(node);
}

// clear container
void Tree::clear()
{
    m_nodeList.clear();
}

// get count of visible items
int Tree::getVisibleItemsCount() const
{
    int count = 0;
    for (auto& node : m_nodeList)
    {
        count += node->getVisibleChildrenCount();
    }
    return count + m_nodeList.size();
}

// get height of visible nodes
int Tree::getVisibleNodesHeight()
{
    auto count = getVisibleItemsCount();
    int pixelSize = 0;
    if (count > 0)
        pixelSize = count * m_nodeList[0]->getHeight();
    return pixelSize;
}

// draw the whole tree of nodes
void Tree::draw(int winWidth, int winHeight, Point point)
{
    Point nextPoint = point;
    for (auto& node : m_nodeList)
    {
         nextPoint = node->draw(winWidth, winHeight, nextPoint);
    }
}

std::shared_ptr<iNode> Tree::findOwner(Point clicked)
{
    std::shared_ptr<iNode> node;
    for (auto& node : m_nodeList)
    {
         if(node->contains(clicked))
            return node;

         for (auto& child : node->m_childrens)
         {
             if (child->contains(clicked))
                 return child;
         }
    }

    return node;
}
