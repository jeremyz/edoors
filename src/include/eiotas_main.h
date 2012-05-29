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

#ifndef __EIOTAS_MAIN_H__
#define __EIOTAS_MAIN_H__

#include <eina_types.h>

/**
 * @typedef Eiotas_Version
 * The version of Eiotas.
 */
typedef struct _Eiotas_Version
{
   int major;    /**< Major component of the version */
   int minor;    /**< Minor component of the version */
   int micro;    /**< Micro component of the version */
} Eiotas_Version;

EAPI extern Eiotas_Version *eiotas_version;

EAPI extern int _eiotas_log_dom;

/**
 * @brief Initialize the Eiotas library.
 *
 * @return 1 or greater on success, 0 on error.
 *
 * This function sets up all the eiotas modules. It returns 0 on
 * failure (that is, when one of the module fails to initialize),
 * otherwise it returns the number of times it has already been
 * called.
 *
 * When Eiotas is not used anymore, call eiotas_shutdown() to shut down
 * the Eiotaslibrary.
 */
EAPI int eiotas_init();

/**
 * @brief Shut down the Eiotas library.
 *
 * @return 0 when all the modules are completely shut down, 1 or
 * greater otherwise.
 *
 * This function shuts down the Eiotas library. It returns 0 when it has
 * been called the same number of times than eiotas_init(). In that case
 * it shut down all the Eiotas modules.
 *
 * Once this function succeeds (that is, @c 0 is returned), you must
 * not call any of the Eiotas function anymore. You must call
 * eiotas_init() again to use the Eiotas functions again.
 */
EAPI int eiotas_shutdown();

#endif // __EIOTAS_MAIN_H__
