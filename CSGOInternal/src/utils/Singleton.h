#pragma once

template <typename T>
class Singleton
{
private:
	static T *s_Instance;

public:
	static T *GetInstance()
	{
		if (!s_Instance)
			s_Instance = new T();

		return s_Instance;
	}
};

template <typename T>
T *Singleton<T>::s_Instance = nullptr;
