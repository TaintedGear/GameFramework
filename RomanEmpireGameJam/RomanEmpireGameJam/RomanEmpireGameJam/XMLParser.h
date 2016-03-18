#pragma once

#include "File.h"
#include "rapidxml.hpp"

//XMLAttribute
class XMLAttribute
{
public:
	XMLAttribute(rapidxml::xml_attribute<>* attribute);

	const std::string GetName() const;
	const std::string GetValue() const;
	XMLAttribute GetNextAttribute();
	XMLAttribute GetPreviousAttribute();

	void SetValue(const std::string& attributeValue);

	class rapidxml::xml_attribute<>* GetRapidXMLAttribute();
private:
	class rapidxml::xml_attribute<>* mAttribute;
};

// XMLElement
class XMLElement
{
public:
	XMLElement(rapidxml::xml_node<>* node);

	void AddChildElement(XMLElement& childElement);
	void AddAttribute(class XMLAttribute& newAttribute);
	void AppendAttribute(class XMLAttribute& appendAttribute);

	const std::string GetName() const;
	const std::string GetValue() const;
	XMLElement GetFirstChildElement() const;
	XMLElement GetLastChildElement() const;
	class XMLAttribute GetFirstAttribute() const;
	class XMLAttribute GetLastAttribute() const;
	class std::vector<class XMLAttribute> GetAllAttributes() const;

	void SetValue(const std::string& elementValue);

	class rapidxml::xml_node<>* GetRapidXMLNode();
private:
	class rapidxml::xml_node<>* mNode;
};

// XML Parser
class XMLParser
{
public:
	XMLParser();
	~XMLParser();

	bool Parse(class File& xmlFile);
	class XMLElement GetFirstElement();
	//class XMLElement FindFirstElementWithTag(const std::string& elementTag);
	class XMLElement GetLastElement();

private:
	class rapidxml::xml_document<> mDOMTree;
	std::string mContents;
};

