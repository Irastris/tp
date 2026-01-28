// #include "d/dolzel.h"
#include <cstring> // <string>
/* #include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/J2DGraph/J2DTextBox.h" */
#include "JSystem/JUtility/JUTResFont.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "d/d_error_msg.h"
/* #include "m_Do/m_Do_Reset.h"
#include "m_Do/m_Do_graphic.h"

#include "assets/black_tex.h"
#include "assets/msg_data.h"
#if VERSION == VERSION_GCN_PAL
#include "assets/msg_data_ge.h"
#include "assets/msg_data_fr.h"
#include "assets/msg_data_sp.h"
#include "assets/msg_data_it.h"
#endif
#include "assets/font_data.h"

#define MSG_READING_DISC 0
#define MSG_COVER_OPEN   1
#define MSG_NO_DISK      2
#define MSG_WRONG_DISK   3
#define MSG_READ_ERROR   4
#define MSG_FATAL_ERROR  5

struct BMG_INF1 : JUTDataBlockHeader {
    u8 m08[0x10 - 0x08];
    u32 entries[6];
};

#if (VERSION == VERSION_GCN_JPN) || (VERSION == VERSION_WII_JPN)
#define LINE_HEIGHT 30.0f
#define LINE_SPACE  30.0f
#define CHAR_SPACE  3.0f
#else
#define LINE_HEIGHT 23.0f
#define LINE_SPACE  23.0f
#define CHAR_SPACE  1.0f
#endif */

static void messageSet(u32 status, bool i_drawBg) {
    std::cout << "messageSet() is stubbed" << std::endl;
}

void dDvdErrorMsg_c::draw(s32 status) {
    std::cout << "dDvdErrorMsg_c::draw() is stubbed" << std::endl;
}

bool dDvdErrorMsg_c::execute() {
    std::cout << "dDvdErrorMsg_c::execute() is stubbed" << std::endl;
    return false;
}

static u8 l_captureAlpha = 0xFF;

static void drawCapture(u8 alpha) {
    std::cout << "drawCapture() is stubbed" << std::endl;
}

bool dShutdownErrorMsg_c::execute() {
    std::cout << "dShutdownErrorMsg_c::execute() is stubbed" << std::endl;
    return false;
}