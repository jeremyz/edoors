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

#ifndef __EDOORS_MAIN_H__
#define __EDOORS_MAIN_H__

#include <eina_types.h>

/**
 * @typedef Edoors_Version
 * Type for the version of Edoors.
 */
typedef struct _Edoors_Version Edoors_Version;

/**
 * @struct _Edoors_Version
 * Struct version of Edoors.
 */
struct _Edoors_Version
{
   int major;    /**< Major component of the version */
   int minor;    /**< Minor component of the version */
   int micro;    /**< Micro component of the version */
};

EAPI extern Edoors_Version *edoors_version;

EAPI extern int _edoors_log_dom;

/**
 * @defgroup Edoors_Main Edoors
 *
 * @{
 */

/**
 * @brief Initialize the Edoors library.
 *
 * @return 1 or greater on success, 0 on error.
 *
 * This function sets up all the edoors modules. It returns 0 on
 * failure (that is, when one of the module fails to initialize),
 * otherwise it returns the number of times it has already been
 * called.
 *
 * When Edoors is not used anymore, call edoors_shutdown() to shut down
 * the Edoorslibrary.
 */
EAPI int edoors_init();

/**
 * @brief Shut down the Edoors library.
 *
 * @return 0 when all the modules are completely shut down, 1 or
 * greater otherwise.
 *
 * This function shuts down the Edoors library. It returns 0 when it has
 * been called the same number of times than edoors_init(). In that case
 * it shut down all the Edoors modules.
 *
 * Once this function succeeds (that is, @c 0 is returned), you must
 * not call any of the Edoors function anymore. You must call
 * edoors_init() again to use the Edoors functions again.
 */
EAPI int edoors_shutdown();

/**
 * @}
 */

#endif // __EDOORS_MAIN_H__
