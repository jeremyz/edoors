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

#ifdef HAVE_CONFIG_H
# include "eina_config.h"
#endif

#include "eiotas_room.h"
#include "eiotas_private.h"

EAPI Eiotas_Room* eiotas_room_add(const char* name, Eiotas_Room *parent)
{
    CHECK_PARENT();

    BUILD_INSTANCE(Eiotas_Room,room);

    if(eiotas_iota_init(&room->iota,name,parent,EIOTAS_TYPE_ROOM)) {
        return NULL;
    }

    if(eina_hash_find(parent->children,room->iota.name)) {
        ERR("Room %s already exists in %s",name,parent->iota.path);
        eiotas_iota_desinit(&room->iota);
        return NULL;
    }
    eina_hash_direct_add(parent->children,room->iota.name,room);

    room->links = NULL;    // TODO
    room->children = eina_hash_stringshared_new((Eina_Free_Cb)&eiotas_iota_free);

    return room;
}

void eiotas_room_free(Eiotas_Room *room)
{
    DBG("Room free 0x%X",room);

    eiotas_iota_desinit(&room->iota);
    // TODO room->links
    eina_hash_free(room->children);

    free(room);
}

