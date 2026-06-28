#include "DSP28x_Project.h"

#define N 200

Uint16 sin_table[N] = {3750, 3867, 3985, 4102, 4219, 4336, 4452, 4568, 4682, 4796, 4908, 5020, 5130, 5239, 5346, 5452, 5556, 5658, 5759, 5857, 5954, 6048, 6140, 6229, 6317, 6401, 6483, 6562, 6639, 6713, 6783, 6851, 6916, 6977, 7036, 7091, 7143, 7191, 7236, 7278, 7316, 7351, 7382, 7409, 7433, 7453, 7470, 7483, 7492, 7498, 7500, 7498, 7492, 7483, 7470, 7453, 7433, 7409, 7382, 7351, 7316, 7278, 7236, 7191, 7143, 7091, 7036, 6977, 6916, 6851, 6783, 6713, 6639, 6562, 6483, 6401, 6317, 6229, 6140, 6048, 5954, 5857, 5759, 5658, 5556, 5452, 5346, 5239, 5130, 5020, 4908, 4796, 4682, 4568, 4452, 4336, 4219, 4102, 3985, 3867, 3750, 3632, 3514, 3397, 3280, 3163, 3047, 2931, 2817, 2703, 2591, 2479, 2369, 2260, 2153, 2047, 1943, 1841, 1740, 1642, 1545, 1451, 1359, 1270, 1182, 1098, 1016, 937, 860, 786, 716, 648, 583, 522, 463, 408, 356, 308, 263, 221, 183, 148, 117, 90, 66, 46, 29, 16, 7, 1, 0, 1, 7, 16, 29, 46, 66, 90, 117, 148, 183, 221, 263, 308, 356, 408, 463, 522, 583, 648, 716, 786, 860, 937, 1016, 1098, 1182, 1270, 1359, 1451, 1545, 1642, 1740, 1841, 1943, 2047, 2153, 2260, 2369, 2479, 2591, 2703, 2817, 2931, 3047, 3163, 3280, 3397, 3514, 3632};

Uint16 idx = 0;

void epwm_init(void);
__interrupt void epwm1_isr(void);

void main(void) {
    InitSysCtrl();

    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_isr;
    EDIS;

    epwm_init();

    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

    IER |= M_INT3;
    EINT;
    ERTM;

    while(1) {

    }
}

void epwm_init(void) {

    EPwm1Regs.TBPRD = 7500;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPA.half.CMPA = 3750;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
    EPwm1Regs.ETSEL.bit.INTEN = 1;
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED = 150;
    EPwm1Regs.DBFED = 150;

    EPwm2Regs.TBPRD = 7500;

    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPA.half.CMPA = 3750;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
    EPwm2Regs.ETSEL.bit.INTEN = 1;
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm3Regs.TBPRD = 7500;

    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.CMPA.half.CMPA = 3750;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
    EPwm3Regs.ETSEL.bit.INTEN = 1;
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;

}

__interrupt void epwm1_isr(void) {
    EPwm1Regs.CMPA.half.CMPA = sin_table[idx];
    EPwm2Regs.CMPA.half.CMPA = sin_table[(idx + N/3) % N];
    EPwm3Regs.CMPA.half.CMPA = sin_table[(idx + 2*N/3) % N];

    idx = (idx + 1) % N;

    EPwm1Regs.ETCLR.bit.INT = 1;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
