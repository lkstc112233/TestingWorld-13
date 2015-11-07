#pragma once

extern const double PI;

template<typename T>
T changeAndReturnValue(T &source, T value)
{
	T temp = source;
	source = value;
	return temp;
}

template <class T>
std::string ConvertToString(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}