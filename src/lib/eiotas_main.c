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

#ifdef HAVE_CONFIG_H
# include "eina_config.h"
#endif

#include "eiotas_main.h"
#include "eiotas_private.h"
#include <stdio.h>

int _eiotas_log_dom;

static Eiotas_Version _version = { VMAJ, VMIN, VMIC };

EAPI Eiotas_Version *eiotas_version = &_version;

EAPI int eiotas_init()
{
    if(!eina_init()) {
        fprintf(stderr,"Error during the initialization of Eina_Log module\n");
        return EXIT_FAILURE;
    }
    _eiotas_log_dom = eina_log_domain_register("eiotas", EINA_COLOR_CYAN);
    return EXIT_SUCCESS;
}

EAPI int eiotas_shutdown()
{
    return eina_shutdown();
}

