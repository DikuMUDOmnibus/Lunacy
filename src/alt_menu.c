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

/* Local Prototypes */
void menu_medit( CHAR_DATA *ch, char *argument );
void menu_oedit( CHAR_DATA *ch, char *argument );
void menu_redit( CHAR_DATA *ch, char *argument );


void menu_medit( CHAR_DATA *ch, char *argument )
{
	call_lua (ch->L, ch, NULL, LCALL_CHAR_SCRIPT, "olcMedit", argument);
}

void menu_oedit( CHAR_DATA *ch, char *argument ) {}
void menu_redit( CHAR_DATA *ch, char *argument ) {}

bool alt_menu( DESCRIPTOR_DATA *d )
{
	switch( d->alt_menu ) {
		case AM_MEDIT:
			menu_medit(d->character, d->incomm);
		return TRUE;


		default:
		return FALSE;
	}
}








