/* EIOTAS
 * Copyright (C) 2012 Jérémy Zurcher
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __EIOTAS_DOOR_H__
#define __EIOTAS_DOOR_H__

#include "eiotas_iota.h"
#include "eiotas_room.h"
#include "eiotas_userbits.h"

#include <eina_types.h>

typedef struct _Eiotas_Door Eiotas_Door;

struct _Eiotas_Door {
    Eiotas_Iota iota;           /* structural info */
    Eiotas_User_Bits user_bits; /* user bits */
};

EAPI Eiotas_Door*   eiotas_door_add(const char* name, Eiotas_Room *parent, Eiotas_User_Bits *user_bits);

#endif // __EIOTAS_DOOR_H__
