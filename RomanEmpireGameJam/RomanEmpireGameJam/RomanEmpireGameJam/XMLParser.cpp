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
	if (xmlFile.GetFileExtension() != ".xml")
	{
		//Not of ext 'XML'
		return false;
	}
	
	//Clear DOM tree
	mDOMTree.clear();

	//Read file contents
	mContents = "";
	if (!xmlFile.ReadFileContents(mContents))
	{
		//Failed to read file contents
		return false;
	}

	//Parse - Without Exceptions
	mDOMTree.parse<0>(&mContents[0]);

	// - DEBUG
	//rapidxml::parse_error::what();
	//rapidxml::parse_error::where();

	return true;
}

//------------------------------------------//
// XMLParser::GetElement				
//------------------------------------------//
XMLElement XMLParser::GetFirstElement()
{
	rapidxml::xml_node<>* node = mDOMTree.first_node();

	XMLElement xmlElement(node);

	return xmlElement;
}

//------------------------------------------//
// XMLParser::GetLastElement				
//------------------------------------------//
class XMLElement XMLParser::GetLastElement()
{
	rapidxml::xml_node<>* node = mDOMTree.last_node();

	XMLElement xmlElement(node);

	return xmlElement;
}