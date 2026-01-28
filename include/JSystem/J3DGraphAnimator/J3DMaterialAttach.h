#ifndef J3DMATERIALATTACH_H
#define J3DMATERIALATTACH_H

#include <dolphin/types.h>

class J3DMaterial;
class J3DTexture;
class J3DAnmColor;
class J3DAnmTexPattern;
class J3DAnmTextureSRTKey;
class J3DAnmTevRegKey;
class JUTNameTab;

class J3DMaterialTable {
public:
    void clear();
    J3DMaterialTable();
    int removeMatColorAnimator(J3DAnmColor*);
    int removeTexNoAnimator(J3DAnmTexPattern*);
    int removeTexMtxAnimator(J3DAnmTextureSRTKey*);
    int removeTevRegAnimator(J3DAnmTevRegKey*);
    int createTexMtxForAnimator(J3DAnmTextureSRTKey*);
    int entryMatColorAnimator(J3DAnmColor*);
    int entryTexNoAnimator(J3DAnmTexPattern*);
    int entryTexMtxAnimator(J3DAnmTextureSRTKey*);
    int entryTevRegAnimator(J3DAnmTevRegKey*);

    virtual ~J3DMaterialTable();

    J3DMaterial* getMaterialNodePointer(u16 idx) const {
        return mMaterialNodePointer[idx];
    }

    J3DTexture* getTexture() const { return mTexture; }
    JUTNameTab* getTextureName() const { return mTextureName; }

    JUTNameTab* getMaterialName() const { return mMaterialName; }

    u16 getMaterialNum() const { return mMaterialNum; }
    bool isLocked() const { return field_0x1c == 1; }

private:
    friend class J3DModelLoader;
    friend class J3DModelLoader_v26;
    friend class J3DModelLoader_v21;

    u16 mMaterialNum;
    u16 mUniqueMatNum;
    J3DMaterial** mMaterialNodePointer;
    JUTNameTab* mMaterialName;
    J3DMaterial* field_0x10;
    J3DTexture* mTexture;
    JUTNameTab* mTextureName;
    u16 field_0x1c;
};
#endif
