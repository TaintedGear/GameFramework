#include "XMLElement.h"

//------------------------------------------//
// XMLElement::XMLElement				
//------------------------------------------//
XMLElement::XMLElement(rapidxml::xml_node<>* node) :
mNode(node)
{
}

//------------------------------------------//
// XMLElement::AddAttribute				
//------------------------------------------//
void XMLElement::AddAttribute(XMLAttribute& newAttribute)
{
	mNode->insert_attribute(0, newAttribute.GetRapidXMLAttribute());
}

//------------------------------------------//
// XMLElement::AppendAttribute				
//------------------------------------------//
void XMLElement::AppendAttribute(XMLAttribute& appendAttribute)
{
	mNode->append_attribute(appendAttribute.GetRapidXMLAttribute());
}

//------------------------------------------//
// XMLElement::GetValue				
//------------------------------------------//
const std::string XMLElement::GetValue() const
{
	return mNode->value();
}

//------------------------------------------//
// XMLElement::GetChildElement				
//------------------------------------------//
XMLElement XMLElement::GetChildElement(const std::string& childElementTag) const
{
	if (mNode != nullptr)
	{
		XMLElement childElement = mNode->first_node(childElementTag.c_str());
	}
	else
	{
		//log
	}
}

//------------------------------------------//
// XMLElement::GetAttribute				
//------------------------------------------//
XMLAttribute XMLElement::GetAttribute(const std::string& attributeTag)
{
	XMLAttribute xmlAttribute(mNode->first_attribute(attributeTag.c_str()));

	return xmlAttribute;
}

//------------------------------------------//
// XMLElement::SetValue				
//------------------------------------------//
void XMLElement::SetValue(const std::string& elementValue)
{
	if (mNode != nullptr)
	{
		if (elementValue.size() > 0)
		{
			mNode->value(&elementValue[0], elementValue.size());
		}
		else
		{
			//Log
		}
	}
	else
	{
		//Log
	}
}

//------------------------------------------//
// XMLElement::AddChildElement				
//------------------------------------------//
void XMLElement::AddChildElement(XMLElement& childElement)
{
	if (mNode != nullptr)
	{
		if (childElement.GetRapidXMLNode() != nullptr)
		{
			mNode->insert_node(0, childElement.GetRapidXMLNode());
		}
	}
	else
	{
		//Log
	}
}

//------------------------------------------//
// XMLElement::GetRapidXMLNode				
//------------------------------------------//
rapidxml::xml_node<>* XMLElement::GetRapidXMLNode()
{
	return mNode;
}
