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

#ifndef __EDOORS_PARTICLE_H__
#define __EDOORS_PARTICLE_H__

#include <time.h>
#include <eina_hash.h>
#include <eina_array.h>
#include <eina_inlist.h>
#include <eina_stringshare.h>

#include "edoors_iota.h"

/**
 * @typedef Edoors_Particle
 * Type for a Particle, holding data and spinning from Iotas to Iotas.
 */
typedef struct _Edoors_Particle Edoors_Particle;

/**
 * @struct _Edoors_Particle
 * Struct for a Particle, holding data and spinning from Iotas to Iotas.
 */
struct _Edoors_Particle {
    EINA_INLIST;                        /**< the Eina_Inlist info */
    time_t ts;                          /**< creation time */
    Edoors_Iota         *src;           /**< where it's born */
    Edoors_Iota         *dst;           /**< current destination */
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
 * @defgroup Edoors_Particle Edoors_Particle
 *
 * The central part of Edoors. The Particle holds, the data, the destination list.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param particle The @ref Edoors_Particle to free.
 *
 * This function will free all the merged @ref Edoors_Particle
 */
void edoors_particle_free(Edoors_Particle *particle);

/**
 * @brief Allocate the resources.
 *
 * @return the new allocated @ref Edoors_Particle @c NULL on failure
 */
Edoors_Particle* edoors_particle_alloc();

/**
 * @brief Reset the @ref Edoors_Particle so that it can be required later.
 *
 * @param particle The @ref Edoors_Particle to reset
 */
EAPI void edoors_particle_reset(Edoors_Particle *particle);

/**
 * @brief Set @c src and @c ts timestamp.
 *
 * @param particle The @ref Edoors_Particle to init
 * @param iota The @ref Edoors_Iota wich will be set as @c src
 */
EAPI void edoors_particle_init(Edoors_Particle *particle, Edoors_Iota *iota);

/**
 * @brief Merge a @ref Edoors_Particle into the other.
 *
 * @param particle The @ref Edoors_Particle to hold @p p
 * @param p The @ref Edoors_Particle to be merged into @p particle
 */
EAPI void edoors_particle_merge(Edoors_Particle *particle, const Edoors_Particle *p);

/**
 * @brief Check if a current destination is defined
 *
 * @param particle The @ref Edoors_Particle to check
 *
 * @return EINA_TRUE if a current destination is defined, EINA_FALSE otherwise.
 */
EAPI Eina_Bool edoors_particle_has_dst(Edoors_Particle *particle);

/**
 * @brief Point to the next destination
 *
 * @param particle The @ref Edoors_Particle to mofify
 *
 * @return EINA_TRUE if next destination is defined, EINA_FALSE otherwise.
 */
EAPI Eina_Bool edoors_particle_next_dst(Edoors_Particle *particle);

/**
 * @brief Split current destination in room ; door ; action Eina_Stringshare
 *
 * @param particle The @ref Edoors_Particle to split current destination
 *
 */
EAPI void edoors_particle_split_dst(Edoors_Particle *particle);

/**
 * @brief Add a destination and set it as current
 *
 * @param particle The @ref Edoors_Particle to add destination to
 * @param destination The destination to add and set as current
 */
EAPI void edoors_particle_destination_set(Edoors_Particle *particle, const char *destination);

/**
 * @brief Add destinations to the @ref Edoors_Particle
 *
 * @param particle The @ref Edoors_Particle to add destinations to
 * @param destinations A comma separated list of destination "/room0/room1/.../doorx?action"
 *
 * This function will append each destination found to the destination list of the @ref Edoors_Particle.
 */
EAPI void edoors_particle_destinations_add(Edoors_Particle *particle, const char *destinations);

/**
 * @brief Set the link fields
 *
 * @param particle The @ref Edoors_Particle to set the link fields to
 * @param link_fields A comma separated list of fields name
 *
 */
EAPI void edoors_particle_link_fields_set(Edoors_Particle *particle, const char *link_fields);

/**
 * @brief Restore the data associated to a given key
 *
 * @param particle The @ref Edoors_Particle to restore data from
 * @param key The Eina_Hash key
 *
 * @return The data stored on success, NULL otherwise.
 */
EAPI const char* edoors_particle_data_get(Edoors_Particle *particle, const char *key);

/**
 * @brief Store a key:value data couple into the Edoors_Particle
 *
 * @param particle The @ref Edoors_Particle to store data into
 * @param key The Eina_Hash key
 * @param value The value to store
 *
 * @return EINA_FALSE if an error occurred, EINA_TRUE otherwise.
 */
EAPI Eina_Bool edoors_particle_data_set(Edoors_Particle *particle, const char *key, const char *value);

/**
 * @brief Delete the data associated to a given key
 *
 * @param particle The @ref Edoors_Particle to delete data from
 * @param key The Eina_Hash key
 *
 * @return EINA_FALSE if an error occurred, EINA_TRUE otherwise.
 */
EAPI Eina_Bool edoors_particle_data_del(Edoors_Particle *particle, const char *key);

/**
 * @brief Check if two @ref Edoors_Particle have the same link_value
 *
 * @param particle The @ref Edoors_Particle to compare with
 * @param p The @ref Edoors_Particle to compare with
 *
 * @return EINA_TRUE if the link value is the same, EINA_FALSE otherwise.
 */
EAPI Eina_Bool edoors_particle_match(Edoors_Particle *particle, const Edoors_Particle *p);

/**
 * @}
 */

#endif // __EDOORS_PARTICLE_H__
