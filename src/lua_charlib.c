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


/* L_getchar() retreives pointer from stack and returns pointer */
CHAR_DATA *L_getchar( lua_State *L )
{
	CHAR_DATA **ch = (CHAR_DATA **)lua_touserdata(L, 1);
	CHAR_DATA *fch;
	if(ch) {
		fch = *ch;
		return fch;	
	}
	else 
		return NULL;
}

/* ------------------------ character library ------------------------- */

static int CHL_send( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	if (ch)
    	sendf(ch, "%s\r\n", luaL_checkstring(L, 2));
    return 0;
}

static int CHL_goTo( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	char *argument = str_dup(luaL_checkstring(L, 2));
	do_goto(ch, (char*)argument);
	free_string(argument);
	return 0;
}

static int CHL_say( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	char *argument = str_dup(luaL_checkstring(L, 2));
	do_say(ch, argument);
	free_string(argument);
	return 0;
}

static int CHL_act( lua_State *L )
{
	CHAR_DATA *p, *p_next;
	CHAR_DATA *ch = L_getchar(L);
	const char *argument = lua_tostring(L, 2);
	int type = lua_tointeger(L, 3);
 
	for ( p = ch->in_room->people; p != NULL; p = p_next ) {
	
		p_next = p->next_in_room;
			
		switch(type) {
			case TO_ROOM:
			if (!(ch == p))
				send_to_char(argument, p);
			break;
		}
	}

	return 0;
}

static int CHL_force( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	char *argument = str_dup(lua_tostring(L, 2));
	do_force(ch, argument);
	free_string(argument);
	return 0;
}

static int CHL_quitOlc( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	if (ch->desc)
		ch->desc->alt_menu = AM_NONE;
	return 0;
}
/* ----------------------- end character library ---------------------- */

int L_set_ch_field (CHAR_DATA *ch, const char *field, const char *value)
{
	if      ( !str_cmp(field, "name"  )) CHV_SETSTRING(ch, name, value);            
	else if ( !str_cmp(field, "title" )) CHV_SETSTRING(ch, pcdata->title, value); 
	else if ( !str_cmp(field, "short" )) CHV_SETSTRING(ch, short_descr, value);
	else if ( !str_cmp(field, "long"  )) CHV_SETSTRING(ch, long_descr, value);
	else if ( !str_cmp(field, "desc"  )) CHV_SETSTRING(ch, description, value);
	else if ( !str_cmp(field, "level" )) CHV_SETNUMBER(ch, level, value);            
	return 0;
}

static int CHL_newindex( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);
	int err = 0;
	const char *field = luaL_checkstring(L, 2);
	const char *value = luaL_checkstring(L, 3);	
	err = (L_set_ch_field(ch, field, value));

	if (err)
		errorL("missing field");

	return 1;
}

/* overrides Lua's __index() method, a "get" method for character properties and functions */
static int CHL_index( lua_State *L )
{
	CHAR_DATA *ch = L_getchar(L);

	if (!ch) {
		errorL("Honkey Grandma be Trippin'");
		return 0;
	}

	int a = 0;
	const char *prop = lua_tostring(L, 2);

	/* define character properties and send to Lua */
	if (!str_cmp(prop, "name"      )) lua_pushstring  (L, ch->name        ); a = 1;
	if (!str_cmp(prop, "short"     )) lua_pushstring (L, ch->short_descr ); a = 1;
	if (!str_cmp(prop, "long"      )) lua_pushstring  (L, ch->long_descr  ); a = 1;
	if (!str_cmp(prop, "desc"      )) lua_pushstring  (L, ch->description ); a = 1;
	if (!str_cmp(prop, "level"     )) lua_pushinteger (L, ch->level       ); a = 1;
	if (!str_cmp(prop, "exp"       )) lua_pushinteger (L, ch->exp         ); a = 1;
	if (!str_cmp(prop, "align"     )) lua_pushinteger (L, ch->alignment   ); a = 1;
	if (!str_cmp(prop, "gold"      )) lua_pushinteger (L, ch->gold        ); a = 1; 
	if (!str_cmp(prop, "hit"       )) lua_pushinteger (L, ch->hit         ); a = 1;

	/* define player properties and send to Lua */
	if (ch->pcdata) {
	if (!str_cmp(prop, "title"  )) lua_pushstring    (L, ch->pcdata->title   ); a = 1;
	if (!str_cmp(prop, "permStr")) lua_pushinteger   (L, ch->pcdata->perm_str); a = 1;
	}

	/* define character functions and send to Lua */
	if (!str_cmp(prop, "send"     )) lua_pushcfunction (L, CHL_send  ); a = 1;		
	if (!str_cmp(prop, "goTo"     )) lua_pushcfunction (L, CHL_goTo  ); a = 1;
	if (!str_cmp(prop, "say"      )) lua_pushcfunction (L, CHL_say   ); a = 1;
	if (!str_cmp(prop, "act"      )) lua_pushcfunction (L, CHL_act   ); a = 1;
	if (!str_cmp(prop, "force"    )) lua_pushcfunction (L, CHL_force ); a = 1;
	if (!str_cmp(prop, "quitOlc"  )) lua_pushcfunction (L, CHL_quitOlc ); a = 1;

	/* if no prop is found, raise error and return 0 */
	if (!a) {
		luaL_error(L, "%s: could not find property %s in CHAR_DATA structure.", 
			__FUNCTION__, prop );
	}

	return a;
}

/* registry for charlib_m (metatable) */
static const struct luaL_reg charlib_m [] = {	
	{"__newindex", CHL_newindex},
	{"__index",    CHL_index},
    {NULL, NULL}
};


void L_register_charlib( lua_State *L )	
{
	luaL_register(L, NULL, charlib_m);
}
