#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <memory>
#include "inode.h"
#include "tinyxml/tinyxml.h"
#include "tree.h"

class Config
{
private:
    Tree& m_tree;

    void parseAttribs(TiXmlElement* pElement, std::shared_ptr<iNode> parentNode);
    void parseNodes( TiXmlNode* pParent, std::shared_ptr<iNode> parentNode = std::shared_ptr<iNode>(nullptr));
public:
    Config(Tree& tree);
    bool loadDocument(std::string documentName);
};

#endif // CONFIG_H
