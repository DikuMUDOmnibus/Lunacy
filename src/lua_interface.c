/***************************************************************************
 *           ____                                                          *
 *        ,'' _,-`.                                                        *
 *      ,'  ,'_|                                                           *
 *     /   / <>|             Lunacy (C) 2009                               *
 *    :   :    \             Version: 1.0                                  *
 *    :   :    _\            Written by: Johnny Starr                      *
 *     \   \  -|             File: lua_interface.c                         *
 *      `.  `._|             Desc: Main Lua interface for Lua scripting    *
 *        `..__`-.'                                                        *
 *                                                                         *
 ***************************************************************************
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "merc.h"
#include "lua_header.h"

/* global Lua state declaration, used for server calls to Lua */
lua_State *global_L;

/*
static void get_traceback_function ( lua_State *L )
{
	lua_pushliteral (L, LUA_DBLIBNAME);
	lua_rawget      (L, LUA_GLOBALSINDEX);

	if (!lua_istable (L, -1)) {
		lua_pop (L, 2);
		lua_pushnil (L);
		return;
	}

	lua_pushstring(L, "traceback");
	lua_rawget    (L, -2);

	if (!lua_isfunction (L, -1)) {
		lua_pop (L, 2);
		lua_pushnil(L);
		return;
	}

	lua_remove (L, -2);
}

*/

/* errorL() a general error message handler */
void errorL (char *fmt, ...)
{
    CHAR_DATA *ch;
    char buf[MAX_STRING_LENGTH];
    va_list args;
    va_start (args, fmt);
    vsprintf (buf, fmt, args);
    va_end (args);

    for (ch = char_list; ch != NULL; ch = ch->next)
        if (!IS_NPC(ch))
            sendf(ch, "%s\r\n", buf);
}

/* stack_dump() another testing function to view contents of stack */
void L_stack_dump( lua_State *L )
{

	int i;
	int top = lua_gettop(L);
	for ( i = 1; i <= top; i++ ) {
		int t = lua_type(L, i);
		switch(t) {
			case LUA_TSTRING:
				errorL("String: %s\r\n", lua_tostring(L, i));
			break;

			case LUA_TBOOLEAN:
				errorL(lua_toboolean(L, i) ? "true\r\n" : "false\r\n");
			break;

			case LUA_TNUMBER:
				errorL("Number: %g\r\n", lua_tostring(L, i));
			break;

			case LUA_TUSERDATA:
				errorL("Userdata: %s\r\n", lua_tostring(L, i));
			break;

			default:
				errorL("Other: %s\r\n", lua_tostring(L, i));
			break;
		}
	
	}
	errorL("\r\n");
}







/* constructs global lua_State* */
void load_global_lua(void)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
	luaL_newmetatable(L, "lunacy.ch");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
   	L_register_charlib(L); 
	L_register_mudlib(L);

    if (luaL_loadfile(L, "../lua/mud.lua") || lua_pcall(L, 0, 0, 0))
        errorL ("LUA-ERROR [%s: %s]\r\n", __FUNCTION__, lua_tostring(L, -1));
    if (luaL_loadfile(L, "../lua/player.lua") || lua_pcall(L, 0, 0, 0))
        errorL ("LUA-ERROR [%s: %s]\r\n", __FUNCTION__, lua_tostring(L, -1));
	/* global Lua state */
    global_L = L;

	lua_settop(L, 0);
}


/* constructs new lua_State* for character */
void load_char_lua( CHAR_DATA *ch )
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
 	
	luaL_newmetatable(L, "lunacy.ch");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	L_register_charlib(L);
    
	if (luaL_loadfile(L, "../lua/player.lua") || lua_pcall(L, 0, 0, 0))
        errorL ("LUA-ERROR [%s: %s]\r\n", __FUNCTION__, lua_tostring(L, -1));
	if (luaL_loadfile(L, "../lua/olc.lua") || lua_pcall(L, 0, 0, 0))
        errorL ("LUA-ERROR [%s: %s]\r\n", __FUNCTION__, lua_tostring(L, -1));
 	if (luaL_loadfile(L, "../lua/battle.lua") || lua_pcall(L, 0, 0, 0))
        errorL ("LUA-ERROR [%s: %s]\r\n", __FUNCTION__, lua_tostring(L, -1));   
	if (L)
        ch->L = L;
    else
        bug ("load_char_lua: bad lua state", 0);

	lua_settop(L, 0);
}

/* main lua interface. Hooks into lua and returns a char* string for output */
char* call_lua(lua_State *L, CHAR_DATA *actor, void *target, int call_type, char *func, char *argument)
{
    int err = 0;
    char *output = NULL;

    switch (call_type) {
        /* one text argument */
    case LCALL_CHAR_SCRIPT:
        lua_getglobal(L, func);                               /* stack: function ...                  */		
		CHAR_DATA **ptr = (CHAR_DATA **)lua_newuserdata( L,
										sizeof(CHAR_DATA**));
		*ptr = actor;
		luaL_getmetatable(L, "lunacy.ch");	
		lua_setmetatable(L, -2);                              /* stack: function(udata) ...           */
		lua_pushstring(L, argument);                          /* stack: function(udata, argument) ... */

        err = lua_pcall(L, 2, 1, 0);

        if (lua_isstring(L, -1))
            output = str_dup( lua_tostring(L, -1));
        else
            output = NULL;
        break;

	case LCALL_OLC:

        lua_getglobal(L, func);                               /* stack: function ...                  */		
		CHAR_DATA **ptr2 = (CHAR_DATA **)lua_newuserdata( L,
										sizeof(CHAR_DATA**));
		*ptr2 = actor;
		luaL_getmetatable(L, "lunacy.ch");	
		lua_setmetatable(L, -2);                              /* stack: function(udata) ...           */
		lua_pushstring(L, argument);                          /* stack: function(udata, argument) ... */

        err = lua_pcall(L, 3, 1, 0);

        if (lua_isstring(L, -1))
            output = str_dup( lua_tostring(L, -1));
        else
            output = NULL;
        break;

	case LCALL_COLOR:
		lua_getglobal(L, func);
		lua_pushstring(L, argument);
		err = lua_pcall(L, 1, 1, 0);
        if (lua_isstring(L, -1))
            output = str_dup( lua_tostring(L, -1));
        else
            output = NULL;

        break;

    default:
        bug("call_lua: bad call_type", 0);
    }

    if (err) {
        errorL ("#RLua Error: %s{w", lua_tostring(L, -1));
        return NULL;
    }

	lua_pop(L, 1);
    return (output);
}
