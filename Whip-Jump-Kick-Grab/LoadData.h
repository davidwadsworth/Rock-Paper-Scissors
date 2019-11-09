#pragma once
#include "rapidxml.hpp"
#include <fstream>

/**
 * @author David Wadsworth
 * 
 * Reads Xml data using rapidxml
 */

class LoadData
{
public:
	explicit LoadData(const std::string path)
		: path(path)
	{}
	LoadData& operator=(const LoadData&) = default;
	virtual ~LoadData() = default;

	std::string path;
	rapidxml::xml_document<> data;
	std::ifstream xml_path;
	std::vector<char> buffer;


};
