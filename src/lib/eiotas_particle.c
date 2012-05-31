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

#include "eiotas_particle.h"
#include "eiotas_private.h"

Eiotas_Particle* eiotas_particle_alloc()
{
    BUILD_INSTANCE(Eiotas_Particle,particle);

    particle->ts = 0;
    particle->src = NULL;
    particle->dst = NULL;
    particle->dsts = eina_array_new(EIOTAS_PARTICLE_ARRAY_STEP);
    particle->payload = eina_hash_string_small_new(NULL);           // TODO data delete function
    particle->merged = NULL;
    particle->link_fields = eina_array_new(EIOTAS_PARTICLE_ARRAY_STEP);
    particle->link_value = NULL;

    return particle;
}

void eiotas_particle_free(Eiotas_Particle *particle)
{
    unsigned int        i;
    Eina_Stringshare    *s;
    Eiotas_Particle     *p;
    Eina_Inlist         *li;
    Eina_Array_Iterator it;

    DBG("Particle free 0x%X",PRINTPTR(particle));

    EINA_ARRAY_ITER_NEXT(particle->dsts, i, s, it) eina_stringshare_del(s);
    eina_array_free(particle->dsts);
    eina_hash_free(particle->payload);
    EINA_INLIST_FOREACH_SAFE(particle->merged, li, p) eiotas_particle_free(p);
    EINA_ARRAY_ITER_NEXT(particle->link_fields, i, s, it) eina_stringshare_del(s);
    eina_array_free(particle->link_fields);
    if(particle->link_value) eina_stringshare_del(particle->link_value);

    free(particle);
}

EAPI void eiotas_particle_reset(Eiotas_Particle *particle)
{
    unsigned int        i;
    Eina_Stringshare    *s;
    Eiotas_Particle     *p;
    Eina_Inlist         *li;
    Eina_Array_Iterator it;

    particle->ts = 0;
    particle->src = NULL;
    particle->dst = NULL;
    EINA_ARRAY_ITER_NEXT(particle->dsts, i, s, it) eina_stringshare_del(s);
    eina_array_clean(particle->dsts);
    eina_hash_free_buckets(particle->payload);
    EINA_INLIST_FOREACH_SAFE(particle->merged, li, p) eiotas_particle_free(p);
    particle->merged = NULL;
    EINA_ARRAY_ITER_NEXT(particle->link_fields, i, s, it) eina_stringshare_del(s);
    eina_array_clean(particle->link_fields);
    if(particle->link_value) eina_stringshare_del(particle->link_value);
    particle->link_value = NULL;
}

EAPI void eiotas_particle_init(Eiotas_Particle *particle, Eiotas_Iota *iota)
{
    particle->src = iota;
    particle->ts = time(NULL);
}

EAPI void eiotas_particle_merge(Eiotas_Particle *particle, const Eiotas_Particle *p)
{
    particle->merged = eina_inlist_append(particle->merged, EINA_INLIST_GET((Eiotas_Particle*)p));
}

EAPI void eiotas_particle_destinations_add(Eiotas_Particle *particle, const char* destinations)
{
    int n;
    char *dst, *sep;
    Eina_Stringshare *s;

    dst = (char*)destinations;
    for(; *dst;) {
        for(; *dst==' '; dst++) /* eat leading spaces */;
        sep = dst;
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP && *sep!=' '); sep++) /* search destination end */;
        n = (sep-dst);
        if(n==0) {
            ERR("ignore empty destination");
        } else {
            s = eina_stringshare_add_length(dst,n);
            eina_array_push(particle->dsts,s);
            DBG("add dst >%s<",s);
        }
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP); sep++) /* eat whatever following */;
        if(!*sep) return;
        dst=sep+1;
    }
}

