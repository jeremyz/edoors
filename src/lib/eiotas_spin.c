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

#include "eiotas_spin.h"
#include "eiotas_iota.h"
#include "eiotas_particle.h"
#include "eiotas_private.h"

EAPI Eiotas_Spin* eiotas_spin_add(const char* name, unsigned int step)
{
    BUILD_INSTANCE(Eiotas_Spin,spin);

    INIT_IOTA(&spin->room.iota,name,NULL,EIOTAS_TYPE_SPIN);

    spin->room.links = NULL;    /* not used */
    spin->room.children = eina_hash_stringshared_new((Eina_Free_Cb)&eiotas_iota_free);
    spin->free_particles = eina_array_new(step);
    spin->sys_fifo = eina_array_new(step);
    spin->app_fifo = eina_array_new(step);

    return spin;
}

EAPI void eiotas_spin_free(Eiotas_Spin *spin)
{
    unsigned int        i;
    Eiotas_Particle     *particle;
    Eina_Array_Iterator iterator;

    DBG("Spin free 0x%X",PRINTPTR(spin));

    eiotas_iota_desinit(&spin->room.iota);
    eina_hash_free(spin->room.children);
    EINA_ARRAY_ITER_NEXT(spin->free_particles, i, particle, iterator) eiotas_particle_free(particle);
    EINA_ARRAY_ITER_NEXT(spin->sys_fifo, i, particle, iterator) eiotas_particle_free(particle);
    EINA_ARRAY_ITER_NEXT(spin->app_fifo, i, particle, iterator) eiotas_particle_free(particle);
    eina_array_free(spin->free_particles);
    eina_array_free(spin->sys_fifo);
    eina_array_free(spin->app_fifo);

    free(spin);
}

EAPI Eiotas_Particle* eiotas_spin_require_particle(Eiotas_Spin *spin)
{
    Eiotas_Particle *particle;
    if(eina_array_count(spin->free_particles)>0) {
        particle = eina_array_pop(spin->free_particles);
    } else {
        particle = (Eiotas_Particle*)eiotas_particle_alloc();
    }
    return particle;
}

EAPI void eiotas_spin_release_particle(Eiotas_Spin *spin, Eiotas_Particle *particle)
{
    // TODO particle->reset();
    eina_array_push(spin->free_particles,particle);
}

