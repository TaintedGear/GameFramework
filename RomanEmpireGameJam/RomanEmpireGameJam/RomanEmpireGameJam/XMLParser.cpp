#include "XMLParser.h"



XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
}

//------------------------------------------//
// XMLParser::Parse				
//------------------------------------------//
bool XMLParser::Parse(File& xmlFile)
{
	//Check if the file is an XML File
	if (xmlFile.GetFileExtension() != "xml")
	{
		//Not of ext 'XML'
		return false;
	}
	
	//Clear DOM tree
	mDOMTree.clear();

	//Read file contents
	std::string fileContents = "";
	if (!xmlFile.ReadFileContents(fileContents))
	{
		//Failed to read file contents
		return false;
	}

	//Parse 
	mDOMTree.parse<0>(&fileContents[0]);

	// - DEBUG
	//rapidxml::parse_error::what();
	//rapidxml::parse_error::where();
}

//------------------------------------------//
// XMLParser::GetElement				
//------------------------------------------//
XMLElement XMLParser::GetElement(const std::string& elementTag)
{
	rapidxml::xml_node<>* node = mDOMTree.first_node(elementTag.c_str());

	XMLElement xmlElement(node);

	return xmlElement;
}

