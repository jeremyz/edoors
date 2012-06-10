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

#ifndef __EDOORS_ROOM_H__
#define __EDOORS_ROOM_H__

#include "edoors_iota.h"

#include <eina_hash.h>

/**
 * @typedef Edoors_Room
 * Type for a Room, which holds other child @ref Edoors_Iota.
 */
typedef struct _Edoors_Room Edoors_Room;

/**
 * @struct _Edoors_Room
 * Struct for a Room, which holds other child @ref Edoors_Iota.
 */
struct _Edoors_Room {
    Edoors_Iota     iota;       /**< @ref Edoors_Iota structural info */
    Eina_Hash       *links;     /**< TODO */
    Eina_Hash       *children;  /**< stringshared values optimized hash table holding @ref Edoors_Iota */
};

/**
 * @defgroup Edoors_Room Edoors_Room
 *
 * A Edoors_Room may hold children @ref Edoors_Room or @ref Edoors_Door (@ref Edoors_Board).
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param room The @ref Edoors_Room to free.
 *
 * This function will free all it's child @ref Edoors_Iota.
 */
void edoors_room_free(Edoors_Room *room);

/**
 * @brief Print iota information using EINA_LOG_DBG.
 *
 * @param name The name of this @ref Edoors_Iota.
 * @param parent The direct hierarchical parent @ref Edoors_Room.
 *
 * @return the new @ref Edoors_Room, @c NULL on failure
 *
 * This function will register the new room as a child of it's parent @ref Edoors_Room.
 */
EAPI Edoors_Room*   edoors_room_add(const char* name, const Edoors_Room *parent);

/**
 * @}
 */

#endif // __EDOORS_ROOM_H__
