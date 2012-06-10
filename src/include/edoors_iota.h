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

#ifndef __EDOORS_IOTA_H__
#define __EDOORS_IOTA_H__

#include <eina_stringshare.h>

/**
 * @enum _Edoors_Type
 * List of available Edoors_Iota
 */
typedef enum _Edoors_Type
{
   EDOORS_TYPE_SPIN=0,
   EDOORS_TYPE_ROOM,
   EDOORS_TYPE_DOOR,
   EDOORS_TYPE_BOARD,
   EDOORS_TYPE_COUNT
} Edoors_Type;

/**
 * @typedef Edoors_Iota
 * Type for structural and  hierachical info
 */
typedef struct _Edoors_Iota Edoors_Iota;

/**
 * @struct _Edoors_Iota
 * Struct for structural and  hierachical info.
 */
struct _Edoors_Iota {
    Edoors_Type         type;       /**< type of the iota */
    Edoors_Iota         *spin;      /**< top level iota which is a @ref Edoors_Spin */
    Edoors_Iota         *parent;    /**< direct parent in the hierarchy */
    Eina_Stringshare    *name;      /**< iota's name */
    Eina_Stringshare    *path;      /**< full path to this @ref Edoors_Iota */
};

/**
 * @defgroup Edoors_Iota Edoors_Iota
 *
 * This is the structural info stored in each @ref Edoors_Room, @ref Edoors_Door, @ref Edoors_Board
 *
 * @{
 */

/**
 * @brief Print iota information using EINA_LOG_DBG.
 *
 * @param iota The @ref Edoors_Iota to show.
 */
EAPI void edoors_iota_show(Edoors_Iota *iota);

/**
 * @brief Free allocated resources.
 *
 * @param iota The @ref Edoors_Iota to free.
 *
 */
void edoors_iota_free(Edoors_Iota *iota);

/**
 * @brief Require a @ref Edoors_Particle from the free list.
 *
 * @see edoors_spin_require_particle
 */
#define edoors_iota_require_particle(_iota) edoors_spin_require_particle((Edoors_Spin*)(_iota)->spin)

/**
 * @brief Release a particle.
 *
 * @see edoors_spin_release_particle
 */
#define edoors_iota_release_particle(_iota,_particle) edoors_spin_release_particle((Edoors_Spin*)(_iota)->spin,_particle)

/**
 * @}
 */

#endif // __EDOORS_IOTA_H__
