#ifndef C_API_H
#define C_API_H

typedef void (*cAPIGph_Mthd)(void);

struct cAPI_Interface {
    cAPIGph_Mthd createMtd;
    cAPIGph_Mthd beforeOfDrawMtd;
    cAPIGph_Mthd afterOfDrawMtd;
    cAPIGph_Mthd painterMtd;
    cAPIGph_Mthd blankingOnMtd;
    cAPIGph_Mthd blankingOffMtd;
};

extern cAPI_Interface g_cAPI_Interface;

#endif
