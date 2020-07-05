#pragma once

#include <iostream>
#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

class LuaManager {
private:
	static void CreateLuaState();
	static void OpenLuaLibs();
	static bool LogError(int stackLocation);
public:
	static lua_State* LuaState;

	static void Init();
	static bool LoadFile(const char* fileLoction);
	void SetGlobals();
	//static lua_Number GetGlobalVariable(const char* globalVariable, bool popStack = true);
	//static double GetGlobalVariable(const char* globalVariable, bool popStack = true);
	//static float GetGlobalVariableAsFloat(const char* globalVariable, bool popStack = true);
	//static void ExecuteLuaFunction(const char* funcName);
	static void Destroy();
};