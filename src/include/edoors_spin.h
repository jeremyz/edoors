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

#ifndef __EDOORS_SPIN_H__
#define __EDOORS_SPIN_H__

#include "edoors_room.h"
#include "edoors_iota.h"
#include "edoors_particle.h"

#include <eina_inlist.h>
#include <eina_array.h>

/**
 * @typedef Edoors_Spin
 * Type for a Spin, the top level Room which holds @ref Edoors_Particle fifos and free @ref Edoors_Particle.
 */
typedef struct _Edoors_Spin Edoors_Spin;

/**
 * @struct _Edoors_Spin
 * Struct for a Spin, the top level Room which holds @ref Edoors_Particle fifos and free @ref Edoors_Particle.
 */
struct  _Edoors_Spin {
    Edoors_Room     room;               /**< higher level Room */
    Eina_Array      *free_particles;    /**< lifo of free to reuse @ref Edoors_Particle TODO support different particle types, use an Eina_Hash */
    Eina_Inlist     *app_fifo;          /**< fifo of application priority particles */
    Eina_Inlist     *sys_fifo;          /**< fifo of system priority particles */
};

/**
 * @defgroup Edoors_Spin Edoors_Spin
 *
 * A Edoors_Spin is the top level object. It holds @ref Edoors_Particle free list,
 * @ref Edoors_Particle system and application fifos.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param spin The @ref Edoors_Spin to free.
 *
 * This function will free all it's child Iotas,
 * all the @ref Edoors_Particle holded in app_fifo, sys_fifo and free_particles.
 */
EAPI void               edoors_spin_free(Edoors_Spin *spin);

/**
 * @brief Allocate the resources.
 *
 * @param name The name of this spin.
 * @param step The count of pointers to add when increasing the fifo size.
 *
 * @return the new allocated @ref Edoors_Spin @c NULL on failure
 *
 * @see eina_array_new().
 */
EAPI Edoors_Spin*       edoors_spin_add(const char* name, unsigned int step);

/**
 * @brief Require a @ref Edoors_Particle from the free list.
 *
 * @param spin The @ref Edoors_Spin to require a @ref Edoors_Particle from.
 *
 * @return a ready to use @ref Edoors_Particle
 *
 * This function will allocate and initialize a new @ref Edoors_Particle if there is none in the free list.
 */
EAPI Edoors_Particle*   edoors_spin_require_particle(Edoors_Spin *spin);

/**
 * @brief Release a particle.
 *
 * @param spin The @ref Edoors_Spin to restore the particle to.
 * @param particle The @ref Edoors_Particle to be restored.
 *
 * This function calls edoors_particle_reset() before giving back the @ref Edoors_Particle.
 * Each @ref Edoors_Particle merged in the first one are also released.
 *
 * @see edoors_particle_reset().
 */
EAPI void               edoors_spin_release_particle(Edoors_Spin *spin, Edoors_Particle *particle);

/**
 * @brief Append the @ref Edoors_Particle to the app or sys fifo.
 *
 * @param spin The @ref Edoors_Spin to post the particle to.
 * @param particle The @ref Edoors_Particle to be sent.
 * @param system Post to the system fifo us true, otherwise to the application fifo.
 *
 */
EAPI void               edoors_spin_send_particle(Edoors_Spin *spin, const Edoors_Particle *particle, Eina_Bool system);

/**
 * @brief Require a @ref Edoors_Particle from the free list.
 *
 * @see edoors_spin_require_particle
 */
#define edoors_require_particle(_iota) edoors_spin_require_particle((Edoors_Spin*)((Edoors_Iota*)(_iota))->spin)

/**
 * @brief Release a particle.
 *
 * @see edoors_spin_release_particle
 */
#define edoors_release_particle(_iota,_particle) edoors_spin_release_particle((Edoors_Spin*)((Edoors_Iota*)(_iota))->spin,_particle)

/**
 * @}
 */

#endif // __EDOORS_SPIN_H__
