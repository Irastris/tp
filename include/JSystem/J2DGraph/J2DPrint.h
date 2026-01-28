#ifndef J2DPRINT_H
#define J2DPRINT_H

#include "JSystem/J2DGraph/J2DTextBox.h"
#include <cstdarg>

class JUTFont;
class J2DPrint;

extern "C" f32 J2DPrint_print_alpha_va(J2DPrint*, u8, const char*, va_list);

class J2DPrint {
public:
    struct TSize {
        f32 field_0x0;
        f32 field_0x4;
    };

    J2DPrint(JUTFont*, JUtility::TColor, JUtility::TColor);

    void initiate();

    J2DPrint(JUTFont*, f32, f32, JUtility::TColor, JUtility::TColor, JUtility::TColor, JUtility::TColor);
    static u8* setBuffer(size_t);
    void setFontSize();
    void locate(f32, f32);
    f32 print(f32, f32, u8, char const*, ...);
    void printReturn(char const*, f32, f32, J2DTextBoxHBinding, J2DTextBoxVBinding, f32, f32, u8);
    f32 parse(u8 const*, int, int, u16*, J2DPrint::TSize&, u8, bool);
    void doCtrlCode(int);
    u16 doEscapeCode(u8 const**, u8);
    void initchar();
    s32 getNumberS32(u8 const**, s32, s32, int);
    f32 getNumberF32(u8 const**, f32, f32, int);

    virtual ~J2DPrint();

    JUTFont* getFont() const { return mFont; }
    f32 getCursorV() const { return mCursorV; }
    void setCharColor(JUtility::TColor color) { mCharColor = color; }
    void setGradColor(JUtility::TColor color) { mGradColor = color; }

    f32 print_va(u8 alpha, const char* fmt, va_list args) {
        return J2DPrint_print_alpha_va(this, alpha, fmt, args);
    }

    void setFontSize(f32 sizeX, f32 sizeY) {
        f32 x;
        if (sizeX > 0.0f) {
            x = sizeX;
        } else {
            x = 0.0f;
        }
        mFontSizeX = x;

        f32 y;
        if (sizeY > 0.0f) {
            y = sizeY;
        } else {
            y = 0.0f;
        }
        mFontSizeY = y;
    }

    static char* mStrBuff;
    static size_t mStrBuffSize;

private:
    void private_initiate(JUTFont*, f32, f32, JUtility::TColor, JUtility::TColor, JUtility::TColor, JUtility::TColor, bool);

    JUTFont* mFont;
    JUtility::TColor field_0x8;
    JUtility::TColor field_0xc;
    f32 field_0x10;
    f32 field_0x14;
    f32 mScaleX;
    f32 mScaleY;
    s16 field_0x20;
    bool field_0x22;
    f32 field_0x24;
    f32 field_0x28;
    f32 mCursorH;
    f32 mCursorV;
    f32 field_0x34;
    JUtility::TColor mBlackColor;
    JUtility::TColor mWhiteColor;
    JUtility::TColor mCharColor;
    JUtility::TColor mGradColor;
    f32 mCharSpacing;
    f32 mLineSpacing;
    f32 mFontSizeX;
    f32 mFontSizeY;
    s16 field_0x58;
    bool field_0x5a;
};

#endif
