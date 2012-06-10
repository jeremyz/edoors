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

#include "edoors_main.h"
#include "edoors_private.h"

#include "eina_main.h"
#include <stdio.h>

static int _edoors_main_count = 0;

int _edoors_log_dom;

static Edoors_Version _version = { VMAJ, VMIN, VMIC };

EAPI Edoors_Version *edoors_version = &_version;

EAPI int edoors_init()
{
    if (EINA_LIKELY(_edoors_main_count > 0))
      return ++_edoors_main_count;

    if(!eina_init()) {
        fprintf(stderr,"Error during the initialization of Eina_Log module\n");
        return EXIT_FAILURE;
    }

    _edoors_log_dom = eina_log_domain_register("edoors", EINA_COLOR_CYAN);
    _edoors_main_count = 1;

    return 1;
}

EAPI int edoors_shutdown()
{
   _edoors_main_count--;
   if (EINA_UNLIKELY(_edoors_main_count == 0)) {
       eina_shutdown();
   }

   return _edoors_main_count;
}

