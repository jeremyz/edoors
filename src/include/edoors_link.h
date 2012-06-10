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

#ifndef __EDOORS_LINK_H__
#define __EDOORS_LINK_H__

/**
 * @typedef Edoors_Link
 * Type for a Link between @ref Edoors_Iota.
 */
typedef struct _Edoors_Link Edoors_Link;

/**
 * @struct _Edoors_Link
 * Struct for a Link between @ref Edoors_Iota.
 */
struct _Edoors_Link {
};

/**
 * @defgroup Edoors_Link Edoors_Link
 *
 * A Edoors_Link allows to apply a destination list to a @ref Edoors_Particle with no defined destination.
 *
 * @{
 */

/**
 * @brief Free allocated resources.
 *
 * @param link The @ref Edoors_Link to free.
 */
void edoors_link_free(Edoors_Link *link);

/**
 * @}
 */

#endif // __EDOORS_LINK_H__
