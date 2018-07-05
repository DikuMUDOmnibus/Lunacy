/***************************************************************************
 *           ____                                                          *
 *        ,'' _,-`.                                                        *
 *      ,'  ,'_|                                                           *
 *     /   / <>|             Lunacy (C) 2009                               *
 *    :   :    \             Version: 1.0                                  *
 *    :   :    _\            Written by: Johnny Starr                      *
 *     \   \  -|             File: lua_charlib.c                           *
 *      `.  `._|             Desc: Lua library file for Characters         *
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
#include "lua_header.h"
#include "merc.h"
/*
 * Mudlib functions: ML
 * Used in the global lua_State as a call to the system: "mud.function()"
 */

/* sends a message to every player, used for testing */
static int ML_send(lua_State *L)
{
    CHAR_DATA *ch;
    for (ch = char_list; ch != NULL; ch = ch->next)
        if (!IS_NPC(ch))
            sendf(ch, "%s\r\n", luaL_checkstring(L, 1));
	
	log_string(luaL_checkstring(L, 1));

    return 0;
}

/* End of mudlib ----------------------------------------------------------*/




/* registry for mudlib */
static const struct luaL_reg mudlib [] = {
    {"send", ML_send},
    {NULL, NULL}
};

void L_register_mudlib( lua_State *L )	
{
	luaL_register(L, NULL, mudlib);
}
