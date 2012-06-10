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

#ifndef __EDOORS_BOARD_H__
#define __EDOORS_BOARD_H__

#include "edoors_iota.h"
#include "edoors_room.h"
#include "edoors_userbits.h"

#include <eina_hash.h>

/**
 * @typedef Edoors_Board
 * Type for a Particle Merging Door.
 */
typedef struct _Edoors_Board Edoors_Board;

/**
 * @struct _Edoors_Board
 * Struct for a Particle Merging Door.
 */
struct _Edoors_Board {
    Edoors_Iota         iota;           /**< structural info */
    Edoors_User_Bits    user_bits;      /**< user bits */
    Eina_Hash           *postponed;     /**< TODO Particles */
};

/**
 * @defgroup Edoors_Board Edoors_Board
 *
 * A Edoors_Board holds @ref Edoors_Particle received.
 * When two @ref Edoors_Particle with the same link_value exists, they are merged together
 * and delivered to user code through Edoors_Receive_Particle callback.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param board The @ref Edoors_Board to free.
 *
 * This function will free all it's user data using user_bits ... FIXME
 */
void edoors_board_free(Edoors_Board *board);

/**
 * @brief Allocate the resources.
 *
 * @param name The name of this door.
 * @param parent The direct hierarchical parent @ref Edoors_Room.
 * @param user_bits A Edoors_User_Bits initilized with user side pointers.
 *
 * @return the new allocated @ref Edoors_Board @c NULL on failure
 *
 * @see Edoors_User_Bits
 */
EAPI Edoors_Board*  edoors_board_add(const char* name, const Edoors_Room *parent, Edoors_User_Bits *user_bits);

/**
 * @}
 */

#endif // __EDOORS_BOARD_H__
