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
    Eina_Hash           *payload;       /**< string data carried by this particle */
    Eina_Inlist         *merged;        /**< list of merged particles */
    Eina_Array          *link_fields;   /**< fields used to generate the link value */
    Eina_Stringshare    *link_value;    /**< computed from link_fields and paylod, used for pearing particles */
};

/**
 * @brief Free allocated resources.
 *
 * @param particle The Eiotas_Particle to free.
 *
 * This function will free all the merged Eiotas_Particle
 */
void eiotas_particle_free(Eiotas_Particle *particle);

/**
 * @brief Allocate the resources.
 *
 * @return the new allocated Eiotas_Particle @c NULL on failure
 */
Eiotas_Particle* eiotas_particle_alloc();

/**
 * @brief Reset the Eiotas_Particle so that it can be required later.
 *
 * @param particle The Eiotas_Particle to reset
 */
EAPI void eiotas_particle_reset(Eiotas_Particle *particle);

/**
 * @brief Set @c src and @c ts timestamp.
 *
 * @param particle The Eiotas_Particle to init
 * @param iota The Eiotas_Iota wich will be set as @c src
 */
EAPI void eiotas_particle_init(Eiotas_Particle *particle, Eiotas_Iota *iota);

/**
 * @brief Merge a particle into the other.
 *
 * @param particle The Eiotas_Particle to hold @p p
 * @param p The Eiotas_Particle to be merged into @p particle
 */
EAPI void eiotas_particle_merge(Eiotas_Particle *particle, Eiotas_Particle *p);

/**
 * @brief Add destinations to the Eiotas_Particle
 *
 * @param particle The Eiotas_Particle to add destinations to
 * @param destinations A comma separated list of destination "/room0/room1/.../doorx?action"
 *
 * This function will append each destination found to the destination list of the Eiotas_Particle.
 */
EAPI void eiotas_particle_add_destinations(Eiotas_Particle *particle, char* destinations);

#endif // __EIOTAS_PARTICLE_H__
