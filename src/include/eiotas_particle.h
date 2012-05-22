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

#include <eina_types.h>
#include <eina_stringshare.h>

typedef struct _Eiotas_Particle Eiotas_Particle;

struct _Eiotas_Particle {
    Eina_Stringshare *src;      /* TODO */
};

Eiotas_Particle* eiotas_particle_alloc();

#endif // __EIOTAS_PARTICLE_H__
