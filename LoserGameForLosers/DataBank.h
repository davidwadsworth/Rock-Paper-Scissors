#pragma once
#include <vector>

struct DataBatch
{


};

struct DataID
{
	unsigned int UID;
	std::string data_id;
	DataBatch * loaded_batch;

};

class DataBank
{ 
	std::vector<DataBatch * > loadedBatches;
	std::vector<DataID> data_ids;
	unsigned int UID_Count;
	std::vector<std::string> file_source;
public:
	DataBank() : UID_Count(0) {}
	~DataBank() {}

	void print_ids()
	{
		for (auto id : data_ids)
		{
			std::cout << "data id : " << id.data_id << ", UID : " << id.UID << std::endl;
		}
	}

	void load_data_ids(const char * file);
	std::vector<DataBatch *> grab_batch(std::string id_match);
	unsigned int get_UID()
	{
		UID_Count++;
		return UID_Count - 1;
	}
};