#ifndef NODE_H
#define NODE_H

#include "inode.h"

class Node : public iNode
{
private:
    bool m_isClicked;       //! true if user clicked on node
    char m_actionPercent;   //! percent of opening/closing node

    //! Register coordinates
    void registerCoords(Point topLeft, Point bottomRight);

    void calculateActionPercent();

public:
    //! Constructor
    Node(bool isOpened = false);

    //! Destructor
    ~Node();

    //! Set node as clicked
    void setClicked();

    //! Check is node clicked
    bool clicked() const;

    //! Draw itself
    //! \return available coordinates for next node
    Point draw(Point point);
};


#endif // NODE_H
