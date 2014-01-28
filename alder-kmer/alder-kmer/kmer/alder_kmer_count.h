/**
 * This file, alder_kmer_count.h, is part of alder-kmer.
 *
 * Copyright 2013 by Sang Chul Choi
 *
 * alder-kmer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * alder-kmer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with alder-kmer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef alder_kmer_alder_kmer_count_h
#define alder_kmer_alder_kmer_count_h

#include <stdint.h>
#include "bstrlib.h"

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

int
alder_kmer_count(long version,
                 int K, long totalmaxkmer, long D, long M,
                 long min_M_table, long max_M_table,
                 long F,
                 long sizeInbuffer,
                 long sizeOutbuffer,
                 int n_ni, int n_np,
                 int n_nh,
                 int n_nt,
                 int progress_flag,
                 int progressToErro_flag,
                 int nopack_flag,
                 int no_delete_partition_flag,
                 int no_partition_flag,
                 int do_partition_flag,
                 struct bstrList *infile,
                 unsigned int outfile_given,
                 const char *outdir,
                 const char *outfile);

int
alder_kmer_count_withPartition(long version,
                               int i_ni, int K, long M, long F,
                               long sizeInbuffer,
                               long sizeOutbuffer,
                               int n_ni, int n_np,
                               int n_nh,
                               int n_thread,
                               int progress_flag,
                               int progressToError_flag,
                               int nopack_flag,
                               struct bstrList *infile,
                               unsigned int outfile_given,
                               const char *outdir,
                               const char *outfile);

int
alder_kmer_partition(long version,
                     int K, long D, long M,
                     long min_M_table, long max_M_table,
                     long F,
                     long sizeInbuffer,
                     long sizeOutbuffer,
                     int n_ni, int n_np,
                     int n_nh,
                     int n_nt,
                     int progress_flag,
                     int progressToError_flag,
                     struct bstrList *infile,
                     unsigned int outfile_given,
                     const char *outdir,
                     const char *outfile);



__END_DECLS


#endif /* alder_kmer_alder_kmer_count_h */