#pragma once
#include <iostream>


extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


namespace Core
{

class LuaTableLoader
{
public:

	LuaTableLoader(const std::string sFilePath);
	~LuaTableLoader();

	// Load an entire table by name.
	// Returns false if load fails.
	bool LoadTableByID(std::string sTableID);

	// Get the std::string value by key.
	std::string GetStringByID(std::string sID);

	// Get the int value by key. 
	int GetIntByID(std::string sID);

	// Returns false if the pushed value is NULL.
	bool PushIntegerAndGetTable(const int iIndex);

	// Remove the first element of the table.
	void PopTopTableElement();

	uint8_t GetCurrentTableSize();


private:

	bool CheckLuaStatus(lua_State* luaState, int iIndex);


private:

	lua_State* m_LuaState;

};
}