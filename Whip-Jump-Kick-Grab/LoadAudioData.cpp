#include "stdafx.h"
#include "LoadAudioData.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>

AudioCollection LoadAudioData::load()
{
	xml_path.open(path);

	buffer.assign((std::istreambuf_iterator<char>(xml_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	const auto audio_collection_node = data.first_node("AudioCollection");

	audio_collection_.id = audio_collection_node->first_attribute("id")->value();
	audio_collection_.path = audio_collection_node->first_attribute("path")->value();

	for (auto audio_node = audio_collection_node->first_node("Audio"); audio_node; audio_node = audio_node->next_sibling())
	{
		auto audio_data = AudioData();
		audio_data.path = audio_node->first_attribute("path")->value();
		audio_data.encoding = atoi(audio_node->first_attribute("encoding")->value());

		audio_collection_.data.push_back(audio_data);
	}

	data.clear();
	return audio_collection_;
}
