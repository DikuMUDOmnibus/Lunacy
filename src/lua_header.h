#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define CHV_SETSTRING(ch, field, value) (ch->field = str_dup(value))
#define CHV_SETNUMBER(ch, field, value) (ch->field = atoi(value))    

/* lua_interface.c */
void errorL (char *fmt, ...);
void L_stack_dump( lua_State *L );

/* lua_charlib.c */
void L_register_charlib( lua_State *L );
/* lua_mudlib.c */
void L_register_mudlib ( lua_State *L );
