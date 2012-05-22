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

#include "eiotas_iota.h"
#include "eiotas_spin.h"
#include "eiotas_room.h"
#include "eiotas_door.h"
#include "eiotas_board.h"
#include "eiotas_private.h"

int eiotas_iota_init(Eiotas_Iota *iota, const char *name, Eiotas_Iota *parent, Eiotas_Type type)
{
    int ln, lp;
    char tmp[MAX_PATH_LENGTH];

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
        if((ln+lp+2)>MAX_PATH_LENGTH) {
            ERR("path length %d is > MAX_PATH_LENGTH (%d)",(ln+lp+2),MAX_PATH_LENGTH);
            return 1;
        }
        memcpy(tmp,parent->path,lp);
        tmp[lp]='/';
        memcpy((tmp+lp+1),name,ln+1);
        iota->name = eina_stringshare_add(name);
        iota->path = eina_stringshare_add(tmp);
    } else {
        iota->name = eina_stringshare_add(name);
        iota->path = eina_stringshare_add(name);
    }

    return 0;
}

void eiotas_iota_desinit(Eiotas_Iota *iota)
{
    eina_stringshare_del(iota->name);
    eina_stringshare_del(iota->path);
}

void eiotas_iota_free(Eiotas_Iota *iota)
{
    switch(iota->type) {
        case EIOTAS_TYPE_SPIN:
            eiotas_spin_free((Eiotas_Spin*)iota);
            break;
        case EIOTAS_TYPE_ROOM:
            eiotas_room_free((Eiotas_Room*)iota);
            break;
        case EIOTAS_TYPE_DOOR:
            eiotas_door_free((Eiotas_Door*)iota);
            break;
        case EIOTAS_TYPE_BOARD:
            eiotas_board_free((Eiotas_Board*)iota);
            break;
    }
}

EAPI void eiotas_iota_show(Eiotas_Iota *iota)
{
    DBG("Iota(%d) 0x%X : %s (%s) [0x%X] {0x%X}",iota->type,(unsigned int)iota,iota->name,iota->path,
            (unsigned int)iota->parent,(unsigned int)iota->spin);
}

