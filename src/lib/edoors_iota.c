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

#include "edoors_iota.h"
#include "edoors_spin.h"
#include "edoors_room.h"
#include "edoors_door.h"
#include "edoors_board.h"
#include "edoors_private.h"

int edoors_iota_init(Edoors_Iota *iota, const char *name, Edoors_Iota *parent, Edoors_Type type)
{
    int ln, lp;
    char tmp[EDOORS_MAX_PATH_LENGTH];

    ln = strlen(name);
    if(name==NULL || ln==0) {
        ERR("name can't be NULL or empty");
        return 1;
    }

    iota->type = type;
    iota->spin = ( parent ? parent->spin : iota );
    iota->parent = parent;
    if(parent) {
        lp = eina_stringshare_strlen(parent->path);
        if((ln+lp+2)>EDOORS_MAX_PATH_LENGTH) {
            ERR("buffer overflow (%d)",(ln+lp+2));
            return 1;
        }
        memcpy(tmp,parent->path,lp);
        tmp[lp]='/';
        memcpy((tmp+lp+sizeof(char)),name,ln+sizeof(char));
        iota->name = eina_stringshare_add(name);
        iota->path = eina_stringshare_add(tmp);
    } else {
        iota->name = eina_stringshare_add(name);
        iota->path = eina_stringshare_add(name);
    }

    return 0;
}

void edoors_iota_desinit(Edoors_Iota *iota)
{
    STRINGSHARE_FREE(iota->name);
    STRINGSHARE_FREE(iota->path);
}

void edoors_iota_free(Edoors_Iota *iota)
{
    switch(iota->type) {
        case EDOORS_TYPE_SPIN:
            edoors_spin_free((Edoors_Spin*)iota);
            break;
        case EDOORS_TYPE_ROOM:
            edoors_room_free((Edoors_Room*)iota);
            break;
        case EDOORS_TYPE_DOOR:
            edoors_door_free((Edoors_Door*)iota);
            break;
        case EDOORS_TYPE_BOARD:
            edoors_board_free((Edoors_Board*)iota);
            break;
        default:
            CRITICAL("SPANK SPANK: 0x%X type %d is unknown, memory leak",PRINTPTR(iota),iota->type);
            break;
    }
}

EAPI void edoors_iota_show(Edoors_Iota *iota)
{
    DBG("Iota(%d) 0x%X : %s (%s) [0x%X] {0x%X}",iota->type,PRINTPTR(iota),iota->name,iota->path,
            PRINTPTR(iota->parent),PRINTPTR(iota->spin));
}

