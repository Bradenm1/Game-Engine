#include "LuaManager.h"

lua_State* LuaManager::LuaState;

void LuaManager::Init()
{
	CreateLuaState();
	OpenLuaLibs();
}

bool LuaManager::LoadFile(const char* fileLoction)
{
	assert(fileLoction != NULL);
	return LogError(luaL_dofile(LuaState, fileLoction));
}

void LuaManager::SetGlobals()
{
	
}

//lua_Number LuaManager::GetGlobalVariable(const char* globalVariable, bool popStack = true)
//{
//	lua_getglobal(LuaState, globalVariable);
//	lua_Number ln = lua_tonumber(LuaState, -1);
//	lua_pop(LuaState, 1);
//	return ln;
//}
//
//double LuaManager::GetGlobalVariable(const char* globalVariable, bool popStack = true)
//{
//	return GetGlobalVariable(globalVariable, popStack);
//}
//
//float LuaManager::GetGlobalVariableAsFloat(const char* globalVariable, bool popStack = true)
//{
//	return (float)GetGlobalVariable(globalVariable, popStack);
//}
//
//template<class T>
//void AddCustomFunction(T func, const char* funcName) {
//	lua_pushcfunction(LuaState, func);
//	lua_setglobal(LuaState, funcName);
//}
//
//void LuaManager::ExecuteLuaFunction(const char* funcName) {
//	lua_getglobal(LuaState, funcName);
//	lua_pcall(LuaState, 0, 0, 0);
//	lua_pop(LuaState, 1);
//}

void LuaManager::CreateLuaState()
{
	LuaState = luaL_newstate();
}

void LuaManager::OpenLuaLibs()
{
	luaL_openlibs(LuaState);
}

bool LuaManager::LogError(int state)
{
	if (state != 0)
	{
		std::cout << "Something went wrong loading the chunk (syntax error?)" << std::endl;
		std::cout << "ERR: " << lua_tostring(LuaState, state) << std::endl;
		lua_pop(LuaState, 1); //remove error
		return false;
	}
	return true;
}

void LuaManager::Destroy()
{
	lua_close(LuaState);
}