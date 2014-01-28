/**
 * This file, alder_segment_cite.c, is part of alder-segment.
 *
 * Copyright 2013 by Sang Chul Choi
 *
 * alder-segment is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * alder-segment is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with alder-segment.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "alder_segment_cite.h" 

static const char *alder_segment_cite_description = "Author et al 2013.";

void alder_segment_cite()
{
    printf("%s\n", alder_segment_cite_description);
}
