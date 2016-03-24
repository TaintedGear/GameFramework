#include "XMLParser.h"
#include "Log.h"

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
// XMLElement::CreateChildElement				
//------------------------------------------//
XMLElement XMLElement::CreateChildElement(const std::string& elementName /*= ""*/, const std::string& elementValue /*= ""*/)
{
	if (mNode != nullptr)
	{
		rapidxml::xml_document<>* parentDoc = mNode->document();
		if (parentDoc != nullptr)
		{
			rapidxml::xml_node<>* newNode = nullptr;

			//Allocate strings
			char* name = parentDoc->allocate_string(elementName.c_str(), elementName.size());
			char* value = parentDoc->allocate_string(elementValue.c_str(), elementValue.size());

			newNode = parentDoc->allocate_node(
				rapidxml::node_element,
				name,
				value,
				elementName.size(),
				elementValue.size());

			mNode->insert_node(0, newNode);

			XMLElement newElement(newNode);
			return newElement;
		}
	}

	Log::GetLog().LogCriticalMsg("Failed to create child node");
	return XMLElement(nullptr);
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
	XMLElement childElement(mNode->first_node());

	return childElement;
}

//------------------------------------------//
// XMLElement::GetLastChildElement				
//------------------------------------------//
XMLElement XMLElement::GetLastChildElement() const
{
	XMLElement childElement(mNode->last_node());

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
// XMLElement::GetAllChildElements				
//------------------------------------------//
bool XMLElement::GetAllChildElements(std::vector<XMLElement>& childElements)
{
	if (mNode == nullptr)
	{
		return false;
	}

	for (rapidxml::xml_node<>* child = mNode->first_node();
		child != nullptr;
		child = child->next_sibling())
	{
		childElements.push_back(XMLElement(child));
	}

	return true;
}

//------------------------------------------//
// XMLElement::GetSiblingElement				
//------------------------------------------//
XMLElement XMLElement::GetSiblingElement() const
{
	return XMLElement(mNode->next_sibling());
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
bool XMLElement::SetName(const std::string& elementName)
{
	if (mNode != nullptr)
	{
		if (elementName.size() > 0)
		{
			//Allocate the string
			if (mNode->document() != nullptr)
			{
				char* newName = mNode->document()->allocate_string(
					elementName.c_str(),
					elementName.size());

				mNode->name(newName, elementName.size());

				return true;
			}
		}
	}

	return false;
}

//------------------------------------------//
// XMLElement::SetValue				
//------------------------------------------//
bool XMLElement::SetValue(const std::string& elementValue)
{
	if (mNode != nullptr)
	{
		if (elementValue.size() > 0)
		{
			//Allocate the string
			if (mNode->document() != nullptr)
			{
				char* newVal = mNode->document()->allocate_string(
					elementValue.c_str(),
					elementValue.size());

				mNode->value(newVal, elementValue.size());

				return true;
			}
		}
	}

	return false;
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

//------------------------------------------//
// XMLElement::IsValid				
//------------------------------------------//
bool XMLElement::IsValid() const
{
	return mNode != nullptr;
}
