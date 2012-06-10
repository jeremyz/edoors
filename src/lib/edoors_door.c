/* EDOORS
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

#include "edoors_door.h"
#include "edoors_private.h"

EAPI Edoors_Door* edoors_door_add(const char* name, const Edoors_Room *parent, Edoors_User_Bits *user_bits)
{
    CHECK_PARENT();

    CHECK_USERBITS(user_bits);

    BUILD_INSTANCE(Edoors_Door,door);

    INIT_IOTA(&door->iota,name,parent,EDOORS_TYPE_DOOR);

    ADD_TO_PARENT(parent,(&door->iota),"Door")

    memcpy(&door->user_bits,user_bits,sizeof(Edoors_User_Bits));

    return door;
}

void edoors_door_free(Edoors_Door *door)
{
    DBG("Door free 0x%X",PRINTPTR(door));

    edoors_iota_desinit(&door->iota);
    door->user_bits.free_fct(door->user_bits.data);

    free(door);
}

