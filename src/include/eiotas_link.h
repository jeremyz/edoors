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

#ifndef __EIOTAS_LINK_H__
#define __EIOTAS_LINK_H__

/**
 * @typedef Eiotas_Link
 * Type for a Link between @ref Eiotas_Iota.
 */
typedef struct _Eiotas_Link Eiotas_Link;

/**
 * @struct _Eiotas_Link
 * Struct for a Link between @ref Eiotas_Iota.
 */
struct _Eiotas_Link {
};

/**
 * @defgroup Eiotas_Link Eiotas_Link
 *
 * A Eiota_Link allows to apply a destination list to a @ref Eiotas_Particle with no defined destination.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param link The @ref Eiotas_Link to free.
 */
void eiotas_link_free(Eiotas_Link *link);

/**
 * @}
 */

#endif // __EIOTAS_LINK_H__
