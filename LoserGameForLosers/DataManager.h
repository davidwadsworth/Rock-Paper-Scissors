#pragma once
#include "ECS.h"
#include "Data.h"

class LoadData;
class DataManager;

using LoadDataID = std::size_t;

inline LoadDataID getNewLoadDataTypeID()
{
	static LoadDataID last_id = 0u;
	return last_id++;
}

template <typename T> inline LoadDataID getLoadDataTypeID() noexcept
{
	static_assert(std::is_base_of<LoadData, T>::value, "");
	static LoadDataID type_id = getNewLoadDataTypeID();
	return type_id;
}

constexpr std::size_t maxLoadData = 32;

using LoadDataBitSet = std::bitset<maxLoadData>;

using LoadDataArray = std::array<LoadData*, maxLoadData>;

class LoadData
{
public:
	std::string path;

	explicit LoadData(const std::string path)
		: path(path)
	{}

	virtual ~LoadData() = default;
};



class DataManager
{
	LoadDataArray load_array_;
	LoadDataBitSet load_bit_set_;
public:
	DataManager()
	{}

	~DataManager() = default;

	template <typename T> bool is_loaded() const
	{
		return load_bit_set_[getLoadDataTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& load_data(TArgs&&... m_args)
	{
		T* d(new T(std::forward<TArgs>(m_args)...));

		load_array_[getLoadDataTypeID<T>()] = d;
		load_bit_set_[getLoadDataTypeID<T>()] = true;

		return *d;
	}

	template<typename T> T& get_load() const
	{
		auto ptr(load_array_[getLoadDataTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};
