#include "config.h"
#include <string>
#include <iostream>
#include <exception>
#include "node.h"
#include "leaf.h"
#include <fstream>

using namespace std;

//! Constructor
Config::Config(Tree& tree)
    : m_tree(tree)
{

}

//! Load data from file into memory and fill tree of nodes
bool Config::loadDocument(std::string documentName)
{
    TiXmlDocument doc(documentName.c_str());
    bool loadOkay = doc.LoadFile();
    if (!loadOkay)
    {
	string logName = "error.log";
	fstream log(logName, ios::app);
	if (!log.is_open())
	    log.open("error.log", ios::out);

	if (log.is_open())
	    log << "Can't open file " << documentName << endl;
        return false;
    }

    parseNodes(&doc); // defined later in the tutorial
    return true;
}

//! Parse attributes of node like "name=node2"
void Config::parseAttribs(TiXmlElement* pElement, shared_ptr<iNode> parentNode)
{
    if (!pElement)
        return;

    TiXmlAttribute* pAttrib=pElement->FirstAttribute();
    while (pAttrib)
    {
        std::string tag(pAttrib->Name());
        std::string value(pAttrib->Name());
        if (tag == "name")
            parentNode->setName(pAttrib->Value());
        else
        {
            shared_ptr<iNode> node = shared_ptr<iNode>(new Leaf());
            node->setName(tag + " : " + value);
            parentNode->addChild(node);
        }
        pAttrib = pAttrib->Next();
    }
}

//! Parse nodes (works recursively)
void Config::parseNodes( TiXmlNode* pParent, shared_ptr<iNode> parentNode)
{
    if (!pParent)
        return;

    shared_ptr<iNode> node;

    if (pParent->Type() == TiXmlNode::TINYXML_ELEMENT)
    {
        std::string val(pParent->Value());
        if (val != "Document" && val != "")
        {
            node = shared_ptr<iNode>(new Node());
            if (parentNode.get())
                parentNode->addChild(node);
            else
                m_tree.push_back(node);
        }

        parseAttribs(pParent->ToElement(), node);
    }


    for (TiXmlNode* pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
    {
        parseNodes( pChild, node);
    }
}




