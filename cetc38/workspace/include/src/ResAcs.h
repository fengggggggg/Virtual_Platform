
#ifndef _RES_ACS_H
#define _RES_ACS_H

bool RdSpecificReg(DSPU32 p_u32SpecRegAddr,DSPU32 p_units, DSPU32 *p_pValue);
bool WrSpecificReg(DSPU32 p_u32SpecRegAddr,DSPU32 p_units, DSPU32 p_u32Value);
bool JTAGWrSpecificReg(DSPU32 p_u32SpecRegAddr, DSPU32 p_units, DSPU32 p_u32Value);
bool JTAGRdSpecificReg(DSPU32 p_u32SpecRegAddr, DSPU32 p_units,  DSPU32 *p_pValue);


#endif


