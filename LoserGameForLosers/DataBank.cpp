#include "stdafx.h"
#include "DataBank.h"

//Make this available to all classes
std::string int_to_id(int id) { return id / 10 + "" + id % 10;}


void DataBank::load_data_ids(const char * file)
{
	std::ifstream data_path(file);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * root_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(data_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	root_node = data.first_node();

	file_source.push_back(file);

	for (rapidxml::xml_node<> * obscure_node = root_node->first_node(); obscure_node; obscure_node = obscure_node->next_sibling())
	{
		auto data_id = new DataID();
		data_id->UID = get_UID();
		data_id->data_id = int_to_id(file_source.size() - 1) + obscure_node->first_attribute()->value();
	}
}

std::vector<DataBatch*> DataBank::grab_batch(std::string id_match)
{
	return std::vector<DataBatch*>();
}
