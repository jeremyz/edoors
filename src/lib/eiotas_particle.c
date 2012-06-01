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

static void update_link_value(Eiotas_Particle *particle, const char *field);
static Eina_Bool add_destination(Eiotas_Particle *particle, const char *dst, int l);

Eiotas_Particle* eiotas_particle_alloc()
{
    BUILD_INSTANCE(Eiotas_Particle,particle);

    particle->ts = 0;
    particle->src = NULL;
    particle->dst = NULL;
    particle->dsts = eina_array_new(EIOTAS_PARTICLE_ARRAY_STEP);
    particle->payload = eina_hash_string_small_new((Eina_Free_Cb)&eina_stringshare_del);
    particle->merged = NULL;
    particle->link_fields = eina_array_new(EIOTAS_PARTICLE_ARRAY_STEP);
    particle->link_value = NULL;
    particle->cur_dst = 0;

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

EAPI Eina_Bool eiotas_particle_has_dst(Eiotas_Particle *particle)
{
    if(eina_array_count_get(particle->dsts)<=particle->cur_dst) return EINA_FALSE;
    return ( (eina_array_data_get(particle->dsts,particle->cur_dst)==NULL) ? EINA_FALSE : EINA_TRUE );
}

EAPI void eiotas_particle_destinations_add(Eiotas_Particle *particle, const char* destinations)
{
    char *dst, *sep;

    dst = (char*)destinations;
    for(; *dst;) {
        for(; *dst==' '; dst++) /* eat leading spaces */;
        sep = dst;
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP && *sep!=' '); sep++) /* search destination end */;
        add_destination(particle,dst,(sep-dst));
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP); sep++) /* eat whatever following */;
        if(!*sep) return;
        dst = sep+1;
    }
}

static Eina_Bool add_destination(Eiotas_Particle *particle, const char *dst, int n)
{
    Eina_Stringshare *s;

    if(n==0) {
        ERR("ignore empty destination");
        return EINA_FALSE;
    }
    if(*dst==EIOTAS_ACTION_SEP || *dst==EIOTAS_PATH_SEP ) {
        ERR("ignore destination starting with '%c' ",*dst);
        return EINA_FALSE;
    }
    if(dst[n-1]==EIOTAS_ACTION_SEP || dst[n-1]==EIOTAS_PATH_SEP ) {
        ERR("ignore destination ending with '%c' ",dst[n-1]);
        return EINA_FALSE;
    }

    s = eina_stringshare_add_length(dst,n);
    eina_array_push(particle->dsts,s);
    DBG("add dst >%s<",s);

    return EINA_TRUE;
}

EAPI void eiotas_particle_link_fields_set(Eiotas_Particle *particle, const char *link_fields)
{
    int                 n;
    unsigned int        i;
    Eina_Stringshare    *s;
    Eina_Array_Iterator it;
    char *field, *sep;

    EINA_ARRAY_ITER_NEXT(particle->link_fields, i, s, it) eina_stringshare_del(s);
    eina_array_clean(particle->link_fields);

    field = (char*)link_fields;
    for(; *field;) {
        for(; *field==' '; field++) /* eat leading spaces */;
        sep = field;
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP && *sep!=' '); sep++) /* search field end */;
        n = (sep-field);
        if(n==0) {
            ERR("ignore empty field");
        } else {
            s = eina_stringshare_add_length(field,n);
            eina_array_push(particle->link_fields,s);
            DBG("add field >%s<",s);
        }
        for(; (*sep && *sep!=EIOTAS_FIELDS_SEP); sep++) /* eat whatever following */;
        if(!*sep) return;
        field = sep+1;
    }
    update_link_value(particle,NULL);
}

EAPI const char* eiotas_particle_data_get(Eiotas_Particle *particle, const char* key)
{
    return eina_hash_find(particle->payload,key);
}

EAPI Eina_Bool eiotas_particle_data_set(Eiotas_Particle *particle, const char* key, const char* value)
{
    unsigned int        i;
    Eina_Stringshare    *s;
    Eina_Array_Iterator it;

    s = eina_stringshare_add(value);
    if(!eina_hash_add(particle->payload,key,s)) return EINA_FALSE;
    update_link_value(particle,key);

    return EINA_TRUE;
}

EAPI Eina_Bool eiotas_particle_data_del(Eiotas_Particle *particle, const char* key)
{
    unsigned int        i;
    Eina_Stringshare    *s;
    Eina_Array_Iterator it;

    if(!eina_hash_del(particle->payload,key,NULL)) return EINA_FALSE;
    update_link_value(particle,key);

    return EINA_TRUE;
}

EAPI Eina_Bool eiotas_particle_match(Eiotas_Particle *particle, const Eiotas_Particle *p)
{
    return ( (particle->link_value==p->link_value) ? EINA_TRUE : EINA_FALSE );
}

static void update_link_value(Eiotas_Particle *particle, const char *field)
{
    unsigned int        i;
    unsigned int        l,t;
    Eina_Stringshare    *k;
    Eina_Stringshare    *v;
    Eina_Array_Iterator it;
    Eina_Bool           update;
    char                tmp[EIOTAS_MAX_VALUE_LENGTH];
    char                *dst;

    if(field!=NULL) {
        /* check if link_value has to be updated */
        update = EINA_FALSE;
        EINA_ARRAY_ITER_NEXT(particle->link_fields, i, k, it) {
            if(strcmp(field,k)==0) {
                update = EINA_TRUE;
                break;
            }
        }
        if(!update) return;
    }

    t = 1;
    dst = tmp;
    EINA_ARRAY_ITER_NEXT(particle->link_fields, i, k, it) {
        v = eina_hash_find(particle->payload,k);
        if(v!=NULL) {
            l = strlen(v);
            t += l;
            if(t>EIOTAS_MAX_VALUE_LENGTH) {
                ERR("buffer overflow (%d>%d) link_value untouched",t,EIOTAS_MAX_VALUE_LENGTH);
                return;
            }
            memcpy(dst,v,l);
            dst += l;
        }
    }
    *dst='\0';

    if(particle->link_value) {
        if(t==1) {
            eina_stringshare_del(particle->link_value);
            particle->link_value = NULL;
        } else if(strcmp(particle->link_value,tmp)!=0) {
            eina_stringshare_del(particle->link_value);
            particle->link_value = eina_stringshare_add(tmp);
        }
        /* else : keep the same stringshare */
    } else if(t!=1) {
        particle->link_value = eina_stringshare_add(tmp);
    }
    /* else : keep particle->link_value=NULL*/
}

