/**
 * This file, alder_align_option.h, is part of alder-align.
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

#ifndef alder_align_alder_align_option_h
#define alder_align_alder_align_option_h

#include "bstring/bstrlib.h"

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif


__BEGIN_DECLS

typedef struct {
    int is_stdin;
    int sparse_suffix_array_k;
    
    struct bstrList *refile;
    struct bstrList *infile;
    struct bstrList *outfile;
    bstring logfilename;
} alder_align_option_t;

void alder_align_option_init(alder_align_option_t *option);
void alder_align_option_free(alder_align_option_t *option);


__END_DECLS


#endif /* alder_align_alder_align_option_h */