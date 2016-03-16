#include "XMLAttribute.h"

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
const std::string& XMLAttribute::GetName() const
{
	return mAttribute->name();
}

//------------------------------------------//
// XMLAttribute::GetValue				
//------------------------------------------//
const std::string& XMLAttribute::GetValue() const
{
	return mAttribute->value();
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
	XMLAttribute nextAttribute(mAttribute->previous_attribute());
	return nextAttribute;
}

//------------------------------------------//
// XMLAttribute::GetRapidXMLAttribute				
//------------------------------------------//
class rapidxml::xml_attribute<>* XMLAttribute::GetRapidXMLAttribute()
{
	return mAttribute;
}