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
	std::string contents = "";
	if (!xmlFile.ReadFileContents(contents))
	{
		//Failed to read file contents
		return false;
	}

	//Safeguard against non null-terminated strings - by adding it in
	contents += '\0';

	//Allocate the string
	char* dataString = mDOMTree.allocate_string(contents.c_str(), contents.size());

	//Parse
	mDOMTree.parse<0>(&dataString[0]);

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

//------------------------------------------//
// XMLParser::CreateNewElement				
//------------------------------------------//
XMLElement XMLParser::CreateNewElement(
	const std::string& elementName,
	const std::string elementValue,
	bool autoInsert)
{
	rapidxml::xml_node<>* newNode = nullptr;

	//Allocate strings
	char* name = mDOMTree.allocate_string(elementName.c_str(), elementName.size());
	char* value = mDOMTree.allocate_string(elementValue.c_str(), elementValue.size());

	newNode = mDOMTree.allocate_node(
		rapidxml::node_element,
		name,
		value,
		elementName.size(),
		elementValue.size());

	XMLElement newElement(newNode);

	if (autoInsert)
	{
		XMLParser::InsertElement(newElement);
	}

	return newElement;
}

//------------------------------------------//
// XMLParser::GetContents				
//------------------------------------------//
const std::string XMLParser::GetContents() const
{
	//Get contets of the DOM tree
	std::string contents = "";
	rapidxml::print(std::back_inserter(contents), mDOMTree, 0);
	
	//Null terminate the string;
	contents += '\0';
	return contents;
}

//------------------------------------------//
// XMLParser::InsertElement				
//------------------------------------------//
bool XMLParser::InsertElement(class XMLElement& element)
{
	if (element.GetRapidXMLNode() == nullptr)
	{
		return false;
	}

	mDOMTree.insert_node(0, element.GetRapidXMLNode());
	return true;
}