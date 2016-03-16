#pragma once

#include "File.h"
#include "rapidxml.hpp"

#include "XMLElement.h"

// XML Parser
class XMLParser
{
public:
	XMLParser();
	~XMLParser();

	bool Parse(class File& xmlFile);
	class XMLElement GetElement(const std::string& elementTag);

private:
	class rapidxml::xml_document<> mDOMTree;
};

