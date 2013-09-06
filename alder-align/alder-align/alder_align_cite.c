/**
 * This file, alder_align_cite.c, is part of alder-align.
 *
 * Copyright 2013 by Sang Chul Choi
 *
 * alder-align is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * alder-align is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with alder-align.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "alder_align_cite.h"

static const char *alder_align_cite_description = "We will have a paper of this method.";

void alder_align_cite()
{
    printf("%s\n", alder_align_cite_description);
}
