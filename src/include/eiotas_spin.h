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

#include <eina_array.h>

typedef struct _Eiotas_Spin Eiotas_Spin;

struct  _Eiotas_Spin {
    Eiotas_Room room;           /* higher level Room */
    Eina_Array *free_particles; /* lifo of free to reuse Particles TODO support different particle types, use an Eina_Hash */
    Eina_Array *app_fifo;       /* fifo of application priority particles */
    Eina_Array *sys_fifo;       /* fifo of system priority particles */
};

EAPI void               eiotas_spin_free(Eiotas_Spin *spin);

EAPI Eiotas_Spin*       eiotas_spin_add(const char* name, unsigned int step);

EAPI Eiotas_Particle*   eiotas_spin_require_particle(Eiotas_Spin *spin);

EAPI Eiotas_Particle*   eiotas_spin_release_particle(Eiotas_Spin *spin, Eiotas_Particle *particle);

EAPI void               eiotas_spin_send_particle(Eiotas_Spin *spin, Eiotas_Particle *particle, Eina_Bool system);

#define eiotas_require_particle(_iota) eiotas_spin_require_particle((Eiotas_Spin*)((Eiotas_Iota*)(_iota))->spin)

#define eiotas_release_particle(_iota,_particle) eiotas_spin_release_particle((Eiotas_Spin*)((Eiotas_Iota*)(_iota))->spin,_particle)

#endif // __EIOTAS_SPIN_H__
