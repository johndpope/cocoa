//
//  alder_const.h
//  alder-align
//
//  Created by Sang Chul Choi on 8/8/13.
//  Copyright (c) 2013 Sang Chul Choi. All rights reserved.
//

#ifndef alder_align_alder_const_h
#define alder_align_alder_const_h

#define ALDER_CONST_NUMBER (1) /* 1 */

#define uintWinBin unsigned short
#define uintWinBinMax numeric_limits<uint16>::max()


#define intSWscore int
#define intScore int

//cleaned

#if defined COMPILE_FOR_LONG_READS
#define MAX_N_EXONS 200
#else
#define MAX_N_EXONS 20
#endif

//input reads
#define MAX_N_MATES 2
#define MAX_READ_NAME_LENGTH 1000
#define EXIT_CODE_BUG 101
#define EXIT_CODE_PARAMETER 102
#define EXIT_CODE_RUNTIME 103
#define EXIT_CODE_INPUT_FILES 104
#define EXIT_CODE_GENOME_FILES 105
#define EXIT_CODE_SHM 106
#define EXIT_CODE_GenomeLoadingWaitedTooLong 107
#define EXIT_CODE_MemoryAllocation 108

//cleaned-end


//exit codes
#define EXIT_createExtendWindowsWithAlign_TOO_MANY_WINDOWS 101

#define SJ_MOTIF_SIZE 7 //number of recorded SJ motifs
#define SJ_SAM_AnnotatedMotifShift 20

#define EXTEND_ORDER 1 //1-first extend to the 5' of the read, then 3'; 2- first extend to the left, then to the right

#define MAX_READ_LENGTH 10000
#define MAX_N_FRAG 2
#define MARK_FRAG_SPACER_BASE 11
#define MAX_N_CHIMERAS 5
#define MAX_N_MULTMAP 10000 //max number of multiple mappers
#define MAX_SJ_REPEAT_SEARCH 255 //max length of a repeat to search around a SJ
#define MAX_QS_VALUE 60
#define MAX_OUTPUT_FLAG 10

#define PC_rStart 0
#define PC_Length 1
#define PC_Str 2
#define PC_Dir 3
#define PC_Nrep 4
#define PC_SAstart 5
#define PC_SAend 6
#define PC_iFrag 7
#define PC_SIZE 8

#define WC_Str 0
#define WC_Chr 1
#define WC_gStart 2
#define WC_gEnd 3
#define WC_SIZE 4

#define WA_Length 0
#define WA_rStart 1
#define WA_gStart 2
#define WA_Nrep 3
#define WA_Anchor 4
#define WA_iFrag 5
#define WA_sjA 6
#define WA_SIZE 7

#define EX_R 0
#define EX_G 1
#define EX_L 2
#define EX_iFrag 3
#define EX_sjA 4
#define EX_SIZE 5

//mapType
#define MT_PE 0 //paired end type
#define MT_SIZE 5

#define MARKER_ALL_PIECES_EXCEED_seedMultimapNmax 999901 //marks the reads that map too many time, more than seedMultimapNmax
#define MARKER_NO_UNIQUE_PIECES 999902 //the best transcript does not contain any unique pieces
#define MARKER_NO_GOOD_WINDOW 999903 //did not find any good windows
#define MARKER_NO_GOOD_PIECES 999904
#define MARKER_TOO_MANY_ANCHORS_PER_WINDOW 999905
#define MARKER_MAX_N_MULT_EXCEEDED 999906
#define MARKER_FULL_LENGTH_MULTIMAPPER_EXCEEDED_alignWindowsPerReadNmax 999907
#define MARKER_ALL_PIECES_EXCEEDED_winAnchorMultimapNmax 999908
#define MARKER_TOO_MANY_CHIMERAS 999909
#define MARKER_READ_TOO_SHORT 999910

#define PEMARKER_SINGLE_END 0
#define PEMARKER_PAIR 1
#define PEMARKER_ONE_END 3
#define PEMARKER_TOO_MANY_PAIRS 5
#define PEMARKER_CHIMERIC_PAIRS 7
#define PEMARKER_CHIMERIC_SJ_READ1 221
#define PEMARKER_CHIMERIC_SJ_READ2 223
#define PEMARKER_CHIMERIC_SJ_READ1and2 225
#define PEMARKER_SINGLE_END_NOTMAPPED 1001

//
//typedef uint uiPC[PC_SIZE];
//typedef uint uiWC[WC_SIZE];
//typedef uint uiWA[WA_SIZE];

// debugging
//#define DEBUG_Nread 1000000
//#define DEBUG
#if defined DEBUG
#define DEBUG_stitch
#define DEBUG_Nread 200000
#define DEBUG_NreadStart 1
#define DEBUG_extend
#endif

// #define DEBUG_NreadStart 500000

#endif
