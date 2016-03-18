#include "XMLParser.h"

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
	if (mNode != nullptr)
	{
		mNode->insert_attribute(0, newAttribute.GetRapidXMLAttribute());
	}
}

//------------------------------------------//
// XMLElement::AppendAttribute				
//------------------------------------------//
void XMLElement::AppendAttribute(XMLAttribute& appendAttribute)
{
	if (mNode != nullptr)
	{
		mNode->append_attribute(appendAttribute.GetRapidXMLAttribute());
	}
}

//------------------------------------------//
// XMLElement::GetName				
//------------------------------------------//
const std::string XMLElement::GetName() const
{
	return mNode != nullptr ? mNode->name() : "";
}

//------------------------------------------//
// XMLElement::GetValue				
//------------------------------------------//
const std::string XMLElement::GetValue() const
{
	return mNode != nullptr ? mNode->value() : "Null";
}

//------------------------------------------//
// XMLElement::GetChildElement				
//------------------------------------------//
XMLElement XMLElement::GetFirstChildElement() const
{
	XMLElement childElement = mNode->first_node();

	return childElement;
}

//------------------------------------------//
// XMLElement::GetLastChildElement				
//------------------------------------------//
XMLElement XMLElement::GetLastChildElement() const
{
	XMLElement childElement = mNode->last_node();

	return childElement;
}

//------------------------------------------//
// XMLElement::GetFirstAttribute				
//------------------------------------------//
XMLAttribute XMLElement::GetFirstAttribute() const
{
	XMLAttribute xmlAttribute(mNode->first_attribute());

	return xmlAttribute;
}

//------------------------------------------//
// XMLElement::GetLastAttribute				
//------------------------------------------//
XMLAttribute XMLElement::GetLastAttribute() const
{
	XMLAttribute xmlAttribute(mNode->last_attribute());

	return xmlAttribute;
}

//------------------------------------------//
// XMLElement::GetAllAttributes				
//------------------------------------------//
std::vector<XMLAttribute> XMLElement::GetAllAttributes() const
{
	std::vector<XMLAttribute> attributeVec;

	for (rapidxml::xml_attribute<>* attr = mNode->first_attribute();
		attr != nullptr;
		attr = attr->next_attribute())
	{
		attributeVec.push_back(XMLAttribute(attr));
	}

	return attributeVec;
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
