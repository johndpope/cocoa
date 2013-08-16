#include "IncludeDefine.h"
#include "Parameters.h"
#include "Transcript.h"
#include "extendAlign.h"

bool extendAlign( char* R, char* Q, char* G, uint rStart, uint gStart, int dR, int dG, uint L, uint Lprev, uint nMMprev, uint nMMmax, double pMMmax, Transcript* trA ) {

// find the maximum score
    
int iS,iG;
    
int Score=0, nMatch=0, nMM=0;
trA->maxScore=0;

R=R+rStart;
Q=Q+rStart;
G=G+gStart;

for (int i=0;i<(int) L;i++) {
    iS=dR*i;
    iG=dG*i;
    
    if (G[iG]==5 || R[iS]==MARK_FRAG_SPACER_BASE) break; //no extension through chr boundary, or through the spacer between fragments
    if (R[iS]>3 || G[iG]>3) continue;//no penalties for Ns in reads or genome
    
    if (G[iG]==R[iS]) {//Match
        nMatch++;        
        Score += int(Q[iS]);
        if (Score>trA->maxScore) {//record new maximum
            if (nMM+nMMprev <= min(pMMmax*double(Lprev+i+1), double(nMMmax)) ) {//check nMM, if too many mismatches - do not record this maximum. Do not break - there might be still hope to make a long extension
                trA->extendL=i+1;
                trA->maxScore=Score;
                trA->nMatch=nMatch;
                trA->nMM=nMM;
            }; 
        };    
    } else {//MM
        if (nMM+nMMprev >= min(pMMmax*double(Lprev+L), double(nMMmax)) ) {//there is no hope to extend it further, break      
            break;
        };
      
        nMM++;  
        Score -= int(Q[iS]);
    };
};

// decide of the extension worked
bool extDone =  trA->extendL > 0; 

return extDone;

};

