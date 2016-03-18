#include "XMLParser.h"

//------------------------------------------//
// XMLAttribute::XMLAttribute				
//------------------------------------------//
XMLAttribute::XMLAttribute(rapidxml::xml_attribute<>* attribute) :
mAttribute(attribute)
{
}

//------------------------------------------//
// XMLAttribute::GetName				
//------------------------------------------//
const std::string XMLAttribute::GetName() const
{
	return mAttribute != nullptr ? mAttribute->name() : "Null";
}

//------------------------------------------//
// XMLAttribute::GetValue				
//------------------------------------------//
const std::string XMLAttribute::GetValue() const
{
	return mAttribute != nullptr ? mAttribute->value() : "Null";
}

//------------------------------------------//
// XMLAttribute::GetNextAttribute				
//------------------------------------------//
XMLAttribute XMLAttribute::GetNextAttribute()
{
	XMLAttribute nextAttribute(mAttribute->next_attribute());
	return nextAttribute;
}

//------------------------------------------//
// XMLAttribute::GetPreviousAttribute				
//------------------------------------------//
XMLAttribute XMLAttribute::GetPreviousAttribute()
{
	XMLAttribute prevAttribute(mAttribute->previous_attribute());
	return prevAttribute;
}

//------------------------------------------//
// XMLAttribute::GetRapidXMLAttribute				
//------------------------------------------//
class rapidxml::xml_attribute<>* XMLAttribute::GetRapidXMLAttribute()
{
	return mAttribute;
}