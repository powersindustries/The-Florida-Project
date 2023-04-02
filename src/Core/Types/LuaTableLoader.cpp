#include "LuaTableLoader.h"
#include "../Systems/Logging.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
LuaTableLoader::LuaTableLoader(const std::string sFilePath)
	: m_LuaState(nullptr)
{
	m_LuaState = luaL_newstate();
	luaL_openlibs(m_LuaState);

	if (!CheckLuaStatus(m_LuaState, luaL_dofile(m_LuaState, sFilePath.c_str())))
	{
		std::string errorMessage = "Input Lua File was not able to load: ";
		errorMessage.append(sFilePath);
		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage.c_str());
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
LuaTableLoader::~LuaTableLoader()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
bool LuaTableLoader::LoadTableByID(std::string sTableID)
{
	lua_getglobal(m_LuaState, sTableID.c_str());
	return lua_istable(m_LuaState, -1);
}


// -------------------------------------------------------
// -------------------------------------------------------
std::string LuaTableLoader::GetStringByID(std::string sID)
{
	std::string output = "";

	// If top stack element is a table, get value and manage table.
	if (lua_istable(m_LuaState, -1))
	{
		lua_pushstring(m_LuaState, sID.c_str());
		lua_gettable(m_LuaState, -2);

		output = static_cast<std::string>(lua_tostring(m_LuaState, -1));

		PopTopTableElement();
	}

	return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
int LuaTableLoader::GetIntByID(std::string sID)
{
	int output = 0;

	// If top stack element is a table, get value and manage table.
	if (lua_istable(m_LuaState, -1))
	{
		lua_pushstring(m_LuaState, sID.c_str());
		lua_gettable(m_LuaState, -2);

		output = static_cast<int>(lua_tointeger(m_LuaState, -1));

		PopTopTableElement();
	}

	return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
uint8_t LuaTableLoader::GetCurrentTableSize()
{
	return static_cast<uint8_t>(lua_rawlen(m_LuaState, -1));
}


// -------------------------------------------------------
// -------------------------------------------------------
bool LuaTableLoader::PushIntegerAndGetTable(const int iIndex)
{
	lua_pushinteger(m_LuaState, iIndex);

	lua_gettable(m_LuaState, -2);

	return lua_type(m_LuaState, -1) == LUA_TNIL;
}


// -------------------------------------------------------
// -------------------------------------------------------
void LuaTableLoader::PopTopTableElement()
{
	lua_pop(m_LuaState, 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
bool LuaTableLoader::CheckLuaStatus(lua_State* luaState, int iIndex)
{
	if (iIndex != LUA_OK)
	{
		std::string errorMessage = lua_tostring(luaState, -1);
		std::cout << errorMessage << std::endl;
		return false;
	}

	return true;
}

}