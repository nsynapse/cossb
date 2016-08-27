
#include "profile.hpp"
#include <iostream>
#include <cstring>
#include <base/common.hpp>
#include <interface/icomponent.hpp>

using namespace std;

namespace cossb {
namespace profile {

xml::xml(){
}

xml::~xml() {
	if(_doc)
		delete _doc;
}

bool xml::load(interface::icomponent* pComponent, const char* filepath)
{
	if(_doc!=nullptr)
	{
		delete _doc;
		_doc = nullptr;
	}

	_doc = new tinyxml2::XMLDocument;
	if(_doc->LoadFile(filepath)==XML_SUCCESS) {
		read_services(pComponent);
		_loaded = true;
	}
	else
		_loaded = false;

	return _loaded;
}

const char* xml::get_error_str(int error) const
{
	switch(error)
	{
	case	XML_NO_ATTRIBUTE: 						return "No Attribute"; 		break;
	case	XML_WRONG_ATTRIBUTE_TYPE: 				return "Wrong attribute type";	break;
	case	XML_ERROR_FILE_NOT_FOUND: 				return "Cannot found profile";	break;
	case	XML_ERROR_FILE_COULD_NOT_BE_OPENED: 	return "Profile could not be loaded";	break;
	case	XML_ERROR_ELEMENT_MISMATCH: 			return "Element mismatch";	break;
	case	XML_ERROR_PARSING_ELEMENT: 				return "Parsing element";	break;
	case	XML_ERROR_PARSING_ATTRIBUTE: 			return "Parsing attribute";	break;
	case	XML_ERROR_IDENTIFYING_TAG: 				return "Identifying tag";	break;
	case	XML_ERROR_PARSING_TEXT: 				return "Parsing text";	break;
	case	XML_ERROR_PARSING_CDATA: 				return "Parsing CDATA";	break;
	case	XML_ERROR_PARSING_COMMENT: 				return "Parsing comment";	break;
	case	XML_ERROR_PARSING_DECLARATION: 		return "Parsing declaration";	break;
	case	XML_ERROR_PARSING_UNKNOWN: 				return "Parsing unknown";	break;
	case	XML_ERROR_EMPTY_DOCUMENT: 				return "Empty document";	break;
	case	XML_ERROR_MISMATCHED_ELEMENT: 			return "Mismatched element";	break;
	case	XML_ERROR_PARSING: 						return "Parsing Error";	break;
	}

	return "";
}

profile::type_value xml::get(profile::section section, const char* element)
{
	profile::type_value result;
	string section_name = "";
	bool exist = false;

	switch(section)
	{
	case profile::section::info:		section_name = "info"; 		exist = true;	break;
	case profile::section::property:	section_name = "property";	exist = true;	break;
	case profile::section::resource:	section_name = "resource";	exist = true;	break;
	case profile::section::service:	section_name = "service";	exist = true; break;
	default:	{ section_name = "unknown"; exist = false; }
	}


	if(_loaded && exist && _doc->FirstChildElement(section_name.c_str())!=0)
	{
		if(_doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)!=0)
		{
			XMLNode* _node = _doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)->FirstChild();
			if(_node)
				set(result, _node->ToText()->Value());
		}
	}

	return result;
}
/*vector<string> xml::gets(profile::section section, const char* element)
{
	vector<string> selections;

	return selections;
}*/

vector<profile::type_value> xml::gets(profile::section section, const char* element)
{
	vector<profile::type_value> valuelist;

	profile::type_value result;
	string section_name = "";
	bool exist = false;

	switch(section)
	{
	case profile::section::info:		section_name = "info"; 		exist = true;	break;
	case profile::section::property:	section_name = "property";	exist = true;	break;
	case profile::section::resource:	section_name = "resource";	exist = true;	break;
	case profile::section::service:	section_name = "service";	exist = true; break;
	default:	{ section_name = "unknown"; exist = false; }
	}

	if(_loaded && exist && _doc->FirstChildElement(section_name.c_str())!=0) {
		for(XMLElement* elem = _doc->FirstChildElement(section_name.c_str())->FirstChildElement(element);
				elem!=nullptr; elem = elem->NextSiblingElement(element)) {
			valuelist.push_back(profile::type_value(elem->FirstChild()->ToText()->Value()));
		}
	}


	/*if(_loaded && exist && _doc->FirstChildElement(section_name.c_str())!=0)
	{
		if(_doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)!=0)
		{
			XMLNode* _node = _doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)->FirstChild();
			if(_node)
				set(result, _node->ToText()->Value());
		}
	}

	for(XMLElement* elem = _doc->FirstChildElement(__SERVICE__);elem!=nullptr; elem = elem->NextSiblingElement(__SERVICE__))
	{
		service::service_desc desc;
		if(elem->Attribute("method")) desc.method = elem->Attribute("method");
		if(elem->Attribute("topic")) desc.topic = elem->Attribute("topic");

		this->add(desc);
	}*/

	return valuelist;
}

/*profile::type_value xml::get_attribute(profile::section section, const char* element, const char* attr)
{

}*/


bool xml::update(profile::section section, const char* element, const char* value)
{
	bool exist = false;

	string section_name = "";
	switch(section)
	{
	case profile::section::property:	section_name = "property";	exist = true;	break;	//property only editable
	default: { section_name="unknown"; exist=false; }
	}

	if(_loaded && exist && _doc->FirstChildElement(section_name.c_str())!=0)
	{
		if(_doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)!=0)
		{
			XMLNode* pNode = _doc->FirstChildElement(section_name.c_str())->FirstChildElement(element)->FirstChild();
			if(pNode){
				pNode->SetValue(value);
				return true;
			}
		}
	}

	return false;
}

bool xml::save()
{
	if(_loaded) {
		_doc->SaveFile(_filepath.c_str());
		return true;
	}

	return false;
}

void xml::read_services(interface::icomponent* pComponent)
{
	//read service desc.
	for(XMLElement* elem = _doc->FirstChildElement(__SERVICE__);elem!=nullptr; elem = elem->NextSiblingElement(__SERVICE__))
	{
		service::service_desc desc;
		if(elem->Attribute("method")) desc.method = elem->Attribute("method");
		if(elem->Attribute("topic")) desc.topic = elem->Attribute("topic");
		if(elem->Attribute("name")) desc.name = elem->Attribute("name");
		desc.component_name = pComponent->get_name();

		this->add(desc);
	}
}


} /* namespace profile */
} /* namespace cossb */
