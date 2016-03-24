#pragma once

#include "File.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

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

	XMLElement CreateChildElement(
		const std::string& elementName = "",
		const std::string& elementValue = "");

	const std::string GetName() const;
	const std::string GetValue() const;

	XMLElement GetFirstChildElement() const;
	bool GetAllChildElements(std::vector<XMLElement>& childElements);
	XMLElement GetLastChildElement() const;

	XMLElement GetSiblingElement() const;

	class XMLAttribute GetFirstAttribute() const;
	class XMLAttribute GetLastAttribute() const;
	std::vector<class XMLAttribute> GetAllAttributes() const;

	bool SetName(const std::string& elementName);
	bool SetValue(const std::string& elementValue);

	bool IsValid() const;

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
	class XMLElement GetLastElement();
	
	class XMLElement CreateNewElement(
		const std::string& elementName = "",
		const std::string elementValue = "",
		bool autoInsert = true);

	bool InsertElement(class XMLElement& element);

	const std::string GetContents() const;

private:
	class rapidxml::xml_document<> mDOMTree;
	//std::string mContents;
};

