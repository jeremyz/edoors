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
    Eiotas_Particle *particle = (Eiotas_Particle*)malloc(sizeof(Eiotas_Particle));

    return particle;
}

void eiotas_particle_free(Eiotas_Particle *particle)
{
    DBG("Particle free 0x%X",(unsigned int)particle);

    free(particle);
}

