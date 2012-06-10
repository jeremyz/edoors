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

#ifndef __EDOORS_USERBITS_H__
#define __EDOORS_USERBITS_H__

#include "edoors_iota.h"
#include "edoors_particle.h"

/**
 * @typedef Edoors_User_Bits
 * Type for a @ref Edoors_User_Bits.
 */
typedef struct _Edoors_User_Bits Edoors_User_Bits;

/**
 * @typedef Edoors_User_Data
 * Struct for user allocated data attached to a @ref Edoors_Door or a @ref Edoors_Board
 */
typedef void Edoors_User_Data;

/**
 * @typedef Edoors_User_Data
 * Type for function called on resources free
 *
 * @see edoors_door_free()
 * @see edoors_board_free()
 */
typedef void (*Edoors_User_Data_Free)   (Edoors_User_Data*);

/**
 * @typedef Edoors_Receive_Particle
 * Type for function called on @ref Edoors_Particle receive
 */
typedef void (*Edoors_Receive_Particle) (Edoors_Iota *iota, Edoors_Particle *particle, Edoors_User_Data *data);

/**
 * @typedef Edoors_Init
 * Type for function called on systsem init
 */
typedef void (*Edoors_Init)     (Edoors_Iota *iota, Edoors_User_Data *data);

/**
 * @typedef Edoors_Shutdown
 * Type for function called on system shutdown
 */
typedef void (*Edoors_Shutdown) (Edoors_Iota *iota, Edoors_User_Data *data);

/**
 * @typedef Edoors_Suspend
 * Type for function called on system suspend
 */
typedef void (*Edoors_Suspend)  (Edoors_Iota *iota, Edoors_User_Data *data);

/**
 * @typedef Edoors_Resume
 * Type for function called on system resume
 */
typedef void (*Edoors_Resume)   (Edoors_Iota *iota, Edoors_User_Data *data);

/**
 * @struct _Edoors_User_Bits
 * Struct for a Edoors_User_Bits.
 */
struct _Edoors_User_Bits {
    Edoors_User_Data        *data;          /**< user data */
    Edoors_User_Data_Free   free_fct;       /**< to free user data */
    Edoors_Receive_Particle recv_fct;       /**< to receive and process a @ref Edoors_Particle */
    Edoors_Init             init_fct;       /**< to initialize user data on system init */
    Edoors_Shutdown         shutdown_fct;   /**< to finalize user data on system shutdown */
    Edoors_Suspend          suspend_fct;    /**< to serialize user data on system shutdown */
    Edoors_Resume           resume_fct;     /**< to deserialize data on system resume */
};

#endif // __EDOORS_USERBITS_H__
