/***************************************************************************
 *           ____                                                          *
 *        ,'' _,-`.                                                        *
 *      ,'  ,'_|                                                           *
 *     /   / <>|             Lunacy (C) 2009                               *
 *    :   :    \             Version: 1.0                                  *
 *    :   :    _\            Written by: Johnny Starr                      *
 *     \   \  -|             File: lua_roomlib.c                           *
 *      `.  `._|             Desc: Lua library file for Rooms              *
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
