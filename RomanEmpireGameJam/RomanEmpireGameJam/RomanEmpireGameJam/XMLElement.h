#pragma once

#include "PCH.h"
#include "rapidxml.hpp"

#include "XMLAttribute.h"

class XMLElement
{
public:
	XMLElement(rapidxml::xml_node<>* node);

	void AddChildElement(XMLElement& childElement);
	void AddAttribute(class XMLAttribute& newAttribute);
	void AppendAttribute(class XMLAttribute& appendAttribute);

	const std::string GetValue() const;
	XMLElement GetChildElement(const std::string& childElementTag) const;
	class XMLAttribute GetAttribute(const std::string& attributeTag);

	void SetValue(const std::string& elementValue);

	class rapidxml::xml_node<>* GetRapidXMLNode();
private:
	class rapidxml::xml_node<>* mNode;
};