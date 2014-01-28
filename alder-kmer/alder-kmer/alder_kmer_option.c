/**
 * This file, alder_kmer_option.c, is part of alder-kmer.
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

#include <assert.h>
#include <stdint.h>
#include "cmdline.h"
#include "alder_logger.h"
#include "alder_kmer_simulate.h"
#include "alder_cmacro.h"
#include "bstrmore.h"
#include "alder_file.h"
#include "alder_file_isstdin.h"
#include "alder_kmer_cite.h" 
#include "alder_kmer_option.h" 

#define MAXKMER 100000000

static void alder_kmer_cmdline_parser_print_help_init(alder_kmer_option_t *o,
                                                      struct gengetopt_args_info *a)
{
    const int number_help_line = 1;
    char line[ALDER_HELP_LINE_SIZE];
    o->help = bstrVectorCreate(number_help_line);
    if (o->help == NULL) {
        return;
    }
    sprintf(line,
            "      --disk=INT               maximum disk space in MB\n"
            "                               on [--outdir=%s] (default=`%ld')",
            a->outdir_arg,
            a->disk_arg);
    bstrVectorAdd(o->help, line);
    
    sprintf(line,
            "      --memory=INT             maximum memory in MB (default=`%ld')",
            a->memory_arg);
    bstrVectorAdd(o->help, line);
    
    sprintf(line,
            "  -t, --nthread=INT            number of threads  (default=`%ld')",
            a->nthread_arg);
    bstrVectorAdd(o->help, line);
}

/* This function prints the default help message.
 */
static void alder_kmer_cmdline_parser_print_help (alder_kmer_option_t *o)
{
    printf("%s\n", gengetopt_args_info_purpose);
    
    printf("\n%s\n", gengetopt_args_info_usage);
    
    printf("\n");
    
    printf("%s\n", gengetopt_args_info_description);
    
    int a[7] = {4,7,13,19,23,25,57};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

/* This function prints the detailed help message.
 */
static void alder_kmer_cmdline_parser_print_detailed_help (alder_kmer_option_t *o)
{
    my_cmdline_parser_print_version ();
    printf("\n%s\n", gengetopt_args_info_purpose);
    printf("\n%s\n", gengetopt_args_info_usage);
    printf("\n");
    printf("%s\n\n", gengetopt_args_info_description);
    
    int a[15] = {0,1,2,68,69,71,72,74,4,5,7,78,79,80,81};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
    printf("%s\n", bdata(o->help->entry[0]));
    printf("%s\n", bdata(o->help->entry[1]));
    printf("%s\n", bdata(o->help->entry[2]));
    
    int b[90] = {
        9,11,89,90,13,14,34,35,15,16,17,18,       // count
        19,20,23,24,85,86,80,81,13,14,            // dump
        25,26,28,57,13,14,                        // query
        29,30,7,78,32,33,34,35,36,37,38,88,13,14, // simulate
        40,41,7,78,79,80,81,9,11,13,14,34,35,     // partition
        45,46,7,13,14,                            // kmer/decode
        48,49,7,15,11,13,14,                      // table
        51,52,7,37,13,14,                         // list
        54,55,57,13,14,                           // match
        58,59,13,14,                              // binary
        61,62,13,14,                              // uncompress
        64,65,13,14                               // inspect
    };
    
    for (int i = 0; i < sizeof(b)/sizeof(b[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[b[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_examples_help (alder_kmer_option_t *o)
{
    printf("%s\n", gengetopt_args_info_detailed_help[96]);
}


static void alder_kmer_cmdline_parser_print_doc_help (alder_kmer_option_t *o)
{
    printf("%s\n", gengetopt_args_info_detailed_help[99]);
}

static void
alder_kmer_cmdline_parser_print_count_help (alder_kmer_option_t *o,
                                            struct gengetopt_args_info *a)
{
    printf("Usage: alder-kmer count [-kINT|-mINT|--kmer|--mer-len=INT]\n"
           "         [-tINT|--nthread=INT] [--disk=INT] [--memory=INT]\n"
           "         [--load-disk=REAL] [--load-memory=REAL] [-C|--canonical]\n"
           "         [-L|--lower-count=INT] [-U|--upper-count=INT]\n"
           "         [--min-table-memory=INT] [--max-table-memory=INT]\n"
           "         [--no-partition] [--no-count] [--no-delete]\n"
           "         [-ofilename|--outfile=filename] [--outdir=directory]\n"
           "         [--nh=INT] [--ni=INT] [--np=INT] [FILES]...\n");
    
    printf("%s\n", gengetopt_args_info_detailed_help[4]);
    printf("%s\n", gengetopt_args_info_detailed_help[5]);
    printf("%s\n", gengetopt_args_info_detailed_help[7]);
    printf("%s\n", gengetopt_args_info_detailed_help[78]);
    printf("%s\n", gengetopt_args_info_detailed_help[79]);
    printf("%s\n", gengetopt_args_info_detailed_help[80]);
    printf("%s\n", gengetopt_args_info_detailed_help[81]);
    printf("%s\n", bdata(o->help->entry[0]));
    printf("%s\n", gengetopt_args_info_detailed_help[9]);
    printf("%s\n", bdata(o->help->entry[1]));
    printf("%s\n", gengetopt_args_info_detailed_help[11]);
    printf("%s\n", bdata(o->help->entry[2]));
    printf("%s\n", gengetopt_args_info_detailed_help[89]);
    printf("%s\n", gengetopt_args_info_detailed_help[90]);
    printf("%s\n", gengetopt_args_info_detailed_help[13]);
    printf("%s\n", gengetopt_args_info_detailed_help[14]);
    printf("%s\n", gengetopt_args_info_detailed_help[34]);
    printf("%s\n", gengetopt_args_info_detailed_help[35]);
    printf("%s\n", gengetopt_args_info_detailed_help[15]);
    printf("%s\n", gengetopt_args_info_detailed_help[16]);
    printf("%s\n", gengetopt_args_info_detailed_help[17]);
    printf("%s\n", gengetopt_args_info_detailed_help[18]);
    
}

static void alder_kmer_cmdline_parser_print_report_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer dump [--fasta] [--no-tab]\n"
           "         [-L|--lower-count=INT] [-U|--upper-count=INT]\n"
           "         [FILE]\n");
    
    int a[10] = {19,20,23,24,85,86,80,81,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_query_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer query [--sequence=STRING] [--tabfile=FILENAME]\n"
           "         [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILES]...\n");
    
    int a[6] = {25,26,28,57,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_simulate_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer simulate [-kINT|-mINT|--kmer|--mer-len=INT]\n"
           "         [-ofilename|--outfile=filename] [--outdir=directory]\n"
           "         [--maxkmer=INT] [--format=STRING] [--ni=INT] [--np=INT] [--nf=INT]\n"
           "         [--with-parfile] [--seqlen=INT] [--seed=INT] [FILES]...\n");
   
    int a[14] = {29,30,7,78,32,33,34,35,36,37,38,88,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }   
}

static void alder_kmer_cmdline_parser_print_partition_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer partition [-kINT|-mINT|--kmer|--mer-len=INT]\n"
           "         [--ni=INT] [--np=INT]\n"
           "         [-tINT|--nthread|--threads=INT] [--disk=INT] [--memory=INT]\n"
           "         [--load-disk=REAL] [--load-memory=REAL] [-C|--canonical]\n"
           "         [-L|--lower-count=INT] [-U|--upper-count=INT]\n"
           "         [-ofilename|--outfile=filename] [--outdir=directory]\n"
           "         [FILES]...\n");
    
    printf("%s\n", gengetopt_args_info_detailed_help[40]);
    printf("%s\n", gengetopt_args_info_detailed_help[41]);
    printf("%s\n", gengetopt_args_info_detailed_help[7]);
    printf("%s\n", gengetopt_args_info_detailed_help[78]);
    printf("%s\n", gengetopt_args_info_detailed_help[79]);
    printf("%s\n", gengetopt_args_info_detailed_help[80]);
    printf("%s\n", gengetopt_args_info_detailed_help[81]);
    printf("%s\n", bdata(o->help->entry[0]));
    printf("%s\n", gengetopt_args_info_detailed_help[9]);
    printf("%s\n", bdata(o->help->entry[1]));
    printf("%s\n", gengetopt_args_info_detailed_help[11]);
    printf("%s\n", bdata(o->help->entry[2]));
    printf("%s\n", gengetopt_args_info_detailed_help[13]);
    printf("%s\n", gengetopt_args_info_detailed_help[14]);
    printf("%s\n", gengetopt_args_info_detailed_help[34]);
    printf("%s\n", gengetopt_args_info_detailed_help[35]);
}

static void alder_kmer_cmdline_parser_print_decode_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer kmer [-kINT|--kmer=INT] [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILES]...\n");
    
    int a[5] = {45,46,7,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_table_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer table [-kINT|--kmer=INT] [--nh=INT] [-mINT|--memory=INT]\n"
           "         [-tINT|--nthread=INT] [--load-memory=REAL] [--outdir=directory]\n"
           "         [-ofilename|--outfile=filename] [FILES]...\n");
    
    printf("%s\n", gengetopt_args_info_detailed_help[48]);
    printf("%s\n", gengetopt_args_info_detailed_help[49]);
    printf("%s\n", gengetopt_args_info_detailed_help[7]);
    printf("%s\n", gengetopt_args_info_detailed_help[15]);
    printf("%s\n", bdata(o->help->entry[1]));
    printf("%s\n", gengetopt_args_info_detailed_help[11]);
    printf("%s\n", bdata(o->help->entry[2]));
    printf("%s\n", gengetopt_args_info_detailed_help[13]);
    printf("%s\n", gengetopt_args_info_detailed_help[14]);
    
}

static void alder_kmer_cmdline_parser_print_list_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer list [-kINT|--kmer=INT] [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [--seqlen=INT] [FILE]\n");
    
    int a[6] = {51,52,7,37,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_match_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer match [--tabfile=filename] [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILES]...\n");
    
    int a[5] = {54,55,57,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_binary_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer binary [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILES]...\n");
    
    int a[4] = {58,59,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_uncompress_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer uncompress [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILES]...\n");
    
    int a[4] = {61,62,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}

static void alder_kmer_cmdline_parser_print_inspect_help (alder_kmer_option_t *o)
{
    printf("Usage: alder-kmer inspect [-ofilename|--outfile=filename]\n"
           "         [--outdir=directory] [FILE]\n");
    
    int a[4] = {64,659,13,14};
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
        printf("%s\n", gengetopt_args_info_detailed_help[a[i]]);
    }
}


/* This function converts gengetopt to alder_kmer_option just for my
 * convenience.
 */
int alder_kmer_option_init(alder_kmer_option_t *o,
                           struct gengetopt_args_info *a,
                           int argc)
{
    int status = 0;
    o->infile = NULL;
    o->help = NULL;
    
    /* Simple runs or error checking without requiring much execution. */
    if (a->cite_given) {
        alder_kmer_cite();
        status = 1;
        return status;
    }
    if (a->document_flag) {
        alder_kmer_cmdline_parser_print_doc_help (o);
        return ALDER_STATUS_ERROR;
    }
    
    if (a->maxkmer_arg > MAXKMER) {
        fprintf(stderr,
                "Error: maxcount of slots in a hash table greater than %d\n",
                MAXKMER);
        fprintf(stderr, "Suggestion: use values less than or equal to %d.\n",
                MAXKMER);
        status = 1;
        return status;
    }
    if (a->seqlen_arg < a->kmer_arg) {
        fprintf(stderr,
                "Error: sequence length must be greater than or equal to "
                "kmer length; seqlen=%ld, kmer=%ld\n",
                a->seqlen_arg, a->kmer_arg);
        fprintf(stderr, "Suggestion: use --seqlen or --kmer to let sequence "
                "length be greater, or kmer size be smaller.\n");
        status = 1;
        return status;
    }
    if (!(0 < a->kmer_arg)) {
        fprintf(stderr, "Error: a negative kmer=%ld\n", a->kmer_arg);
        fprintf(stderr, "Suggestion: use a positive value of --kmer!\n");
        status = 1;
        return status;
    }
    if (a->format_arg == format_arg_fasta ||
        a->format_arg == format_arg_fa) {
        o->format = ALDER_FORMAT_FASTA;
    } else if (a->format_arg == format_arg_fastq ||
               a->format_arg == format_arg_fq) {
        o->format = ALDER_FORMAT_FASTQ;
    } else if (a->format_arg == format_arg_seq) {
        o->format = ALDER_FORMAT_SEQUENCE;
    }
    if (a->kmer_given && a->mer_len_given) {
        fprintf(stderr, "Error: ambiguous options\n");
        fprintf(stderr, "Suggestion: use only one of -k, -m, --kmer, or --mer-len\n");
        status = 1;
        return status;
    }
    if (a->mer_len_given) {
        a->kmer_arg = a->mer_len_arg;
    }
    if (a->release_flag) {
        switch (a->select_version_arg) {
            case 1:
                a->select_version_arg = 4;
                break;
            case 2:
                a->select_version_arg = 5;
                break;
            case 3:
                a->select_version_arg = 6;
                break;
            default:
                a->select_version_arg = 0;
                break;
        }
    }
    if (strcmp(a->outdir_arg,".")) {
        int s = alder_file_mkdir(a->outdir_arg);
        if (s != ALDER_STATUS_SUCCESS) {
            fprintf(stderr, "Error: failed to create directory: %s\n", a->outdir_arg);
            status = 1;
            return status;
        }
    }
    
    /* Free memory, free disk space, and maximum open files. */
    int64_t physical_memory = 0;
    int64_t free_memory = 0;
    int64_t used_memory = 0;
    if (!a->memory_given) {
        alder_file_availablememory(&physical_memory);
        alder_file_availablememory2(&free_memory, &used_memory);
        a->memory_arg = (long)(free_memory/ALDER_MB2BYTE);
    }
    unsigned long disk_space = 0;
    if (!a->disk_given) {
        alder_file_availablediskspace(a->outdir_arg, &disk_space);
        a->disk_arg = (long)(disk_space/ALDER_MB2BYTE);
    }
    if (!a->nthread_given) {
        a->nthread_arg = (long) alder_file_sysctl();
    }
    status = alder_file_availableopenfiles(&o->maxfile);
    o->maxfile -= 4;
    if (status == 1) {
        return status;
    }
    
    /* Adjust the disk and memory sizes. */
    a->disk_arg *= a->load_disk_arg;
    if (a->disk_arg < 10) {
        fprintf(stderr, "Error: disk space is less than 10MB.\n");
        fprintf(stderr, "Suggestion: use --disk to set a larger value.\n");
        return ALDER_STATUS_ERROR;
    }
    a->memory_arg *= a->load_memory_arg;
    if (a->memory_arg < 2) {
        fprintf(stderr, "Error: memory is less than 2MB.\n");
        fprintf(stderr, "Suggestion: use --memory to set a larger value.\n");
        return ALDER_STATUS_ERROR;
    }
    
    /* Initialize the help message. */
    alder_kmer_cmdline_parser_print_help_init(o,a);
    if (argc == 1) {
        printf("Usage: alder-kmer [command] -h\n");
        printf("Available commands: count, dump, query, simulate, partition, kmer,\n"
               "                    table, list, binary, uncompress, and inspect.\n");
        status = 1;
        return status;
    } else if (a->inputs_num == 0 && a->help_given) {
        alder_kmer_cmdline_parser_print_help (o);
        status = 1;
        return status;
    } else if (a->inputs_num == 0 && a->detailed_help_given) {
        alder_kmer_cmdline_parser_print_detailed_help(o);
        status = 1;
        return status;
    } 
    
    /* Command check */
    size_t inputs_num_start = 1;
    a->count_flag = 0;
    a->report_flag = 0;
    a->query_flag = 0;
    a->simulate_flag = 0;
    a->partition_flag = 0;
    a->decode_flag = 0;
    a->table_flag = 0;
    a->list_flag = 0;
    a->match_flag = 0;
    a->binary_flag = 0;
    a->uncompress_flag = 0;
    a->inspect_flag = 0;
    a->examples_flag = 0;
    if (!strcmp(a->inputs[0], "count") || *a->inputs[0] == 'c') {
        a->count_flag = 1;
    } else if (!strcmp(a->inputs[0], "kmer") || *a->inputs[0] == 'k') {
        a->decode_flag = 1;
    } else if (!strcmp(a->inputs[0], "report") || *a->inputs[0] == 'r') {
        a->report_flag = 1;
    } else if (!strcmp(a->inputs[0], "dump") || *a->inputs[0] == 'd') {
        a->report_flag = 1;
    } else if (!strcmp(a->inputs[0], "query") || *a->inputs[0] == 'q') {
        a->query_flag = 1;
    } else if (!strcmp(a->inputs[0], "simulate") || *a->inputs[0] == 's') {
        a->simulate_flag = 1;
    } else if (!strcmp(a->inputs[0], "partition") || *a->inputs[0] == 'p') {
        a->partition_flag = 1;
    } else if (!strcmp(a->inputs[0], "table") || *a->inputs[0] == 't') {
        a->table_flag = 1;
    } else if (!strcmp(a->inputs[0], "list") || *a->inputs[0] == 'l') {
        a->list_flag = 1;
    } else if (!strcmp(a->inputs[0], "match") || *a->inputs[0] == 'm') {
        a->match_flag = 1;
    } else if (!strcmp(a->inputs[0], "binary") || *a->inputs[0] == 'b') {
        a->binary_flag = 1;
    } else if (!strcmp(a->inputs[0], "uncompress") || *a->inputs[0] == 'u') {
        a->uncompress_flag = 1;
    } else if (!strcmp(a->inputs[0], "inspect") || *a->inputs[0] == 'i') {
        a->inspect_flag = 1;
    } else if (!strcmp(a->inputs[0], "examples") || *a->inputs[0] == 'e') {
        a->examples_flag = 1;
    } else {
        fprintf(stderr, "Error: the first argument must be a command.\n");
        fprintf(stderr, "Suggestion: use --help to find available commands.\n");
        status = 1;
        return status;
    }
    if (a->count_flag) {
        if (a->ni_given == 0) {
            a->ni_arg = -1;
        }
        if (a->np_given == 0) {
            a->np_arg = -1;
        }
        if (a->nh_given == 0) {
            a->nh_arg = -1;
        }
    }
    
    /* Help message for commands. */
    if (a->count_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_count_help(o,a);
        status = 1;
        return status;
    } else if (a->report_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_report_help(o);
        status = 1;
        return status;
    } else if (a->query_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_query_help(o);
        status = 1;
        return status;
    } else if (a->simulate_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_simulate_help(o);
        status = 1;
        return status;
    } else if (a->partition_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_partition_help(o);
        status = 1;
        return status;
    } else if (a->decode_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_decode_help(o);
        status = 1;
        return status;
    } else if (a->table_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_table_help(o);
        status = 1;
        return status;
    } else if (a->list_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_list_help(o);
        status = 1;
        return status;
    } else if (a->match_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_match_help(o);
        status = 1;
        return status;
    } else if (a->binary_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_binary_help(o);
        status = 1;
        return status;
    } else if (a->uncompress_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_uncompress_help(o);
        status = 1;
        return status;
    } else if (a->inspect_flag && a->help_given) {
        alder_kmer_cmdline_parser_print_inspect_help(o);
        status = 1;
        return status;
    } else if (a->examples_flag) {
        alder_kmer_cmdline_parser_print_examples_help(o);
        status = 1;
        return status;
    }
    
    /* Check of STDIN is unstable. */
    o->is_stdin = alder_file_isstdin();
    if (a->simulate_flag == 0) {
        if (status == 1) {
            return status;
        }
    }
    
    for (size_t i = inputs_num_start; i < a->inputs_num; i++) {
        int isExist = alder_file_exist(a->inputs[i]);
        if (isExist == 0) {
            fprintf(stderr, "Error: no such file %s\n", a->inputs[i]);
            status = 1;
            return status;
        }
    }
    
    if (a->inputs_num > 0) o->infile = bstrVectorCreate((int)(a->inputs_num));
    for (size_t i = inputs_num_start; i < a->inputs_num; i++) {
        bstrVectorAdd(o->infile, a->inputs[i]);
    }
    
    return status;
}

/**
 *  This function frees the option.
 *
 *  @param o alder-kmer option
 */
void alder_kmer_option_free(alder_kmer_option_t *o)
{
    if (o->infile != NULL) bstrListDestroy(o->infile);
    if (o->help != NULL) bstrListDestroy(o->help);
}
