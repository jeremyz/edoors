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

#ifndef __EDOORS_DOOR_H__
#define __EDOORS_DOOR_H__

#include "edoors_iota.h"
#include "edoors_room.h"
#include "edoors_userbits.h"

#include <eina_types.h>

/**
 * @typedef Edoors_Door
 * Type for a basic Door.
 */
typedef struct _Edoors_Door Edoors_Door;

/**
 * @struct _Edoors_Door
 * Struct for a basic Door.
 */
struct _Edoors_Door {
    Edoors_Iota         iota;       /**< structural info */
    Edoors_User_Bits    user_bits;  /**< user bits */
};

/**
 * @defgroup Edoors_Door Edoors_Door
 *
 * A Edoors_Door is the main structure used to interact with user code.
 * @ref Edoors_Particle sent to user code are, follower and sent releaseed
 * through edoors_spin_release_particle if not cprrectly managed by user code.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param door The @ref Edoors_Door to free.
 *
 * This function will free all it's user data using user_bits ... FIXME
 */
void edoors_door_free(Edoors_Door *door);

/**
 * @brief Allocate the resources.
 *
 * @param name The name of this door.
 * @param parent The direct hierarchical parent @ref Edoors_Room.
 * @param user_bits A Edoors_User_Bits initilized with user side pointers.
 *
 * @return the new allocated @ref Edoors_Door @c NULL on failure
 *
 * @see Edoors_User_Bits
 */
EAPI Edoors_Door*   edoors_door_add(const char* name, const Edoors_Room *parent, Edoors_User_Bits *user_bits);

/**
 * @}
 */

#endif // __EDOORS_DOOR_H__
