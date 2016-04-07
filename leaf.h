#ifndef LEAF
#define LEAF

#include "inode.h"
#include "color.h"
#include "drawer.h"

class Leaf : public iNode
{
public:
    //! Can't have childrens
    void addChild(iNode* child) = delete;

    //! Draw itself
    //! \return available point for the next node
    Point draw(Point point)
    {
        m_topCoord = point;
        Drawer::DrawNode(false, false, point, lim_square_size, getColor(Color::red), m_name);
        point.y += lim_node_full_height;

        return point;
    }
};

#endif // LEAF

