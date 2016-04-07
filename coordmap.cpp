#include "coordmap.h"

CoordMap* CoordMap::get()
{
    static CoordMap self;
    return &self;
}

void CoordMap::add(Point _startPoint, Point _endPoint, std::shared_ptr<iNode> _node)
{
    ElementInfo info(_startPoint, _endPoint, _node);
    m_container.push_back(info);
}

std::shared_ptr<iNode> CoordMap::find(Point clicked)
{
    for (auto& info : m_container)
    {
        if (info.topLeft.y <= clicked.y && clicked.y < info.bottomRight.y)
            if (info.topLeft.x <= clicked.x && clicked.x < info.bottomRight.x)
                return info.node;
    }
    return nullptr;
}

void CoordMap::clear()
{
    m_container.clear();
}
