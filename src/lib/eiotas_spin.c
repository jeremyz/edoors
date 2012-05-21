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

#ifdef HAVE_CONFIG_H
# include "eina_config.h"
#endif

#include "eiotas_spin.h"
#include "eiotas_iota.h"
#include "eiotas_private.h"

EAPI Eiotas_Spin* eiotas_spin_add(const char* name, unsigned int step)
{
    BUILD_INSTANCE(Eiotas_Spin,spin);

    if(name==NULL) {
        ERR("name can't be NULL");
        return NULL;
    }

    if(eiotas_iota_init(&spin->room.iota,name,NULL,EIOTAS_TYPE_SPIN)) {
        return NULL;
    }

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

    DBG("Spin free 0x%X",spin);

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

