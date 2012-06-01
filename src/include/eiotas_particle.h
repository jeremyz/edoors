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

#ifndef __EIOTAS_PARTICLE_H__
#define __EIOTAS_PARTICLE_H__

#include <time.h>
#include <eina_hash.h>
#include <eina_array.h>
#include <eina_inlist.h>
#include <eina_stringshare.h>

#include "eiotas_iota.h"

/**
 * @typedef Eiotas_Particle
 * Type for a Particle, holding data and spinning from Iotas to Iotas.
 */
typedef struct _Eiotas_Particle Eiotas_Particle;

/**
 * @struct _Eiotas_Particle
 * Struct for a Particle, holding data and spinning from Iotas to Iotas.
 */
struct _Eiotas_Particle {
    EINA_INLIST;                        /**< the Eina_Inlist info */
    time_t ts;                          /**< creation time */
    Eiotas_Iota         *src;           /**< where it's born */
    Eiotas_Iota         *dst;           /**< current destination */
    Eina_Array          *dsts;          /**< array of destinatinon strings */
    unsigned int        cur_dst;        /**< current destination index */
    Eina_Stringshare    *cur_action;    /**< action part of the current destination */
    Eina_Stringshare    *cur_door;      /**< door part of the current destination */
    Eina_Stringshare    *cur_room;      /**< room part of the current destination */
    Eina_Hash           *payload;       /**< string data carried by this particle */
    Eina_Inlist         *merged;        /**< list of merged particles */
    Eina_Array          *link_fields;   /**< fields used to generate the link value */
    Eina_Stringshare    *link_value;    /**< computed from link_fields and paylod, used for pearing particles */
};

/**
 * @defgroup Eiotas_Particle Eiotas_Particle
 *
 * The central part of Eiotas. The Particle holds, the data, the destination list.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param particle The @ref Eiotas_Particle to free.
 *
 * This function will free all the merged @ref Eiotas_Particle
 */
void eiotas_particle_free(Eiotas_Particle *particle);

/**
 * @brief Allocate the resources.
 *
 * @return the new allocated @ref Eiotas_Particle @c NULL on failure
 */
Eiotas_Particle* eiotas_particle_alloc();

/**
 * @brief Reset the @ref Eiotas_Particle so that it can be required later.
 *
 * @param particle The @ref Eiotas_Particle to reset
 */
EAPI void eiotas_particle_reset(Eiotas_Particle *particle);

/**
 * @brief Set @c src and @c ts timestamp.
 *
 * @param particle The @ref Eiotas_Particle to init
 * @param iota The @ref Eiotas_Iota wich will be set as @c src
 */
EAPI void eiotas_particle_init(Eiotas_Particle *particle, Eiotas_Iota *iota);

/**
 * @brief Merge a @ref Eiotas_Particle into the other.
 *
 * @param particle The @ref Eiotas_Particle to hold @p p
 * @param p The @ref Eiotas_Particle to be merged into @p particle
 */
EAPI void eiotas_particle_merge(Eiotas_Particle *particle, const Eiotas_Particle *p);

/**
 * @brief Check if a current destination is defined
 *
 * @param particle The @ref Eiotas_Particle to check
 *
 * @return EINA_TRUE if a current destination is defined, EINA_FALSE otherwise.
 */
EAPI Eina_Bool eiotas_particle_has_dst(Eiotas_Particle *particle);

/**
 * @brief Point to the next destination
 *
 * @param particle The @ref Eiotas_Particle to mofify
 *
 * @return EINA_TRUE if next destination is defined, EINA_FALSE otherwise.
 */
EAPI Eina_Bool eiotas_particle_next_dst(Eiotas_Particle *particle);

/**
 * @brief Add destinations to the @ref Eiotas_Particle
 *
 * @param particle The @ref Eiotas_Particle to add destinations to
 * @param destinations A comma separated list of destination "/room0/room1/.../doorx?action"
 *
 * This function will append each destination found to the destination list of the @ref Eiotas_Particle.
 */
EAPI void eiotas_particle_destinations_add(Eiotas_Particle *particle, const char *destinations);

/**
 * @brief Set the link fields
 *
 * @param particle The @ref Eiotas_Particle to set the link fields to
 * @param link_fields A comma separated list of fields name
 *
 */
EAPI void eiotas_particle_link_fields_set(Eiotas_Particle *particle, const char *link_fields);

/**
 * @brief Restore the data associated to a given key
 *
 * @param particle The @ref Eiotas_Particle to restore data from
 * @param key The Eina_Hash key
 *
 * @return The data stored on success, NULL otherwise.
 */
EAPI const char* eiotas_particle_data_get(Eiotas_Particle *particle, const char *key);

/**
 * @brief Store a key:value data couple into the Eiotas_Particle
 *
 * @param particle The @ref Eiotas_Particle to store data into
 * @param key The Eina_Hash key
 * @param value The value to store
 *
 * @return EINA_FALSE if an error occurred, EINA_TRUE otherwise.
 */
EAPI Eina_Bool eiotas_particle_data_set(Eiotas_Particle *particle, const char *key, const char *value);

/**
 * @brief Delete the data associated to a given key
 *
 * @param particle The @ref Eiotas_Particle to delete data from
 * @param key The Eina_Hash key
 *
 * @return EINA_FALSE if an error occurred, EINA_TRUE otherwise.
 */
EAPI Eina_Bool eiotas_particle_data_del(Eiotas_Particle *particle, const char *key);

/**
 * @brief Check if two @ref Eiotas_Particle have the same link_value
 *
 * @param particle The @ref Eiotas_Particle to compare with
 * @param p The @ref Eiotas_Particle to compare with
 *
 * @return EINA_TRUE if the link value is the same, EINA_FALSE otherwise.
 */
EAPI Eina_Bool eiotas_particle_match(Eiotas_Particle *particle, const Eiotas_Particle *p);

/**
 * @}
 */

#endif // __EIOTAS_PARTICLE_H__
