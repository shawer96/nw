#include "nw.h"

#define MATCH_SCORE 1
#define MISMATCH_SCORE -1
#define GAP_SCORE -1

#define ALIGN '\\'
#define SKIPA '^'
#define SKIPB '<'

#define MAX(A,B) ( ((A)>(B))?(A):(B) )
#define MIN(A,B) ( ((A)<(B))?(A):(B) )
#define NPE 4

void needwun(char SEQA[ALEN], char SEQB[BLEN],
             char alignedA[ALEN+BLEN], char alignedB[ALEN+BLEN],
             int M[(ALEN+1)*(BLEN+1)], char ptr[(ALEN+1)*(BLEN+1)]){

    int score, up_left, up, left, max;
    int row, row_up, r;
    int a_idx, b_idx;
    int a_str_idx, b_str_idx;

    int iMaxLength = MAX(ALEN, BLEN);
    int iMinLength = MIN(ALEN, BLEN);

    init_row: for(a_idx=0; a_idx<(ALEN+1); a_idx++){
        M[a_idx] = a_idx * GAP_SCORE;
    }
    init_col: for(b_idx=0; b_idx<(BLEN+1); b_idx++){
        M[b_idx*(ALEN+1)] = b_idx * GAP_SCORE;
    }

    // Matrix filling loop
    // fill_out: for(b_idx=1; b_idx<(BLEN+1); b_idx++){
    //     fill_in: for(a_idx=1; a_idx<(ALEN+1); a_idx++){
    //         if(SEQA[a_idx-1] == SEQB[b_idx-1]){
    //             score = MATCH_SCORE;
    //         } else {
    //             score = MISMATCH_SCORE;
    //         }

    //         row_up = (b_idx-1)*(ALEN+1);
    //         row = (b_idx)*(ALEN+1);

    //         up_left = M[row_up + (a_idx-1)] + score;
    //         up      = M[row_up + (a_idx  )] + GAP_SCORE;
    //         left    = M[row    + (a_idx-1)] + GAP_SCORE;

    //         max = MAX(up_left, MAX(up, left));

    //         M[row + a_idx] = max;
    //         if(max == left){
    //             ptr[row + a_idx] = SKIPB;
    //         } else if(max == up){
    //             ptr[row + a_idx] = SKIPA;
    //         } else{
    //              ptr[row + a_idx] = ALIGN;
    //         }
    //     }
    // }


    for (int ik = 2; ik < ALEN + BLEN +2 ; ik++)
    {
        int ii;
        if (ik < MAX(ALEN, BLEN) + 1)   ii = 1;
        else ii = ik - iMaxLength;

        for (; ii < MIN(ik,iMinLength+1); ii = ii + NPE)
        {
            //ii  =======================================
                if(SEQB[ii-1] == SEQA[ik-ii-1]){
                    score = MATCH_SCORE;
                } else {
                    score = MISMATCH_SCORE;
                }

                row_up = (ii-1)*(ALEN+1);
                row = (ii)*(ALEN+1);

                up_left = M[row_up + (ik-ii-1)] + score;
                up      = M[row_up + (ik-ii  )] + GAP_SCORE;
                left    = M[row    + (ik-ii-1)] + GAP_SCORE;

                max = MAX(up_left, MAX(up, left));

                M[row + ik-ii] = max;
                if(max == left){
                    ptr[row + ik-ii] = SKIPB;
                } else if(max == up){
                    ptr[row + ik-ii] = SKIPA;
                } else{
                    ptr[row + ik-ii] = ALIGN;
                }
            //ii+1=========================================
            if ((ik - ii - 1 > 0) && (ii + 1 < iMinLength + 1))
            {
                if(SEQB[ii] == SEQA[ik-ii-2]){
                    score = MATCH_SCORE;
                } else {
                    score = MISMATCH_SCORE;
                }

                row_up = (ii)*(ALEN+1);
                row = (ii+1)*(ALEN+1);

                up_left = M[row_up + (ik-ii-2)] + score;
                up      = M[row_up + (ik-ii-1)] + GAP_SCORE;
                left    = M[row    + (ik-ii-2)] + GAP_SCORE;

                max = MAX(up_left, MAX(up, left));

                M[row + ik-ii-1] = max;
                if(max == left){
                    ptr[row + ik-ii-1] = SKIPB;
                } else if(max == up){
                    ptr[row + ik-ii-1] = SKIPA;
                } else{
                     ptr[row + ik-ii-1] = ALIGN;
                }
            }
            //ii+2==========================================
            if ((ik - ii - 2 > 0) && (ii + 2 < iMinLength + 1))
            {
                if(SEQB[ii+1] == SEQA[ik-ii-3]){
                    score = MATCH_SCORE;
                } else {
                    score = MISMATCH_SCORE;
                }

                row_up = (ii+1)*(ALEN+1);
                row = (ii+2)*(ALEN+1);

                up_left = M[row_up + (ik-ii-3)] + score;
                up      = M[row_up + (ik-ii-2)] + GAP_SCORE;
                left    = M[row    + (ik-ii-3)] + GAP_SCORE;

                max = MAX(up_left, MAX(up, left));

                M[row + ik-ii-2] = max;
                if(max == left){
                    ptr[row + ik-ii-2] = SKIPB;
                } else if(max == up){
                    ptr[row + ik-ii-2] = SKIPA;
                } else{
                     ptr[row + ik-ii-2] = ALIGN;
                }
            }
            //ii+3==========================================
            if ((ik - ii - 3 > 0) && (ii + 3 < iMinLength + 1))
            {
                if(SEQB[ii+2] == SEQA[ik-ii-4]){
                    score = MATCH_SCORE;
                } else {
                    score = MISMATCH_SCORE;
                }

                row_up = (ii+2)*(ALEN+1);
                row = (ii+3)*(ALEN+1);

                up_left = M[row_up + (ik-ii-4)] + score;
                up      = M[row_up + (ik-ii-3)] + GAP_SCORE;
                left    = M[row    + (ik-ii-4)] + GAP_SCORE;

                max = MAX(up_left, MAX(up, left));

                M[row + ik-ii-3] = max;
                if(max == left){
                    ptr[row + ik-ii-3] = SKIPB;
                } else if(max == up){
                    ptr[row + ik-ii-3] = SKIPA;
                } else{
                     ptr[row + ik-ii-3] = ALIGN;
                }
            }
        }
    }

    // TraceBack (n.b. aligned sequences are backwards to avoid string appending)
    a_idx = ALEN;
    b_idx = BLEN;
    a_str_idx = 0;
    b_str_idx = 0;

    trace: while(a_idx>0 || b_idx>0) {
        r = b_idx*(ALEN+1);
        if (ptr[r + a_idx] == ALIGN){
            alignedA[a_str_idx++] = SEQA[a_idx-1];
            alignedB[b_str_idx++] = SEQB[b_idx-1];
            a_idx--;
            b_idx--;
        }
        else if (ptr[r + a_idx] == SKIPB){
            alignedA[a_str_idx++] = SEQA[a_idx-1];
            alignedB[b_str_idx++] = '-';
            a_idx--;
        }
        else{ // SKIPA
            alignedA[a_str_idx++] = '-';
            alignedB[b_str_idx++] = SEQB[b_idx-1];
            b_idx--;
        }
    }

    // Pad the result
    pad_a: for( ; a_str_idx<ALEN+BLEN; a_str_idx++ ) {
      alignedA[a_str_idx] = '_';
    }
    pad_b: for( ; b_str_idx<ALEN+BLEN; b_str_idx++ ) {
      alignedB[b_str_idx] = '_';
    }
}
