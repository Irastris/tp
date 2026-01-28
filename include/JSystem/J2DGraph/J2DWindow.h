#ifndef J2DWINDOW_H
#define J2DWINDOW_H

#include "JSystem/J2DGraph/J2DMaterial.h"
#include "JSystem/J2DGraph/J2DPane.h"

class JSURandomInputStream;
class JUTTexture;

enum J2DTextureBase {
    TEXTUREBASE_0 = 0,
    TEXTUREBASE_1 = 1,
    TEXTUREBASE_2 = 2,
    TEXTUREBASE_3 = 3,
};

enum J2DWindowMirror {
    WINDOWMIRROR_39 = 39,
    WINDOWMIRROR_114 = 114,
    WINDOWMIRROR_141 = 141,
    WINDOWMIRROR_216 = 216,
};

class J2DWindow : public J2DPane {
public:
    struct TMaterial {
        J2DMaterial* field_0x0;
        J2DMaterial* field_0x4;
        J2DMaterial* field_0x8;
        J2DMaterial* field_0xc;
        J2DMaterial* field_0x10;
    };

    struct TContentsColor {
        TContentsColor() {}
        JUtility::TColor field_0x0;
        JUtility::TColor field_0x4;
        JUtility::TColor field_0x8;
        JUtility::TColor field_0xc;
    };

    J2DWindow(J2DPane*, JSURandomInputStream*, J2DMaterial*);
    J2DWindow(J2DPane*, JSURandomInputStream*, JKRArchive*);
    J2DWindow();
    J2DWindow(u64, const JGeometry::TBox2<f32>&, const char*, J2DTextureBase, const ResTLUT*);
    void initiate(const ResTIMG*, const ResTIMG*, const ResTIMG*, const ResTIMG*, const ResTLUT*, J2DWindowMirror, const JGeometry::TBox2<f32>&);
    void private_readStream(J2DPane*, JSURandomInputStream*, JKRArchive*);
    void initinfo();
    void initinfo2();
    static J2DWindowMirror convertMirror(J2DTextureBase);
    void draw_private(JGeometry::TBox2<f32> const&, JGeometry::TBox2<f32> const&);
    void setContentsColor(JUtility::TColor, JUtility::TColor, JUtility::TColor,
                                         JUtility::TColor);
    void drawFrameTexture(JUTTexture*, f32, f32, f32, f32, u16, u16, u16, u16, bool);
    void drawFrameTexture(JUTTexture*, f32, f32, bool, bool, bool);
    void drawContentsTexture(f32, f32, f32, f32);
    void setTevMode(JUTTexture*, JUtility::TColor, JUtility::TColor);

    virtual ~J2DWindow();
    virtual u16 getTypeID() const { return 17; }
    virtual void resize(f32, f32);
    virtual void drawSelf(f32, f32);
    virtual void drawSelf(f32, f32, Mtx*);
    virtual void draw(JGeometry::TBox2<f32> const&);
    virtual void draw(JGeometry::TBox2<f32> const&, JGeometry::TBox2<f32> const&);
    virtual void draw(f32 left, f32 top, f32 width, f32 height) { draw(JGeometry::TBox2<f32>(left, top, left + width, top + height)); }
    virtual bool setBlack(JUtility::TColor);
    virtual bool setWhite(JUtility::TColor);
    virtual bool setBlackWhite(JUtility::TColor, JUtility::TColor);
    virtual JUtility::TColor getBlack() const;
    virtual JUtility::TColor getWhite() const;
    virtual JUTTexture* getFrameTexture(u8, u8) const;
    virtual JUTTexture* getContentsTexture(u8 param_1) const {
        if (param_1 != 0) {
            return NULL;
        }
        return field_0x110;
    }
    virtual void getMaterial(J2DWindow::TMaterial& mat) const {
        mat.field_0x0 = NULL;
        mat.field_0x4 = NULL;
        mat.field_0x8 = NULL;
        mat.field_0xc = NULL;
        mat.field_0x10 = NULL;
    }
    virtual J2DMaterial* getFrameMaterial(u8) const { return NULL; }
    virtual J2DMaterial* getContentsMaterial() const { return NULL; }
    virtual void drawContents(JGeometry::TBox2<f32> const&);
    virtual bool isUsed(const ResTIMG*);
    virtual bool isUsed(const ResFONT* font) { return J2DPane::isUsed(font); }
    virtual void rewriteAlpha() {}

    bool isField0x145Set(u8 flag) { return field_0x145 & flag; }

    void getContentsColor(TContentsColor& param_0) const {
        param_0.field_0x0 = field_0x128;
        param_0.field_0x4 = field_0x12C;
        param_0.field_0x8 = field_0x130;
        param_0.field_0xc = field_0x134;
    }
    void setContentsColor(JUtility::TColor param_0) {
        setContentsColor(param_0, param_0, param_0, param_0);
    }

protected:
    JUTTexture* field_0x100;
    JUTTexture* field_0x104;
    JUTTexture* field_0x108;
    JUTTexture* field_0x10c;
    JUTTexture* field_0x110;
    JGeometry::TBox2<f32> field_0x114;
    JUTPalette* mPalette;
    JUtility::TColor field_0x128;
    JUtility::TColor field_0x12C;
    JUtility::TColor field_0x130;
    JUtility::TColor field_0x134;
    JUtility::TColor mWhite;
    JUtility::TColor mBlack;
    s16 field_0x140;
    s16 field_0x142;
    u8 field_0x144;
    u8 field_0x145;
};

#endif
