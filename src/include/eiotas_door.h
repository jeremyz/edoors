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

/**
 * @typedef Eiotas_Door
 * Type for a basic Door.
 */
typedef struct _Eiotas_Door Eiotas_Door;

/**
 * @struct _Eiotas_Door
 * Struct for a basic Door.
 */
struct _Eiotas_Door {
    Eiotas_Iota         iota;       /**< structural info */
    Eiotas_User_Bits    user_bits;  /**< user bits */
};

/**
 * @defgroup Eiotas_Door Eiotas_Door
 *
 * A Eiota_Door is the main structure used to interact with user code.
 * @ref Eiotas_Particle sent to user code are, follower and sent releaseed
 * through eiotas_spin_release_particle if not cprrectly managed by user code.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param door The @ref Eiotas_Door to free.
 *
 * This function will free all it's user data using user_bits ... FIXME
 */
void eiotas_door_free(Eiotas_Door *door);

/**
 * @brief Allocate the resources.
 *
 * @param name The name of this door.
 * @param parent The direct hierarchical parent @ref Eiotas_Room.
 * @param user_bits A Eiotas_User_Bits initilized with user side pointers.
 *
 * @return the new allocated @ref Eiotas_Door @c NULL on failure
 *
 * @see Eiotas_User_Bits
 */
EAPI Eiotas_Door*   eiotas_door_add(const char* name, Eiotas_Room *parent, Eiotas_User_Bits *user_bits);

/**
 * @}
 */

#endif // __EIOTAS_DOOR_H__
