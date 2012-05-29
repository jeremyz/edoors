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

#ifndef __EIOTAS_ROOM_H__
#define __EIOTAS_ROOM_H__

#include "eiotas_iota.h"

#include <eina_hash.h>

/**
 * @typedef Eiotas_Room
 * Type for a Room, which holds other child Eiotas_Iotas.
 */
typedef struct _Eiotas_Room Eiotas_Room;

/**
 * @struct _Eiotas_Room
 * Struct for a Room, which holds other child Eiotas_Iotas.
 */
struct _Eiotas_Room {
    Eiotas_Iota     iota;       /**< Eiotas_Iota structural info */
    Eina_Hash       *links;     /**< TODO */
    Eina_Hash       *children;  /**< stringshared values optimized hash table holding Eiotas_Iotas */
};

/**
 * @brief Free allocated resources.
 *
 * @param room The Eiotas_Room to free.
 *
 * This function will free all it's child Eiotas_Iotas.
 */
void eiotas_room_free(Eiotas_Room *room);

/**
 * @brief Print iota information using EINA_LOG_DBG.
 *
 * @param name The name of this Eiotas_Iota.
 * @param parent The direct hierarchical parent Eiotas_Room.
 *
 * @return the new Eiotas_Room, @c NULL on failure
 *
 * This function will register the new room as a child of it's parent Eiotas_Room.
 */
EAPI Eiotas_Room*   eiotas_room_add(const char* name, Eiotas_Room *parent);

#endif // __EIOTAS_ROOM_H__
