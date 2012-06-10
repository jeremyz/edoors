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

#include "edoors_spin.h"
#include "edoors_iota.h"
#include "edoors_particle.h"
#include "edoors_private.h"

EAPI Edoors_Spin* edoors_spin_add(const char* name, unsigned int step)
{
    BUILD_INSTANCE(Edoors_Spin,spin);

    INIT_IOTA(&spin->room.iota,name,NULL,EDOORS_TYPE_SPIN);

    spin->room.links = NULL;    /* not used */
    spin->room.children = eina_hash_stringshared_new((Eina_Free_Cb)&edoors_iota_free);
    spin->free_particles = eina_array_new(step);
    spin->sys_fifo = NULL;
    spin->app_fifo = NULL;

    return spin;
}

EAPI void edoors_spin_free(Edoors_Spin *spin)
{
    unsigned int        i;
    Edoors_Particle     *particle;
    Eina_Array_Iterator iterator;
    Eina_Inlist         *list;

    DBG("Spin free 0x%X",PRINTPTR(spin));

    edoors_iota_desinit(&spin->room.iota);
    eina_hash_free(spin->room.children);
    EINA_ARRAY_ITER_NEXT(spin->free_particles, i, particle, iterator) edoors_particle_free(particle);
    eina_array_free(spin->free_particles);
    EINA_INLIST_FOREACH_SAFE(spin->sys_fifo, list,particle) edoors_particle_free(particle);
    EINA_INLIST_FOREACH_SAFE(spin->app_fifo, list,particle) edoors_particle_free(particle);

    free(spin);
}

EAPI Edoors_Particle* edoors_spin_require_particle(Edoors_Spin *spin)
{
    Edoors_Particle *particle;
    if(eina_array_count(spin->free_particles)>0) {
        particle = eina_array_pop(spin->free_particles);
    } else {
        particle = (Edoors_Particle*)edoors_particle_alloc();
    }
    return particle;
}

EAPI void edoors_spin_release_particle(Edoors_Spin *spin, Edoors_Particle *particle)
{
    Edoors_Particle     *p;
    Eina_Inlist         *list;

    while (particle->merged) {
        p = EINA_INLIST_CONTAINER_GET(particle->merged,Edoors_Particle);
        particle->merged = eina_inlist_remove(particle->merged,particle->merged);
        edoors_spin_release_particle(spin,p);
    }
    edoors_particle_reset(particle);
    eina_array_push(spin->free_particles,particle);
}

EAPI void edoors_spin_send_particle(Edoors_Spin *spin, const Edoors_Particle *particle, Eina_Bool system)
{
    if(system) {
        spin->sys_fifo = eina_inlist_append(spin->sys_fifo,EINA_INLIST_GET((Edoors_Particle*)particle));
    } else {
        spin->app_fifo = eina_inlist_append(spin->app_fifo,EINA_INLIST_GET((Edoors_Particle*)particle));
    }
}

