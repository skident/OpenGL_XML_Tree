#ifndef TREE_H
#define TREE_H

#include "inode.h"
#include <vector>

class Tree
{
private:
    std::vector<std::shared_ptr<iNode>> m_nodeList;

public:
    //! Constructor
    Tree();

    //! Destructor
    ~Tree();

    //! Append new node
    void push_back(std::shared_ptr<iNode> node);

    //! Clear tree
    void clear();

    //! Get count of visible items
    int getVisibleItemsCount() const;

    //! Get height of all visible items in pixels
    int getVisibleNodesHeight();

    //! Get coordinates of the last visible object
    Point getLastVisibleCoords() const;

    //! Draw the whole tree
    //! \param winWindth width of window
    //! \param winHeight height of window
    //! \param point point for first node
    void draw(int winWidth, int winHeight, Point point);

    //! Find node who is the owner of clicked coordinates
    //! \param clicked mouse click coordinates
    std::shared_ptr<iNode> findOwner(Point clicked);
};

#endif // TREE_H
