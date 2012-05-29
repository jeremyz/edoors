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

#ifndef __EIOTAS_SPIN_H__
#define __EIOTAS_SPIN_H__

#include "eiotas_room.h"
#include "eiotas_iota.h"
#include "eiotas_particle.h"

#include <eina_inlist.h>
#include <eina_array.h>

/**
 * @typedef Eiotas_Spin
 * Type for a Spin, the top level Room which holds Eiotas_Particle fifos and free Eiotas_Particles.
 */
typedef struct _Eiotas_Spin Eiotas_Spin;

/**
 * @struct _Eiotas_Spin
 * Struct for a Spin, the top level Room which holds Eiotas_Particle fifos and free Eiotas_Particles.
 */
struct  _Eiotas_Spin {
    Eiotas_Room     room;               /**< higher level Room */
    Eina_Array      *free_particles;    /**< lifo of free to reuse Eiotas_Particles TODO support different particle types, use an Eina_Hash */
    Eina_Inlist     *app_fifo;          /**< fifo of application priority particles */
    Eina_Inlist     *sys_fifo;          /**< fifo of system priority particles */
};

/**
 * @brief Free allocated resources.
 *
 * @param spin The Eiotas_Spin to free.
 *
 * This function will free all it's child Iotas,
 * all the Eiotas_Particles holded in app_fifo, sys_fifo and free_particles.
 */
EAPI void               eiotas_spin_free(Eiotas_Spin *spin);

/**
 * @brief Allocate the resources.
 *
 * @param name The name of this spin.
 * @param step The count of pointers to add when increasing the fifo size.
 *
 * @return the new allocated Eiotas_Spin @c NULL on failure
 *
 * @see eina_array_new().
 */
EAPI Eiotas_Spin*       eiotas_spin_add(const char* name, unsigned int step);

/**
 * @brief Require a Eiotas_Particle from the free list.
 *
 * @param spin The Eiotas_Spin to require a Eiotas_Particle from.
 *
 * @return a ready to use Eiotas_Particle
 *
 * This function will allocate and initialize a new Eiotas_Particle if there is none in the free list.
 */
EAPI Eiotas_Particle*   eiotas_spin_require_particle(Eiotas_Spin *spin);

/**
 * @brief Release a particle.
 *
 * @param spin The Eiotas_Spin to restore the particle to.
 * @param particle The Eiotas_Particle to be restored.
 *
 * This function calls eiotas_particle_reset() before giving back the Eiotas_Particle.
 * Each Eiotas_Particle merged in the first one are also released.
 *
 * @see eiotas_particle_reset().
 */
EAPI void               eiotas_spin_release_particle(Eiotas_Spin *spin, Eiotas_Particle *particle);

/**
 * @brief Appand the Eiotas_Particle to the app or sys fifo.
 *
 * @param spin The Eiotas_Spin to post the particle to.
 * @param particle The Eiotas_Particle to be sent.
 * @param system Post to the system fifo us true, otherwise to the application fifo.
 *
 */
EAPI void               eiotas_spin_send_particle(Eiotas_Spin *spin, Eiotas_Particle *particle, Eina_Bool system);

#define eiotas_require_particle(_iota) eiotas_spin_require_particle((Eiotas_Spin*)((Eiotas_Iota*)(_iota))->spin)

#define eiotas_release_particle(_iota,_particle) eiotas_spin_release_particle((Eiotas_Spin*)((Eiotas_Iota*)(_iota))->spin,_particle)

#endif // __EIOTAS_SPIN_H__
