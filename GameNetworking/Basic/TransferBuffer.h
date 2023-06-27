#pragma once
#include <vector>


class TransferBuffer: public std::vector<uint8_t>
{
public:
	using vector::vector;

	template<class T>
	TransferBuffer& operator<<(const T& data)
	{
		auto dest = end();
		resize(size() + sizeof(T));
		std::memcpy(dest, &data, sizeof(T));
		return *this;
	}

	template<class T>
	TransferBuffer& operator>>(T& data)
	{
		std::memcpy(&data, end() - sizeof(T), sizeof(T)); // TODO: reverse reading order
		resize(size() - sizeof(T));
		return *this;
	}
};
