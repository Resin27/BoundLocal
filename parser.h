#ifndef PARSER_H
#define PARSER_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include <LuaBridge.h>
extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace luabridge;

///Class
class Parser
{
protected:

    lua_State* luaState;

public:

    Parser(const std::string& fileName);
    ~Parser();

    bool getBool(const std::string& section, const std::string& key);
    int getInt(const std::string& section, const std::string& key);
    sf::Keyboard::Key getKey(const std::string& section, const std::string& key);
    std::string getString(const std::string& section, const std::string& key);

    void doTheThing();
};

#endif


