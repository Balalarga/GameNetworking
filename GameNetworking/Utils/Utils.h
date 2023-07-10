#pragma once
#include <algorithm>


template<class T>
T&& moveTemp(T& x)
{
	return std::move(x);
}
