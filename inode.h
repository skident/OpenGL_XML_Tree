#ifndef INODE_H
#define INODE_H

#include <memory>
#include <vector>
#include "point.h"

class iNode : public std::enable_shared_from_this<iNode>
{
private:
    friend class Tree;

protected:
    typedef std::vector<std::shared_ptr<iNode>> tPtrContainer;

    //! Status of node
    enum eStatus
    {
        status_needOpen,            //! need open (click on closed node)
        status_needClose,           //! need close (click on opened node)
        status_none                 //! node doesn't have status
    };

    //! Internal limits
    enum eLimits
    {
        lim_node_full_height= 40,   //! height of node (height of square + margin between nodes)
        lim_left_indent     = 20,   //! uses for indent nested nodes
        lim_step_percent    = 5,    //! percentage of opening/closing node with state
        lim_square_size     = 20,   //! length of square's edge
    };

    iNode*          m_parent;       //! parent of current node
    tPtrContainer   m_childrens;    //! childrens of current node
    bool            m_isOpened;     //! current state of node (opened, closed)
    eStatus         m_status;       //! current status of node (need to open, need to close)
    std::string     m_name;         //! name (title) of node
    Point           m_topCoord;     //! position from which element will be drawn

    static int      m_winWidth;     //! window width
    static int      m_winHeight;    //! window height

public:
    //! Construcor
    iNode(bool isOpened = false);

    //! Destructor
    virtual ~iNode();

    //! Get height of node in pixels (element heihgt + margin)
    std::size_t getHeight() const;

    //! Set parent for node
    void setParent(iNode* parent);

    //! Set name(title) of node
    void setName(std::string name);

    //! Add child to node
    void addChild(std::shared_ptr<iNode> child);

    //! Get count of visible children
    std::size_t getVisibleChildrenCount() const;

	//! Is node opened 
    bool isOpened() const;

	//! Is node has childrens
    bool hasChildrens() const;

	//! Get coordinated of node
    Point getCoords() const;

	//! Get last children if it exists
    std::shared_ptr<iNode> getLastChild();

    //! Check is point in node coordinates
    bool contains(Point point);

    //! Redraw self and register own coordinates
    //! \sa pattern template method
    Point draw(int winWidth, int winHeight, Point point);

    //! Every inherited class must override this method
    virtual Point draw(Point point) = 0;
};


#endif // INODE_H
