#ifndef COORDMAP_H
#define COORDMAP_H

#include "inode.h"
#include <memory>

struct ElementInfo
{
    Point topLeft;
    Point bottomRight;
    std::shared_ptr<iNode> node;

    ElementInfo(const Point& _topLeft, const Point& _bottomRight, std::shared_ptr<iNode> _node)
        : topLeft(_topLeft)
        , bottomRight(_bottomRight)
    {
        node = _node;
    }
};

//! Container of visible nodes and their coordinates
//! Meyers' singleton (safe-thread in C++11 and greater)
class CoordMap
{
private:
    std::vector<ElementInfo> m_container; //! container for nodes info

    CoordMap() {}
    ~CoordMap() {}
    CoordMap(const CoordMap& rhs);
    CoordMap& operator=(const CoordMap& rhs);

public:
    //! \return handle on self
    static CoordMap* get();

    //! Register new node's info
    void add(Point _startPoint, Point _endPoint, std::shared_ptr<iNode> _node);

    //! Find node which contains coordinates from variable clicked
    //! \return shared pointer on node if found, otherwise - empty shared pointer
    std::shared_ptr<iNode> find(Point clicked);

    //! Remove all info about registered nodes
    void clear();
};

#endif // COORDMAP_H

