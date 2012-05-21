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

#ifndef __EIOTAS_IOTA_H__
#define __EIOTAS_IOTA_H__

#include <eina_stringshare.h>

typedef enum _Eiotas_Type
{
   EIOTAS_TYPE_SPIN=0,
   EIOTAS_TYPE_ROOM,
   EIOTAS_TYPE_BOARD,
   EIOTAS_TYPE_DOOR,
   EIOTAS_TYPE_COUNT
} Eiotas_Type;

typedef struct _Eiotas_Iota Eiotas_Iota;

struct _Eiotas_Iota {
    Eiotas_Type type;           /* type of the iota */
    Eiotas_Iota *spin;          /* top level iota which is a Eiota_Spin */
    Eiotas_Iota *parent;        /* direct parent in the hierarchy */
    Eina_Stringshare *name;     /* iota's name */
    Eina_Stringshare *path;     /* full path to this iota */
};

EAPI void eiotas_iota_show(Eiotas_Iota *iota);

void eiotas_iota_free(Eiotas_Iota *iota);

#define eiotas_iota_require_particle(_iota) eiotas_spin_require_particle((Eiotas_Spin*)(_iota)->spin)

#define eiotas_iota_release_particle(_iota,_particle) eiotas_spin_release_particle((Eiotas_Spin*)(_iota)->spin,_particle)

#endif // __EIOTAS_IOTA_H__
