#include "parser.h"

Parser::Parser(const std::string& fileName)
{
    luaState = luaL_newstate();
    if(luaL_loadfile(luaState, fileName.c_str()) || lua_pcall(luaState, 0, 0, 0))
    {
        std::cout << "Error: script not loaded (" << fileName << ")" << std::endl;
        luaState = 0;
    }
    luaL_dofile(luaState, fileName.c_str());
    luaL_openlibs(luaState);
}

Parser::~Parser()
{
    if(luaState)
        lua_close(luaState);
}

bool Parser::getBool(const std::string& section, const std::string& key)
{
    LuaRef sec = getGlobal(luaState, section.c_str());
    LuaRef b = sec[key.c_str()];
    if(!b.isNil() && b.isNumber())
    {
        return b.cast<bool>();
    }
    return false;
}

int Parser::getInt(const std::string& section, const std::string& key)
{
    LuaRef sec = getGlobal(luaState, section.c_str());
    LuaRef n = sec[key.c_str()];
    if(!n.isNil() && n.isNumber())
    {
        return n.cast<int>();
    }
    return 0;
}

std::string Parser::getString(const std::string& section, const std::string& key)
{
    LuaRef sec = getGlobal(luaState, section.c_str());
    LuaRef s = sec[key.c_str()];
    if(!s.isNil() && s.isString())
    {
        return s.cast<std::string>();
    }
    return "";
}

sf::Keyboard::Key Parser::getKey(const std::string& section, const std::string& key)
{
    LuaRef sec = getGlobal(luaState, section.c_str());
    LuaRef k = sec[key.c_str()];
    if(!k.isNil() && k.isNumber())
    {
        return (sf::Keyboard::Key)k.cast<int>();
    }
    return (sf::Keyboard::Key)0;
}

LuaRef Parser::getSection(const std::string& section)
{
    LuaRef sec = getGlobal(luaState, section.c_str());
    return sec;
}

void Parser::doTheThing()
{
    lua_State* L = luaL_newstate();
    luaL_dofile(L, "script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}

