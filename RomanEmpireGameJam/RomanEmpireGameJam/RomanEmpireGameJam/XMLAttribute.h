#pragma once

#include "PCH.h"
#include "rapidxml.hpp"

class XMLAttribute
{
public:
	XMLAttribute(rapidxml::xml_attribute<>* attribute);

	const std::string& GetName() const;
	const std::string& GetValue() const;
	XMLAttribute GetNextAttribute();
	XMLAttribute GetPreviousAttribute();

	void SetValue(const std::string& attributeValue);

	class rapidxml::xml_attribute<>* GetRapidXMLAttribute();
private:
	class rapidxml::xml_attribute<>* mAttribute;
};