
#ifndef _BPB_H
#define _BPB_H

void ResetBPB();
void WriteBPB(DSPU32 p_u32PC, DSPU32 p_u32Value);
DSPU32 CalcBPB(DSPU32 p_u32BPBValue, bool p_bolBraTaken);
DSPU32 ReadBPB(DSPU32 p_u32PC);
bool IsBTakenLast(DSPU32 p_u32BPBValue);


#endif


