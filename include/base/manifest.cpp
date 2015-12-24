/**
 * @file		configreader.CPP
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#include "manifest.hpp"
#include <algorithm>

namespace cossb {
namespace base {

manifestreader::manifestreader()
{

}
manifestreader::~manifestreader()
{
	if(!_required.empty())
	{
		for(auto itr:_required)
			delete itr;
	}

	if(_doc)
		delete _doc;
}

bool manifestreader::load(const char* manifest_file)
{
	if(_doc)
		return false;

	_doc = new tinyxml2::XMLDocument;
	if(_doc->LoadFile(manifest_file)==XML_SUCCESS)
	{
		read_info();
		read_required();
	}

	return true;
}

void manifestreader::read_info()
{
	XMLElement* section = _doc->FirstChildElement("manifest")->FirstChildElement("info");
	for(XMLElement* child = section->FirstChildElement();child!=nullptr; child = child->NextSiblingElement()) {
		_info[child->Value()] = child->GetText();
	}
}

void manifestreader::read_required()
{
	XMLElement* section = _doc->FirstChildElement("manifest");
	for(XMLElement* child = section->FirstChildElement("required");child!=nullptr; child = child->NextSiblingElement("required"))
	{
		string type = child->Attribute("type");
		std::transform(type.begin(), type.end(), type.begin(), ::tolower);

		if(!type.compare("component"))
			_required.push_back(new req_element(bundleType::COMPONENT, child->GetText()));
		else if(!type.compare("library"))
			_required.push_back(new req_element(bundleType::LIBRARY, child->GetText()));
		else if(!type.compare("package"))
			_required.push_back(new req_element(bundleType::PACKAGE, child->GetText()));
	}
}


void manifestreader::parse_path()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest")->FirstChildElement("property");
	for(XMLElement* child = elem_com->FirstChildElement("path");child!=nullptr; child = child->NextSiblingElement("path"))
		_path[child->Attribute("name")] = child->GetText();
}

void manifestreader::parse_repository()
{
	XMLElement* elem_uri = _doc->FirstChildElement("manifest")->FirstChildElement("repository");
	for(XMLElement* child = elem_uri->FirstChildElement("uri");child!=nullptr; child = child->NextSiblingElement("uri"))
		if(child->GetText())
			_repository.push_back(child->GetText());
}

void manifestreader::parse_product_info()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest")->FirstChildElement("product");
	for(XMLElement* child = elem_com->FirstChildElement();child!=nullptr; child = child->NextSiblingElement())
		_product[child->Value()] = child->GetText();
}

/*void configreader::parse_service()
{
	XMLElement* elem_com = _doc->FirstChildElement("manifest");
	for(XMLElement* child = elem_com->FirstChildElement("service");child!=nullptr; child = child->NextSiblingElement("service"))
		_service.insert(std::pair<string, string>(child->Attribute("name"), child->GetText()));
}*/

} /* namespace base */
} /* namespace cossb */
