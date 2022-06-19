#pragma once
#include "../utils/Singleton.h"
#include <Windows.h>
#include <stdio.h>

template <typename T>
class Hack : public Singleton<T>
{
protected:
	virtual bool ShouldRun()
	{
		return true;
	}

	virtual void RunInternal() = 0;

public:
	void Run()
	{
		if (ShouldRun())
			RunInternal();
	}
};

template <typename T>
class KeybindHack : public Hack<T>
{
protected:
	inline virtual int Keybind() = 0;

	virtual bool ShouldRun() override
	{
		return GetAsyncKeyState(Keybind());
	}
};
