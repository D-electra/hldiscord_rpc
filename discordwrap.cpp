#include "discordwrap.h"

#define _PRESENCE _OBJ( \
		_BYTES          \
		_BYTES          \
		_I64            \
		_I64            \
		_BYTES          \
		_BYTES          \
		_BYTES          \
		_BYTES          \
		_BYTES          \
		_I32            \
		_I32            \
		_BYTES          \
		_BYTES          \
		_BYTES          \
		_I8)

#define _HANDLERS _OBJ(                            \
		_FUN(_VOID, _BYTES _BYTES _BYTES _BYTES)  \
		_FUN(_VOID, _I32 _BYTES)                  \
		_FUN(_VOID, _I32 _BYTES)                  \
		_FUN(_VOID, _BYTES)                       \
		_FUN(_VOID, _BYTES)                       \
		_FUN(_VOID, _BYTES _BYTES _BYTES _BYTES))

DEFINE_PRIM(_VOID, initialize, _BYTES _HANDLERS _I32 _BYTES)
DEFINE_PRIM(_VOID, shutdown, _NO_ARG)

DEFINE_PRIM(_VOID, run_callbacks, _NO_ARG)

DEFINE_PRIM(_VOID, update_presence, _PRESENCE)
DEFINE_PRIM(_VOID, clear_presence, _NO_ARG)

DEFINE_PRIM(_VOID, respond, _BYTES _I32)
DEFINE_PRIM(_VOID, update_handlers, _HANDLERS)