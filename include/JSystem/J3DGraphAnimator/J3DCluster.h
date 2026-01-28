#ifndef J3DCLUSTER_H
#define J3DCLUSTER_H

class J3DDeformer;
class J3DClusterKey;
class J3DClusterVertex;
class J3DVertexBuffer;
class J3DModel;
class J3DAnmCluster;
class JUTNameTab;

class J3DCluster {
public:
    void operator=(const J3DCluster& other) {
        mMaxAngle = other.mMaxAngle;
        mMinAngle = other.mMinAngle;
        mClusterKey = other.mClusterKey;
        mFlags = other.mFlags;
        mKeyNum = other.mKeyNum;
        mPosNum = other.mPosNum;
        field_0x14 = other.field_0x14;
        field_0x16 = other.field_0x16;
        field_0x18 = other.field_0x18;
        mClusterVertex = other.mClusterVertex;
        mDeformer = other.mDeformer;
    }

    J3DDeformer* getDeformer() { return mDeformer; }
    void setDeformer(J3DDeformer* deformer) {
        mDeformer = deformer;
    }

    f32 mMaxAngle;
    f32 mMinAngle;
    J3DClusterKey* mClusterKey;
    u8 mFlags;
    u8 field_0xe[0x10 - 0xD];
    u16 mKeyNum;
    u16 mPosNum;
    u16 field_0x14;
    u16 field_0x16;
    u16* field_0x18;
    J3DClusterVertex* mClusterVertex;
    J3DDeformer* mDeformer;
};

class J3DClusterKey {
public:
    void operator=(const J3DClusterKey& other) {
        mPosNum = other.mPosNum;
        mNrmNum = other.mNrmNum;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

    u16 mPosNum;
    u16 mNrmNum;
    void* field_0x4;
    void* field_0x8;
};

class J3DDeformData {
public:
    J3DDeformData();
    void offAllFlag(u32);
    void deform(J3DVertexBuffer*);
    void deform(J3DModel*);
    void setAnm(J3DAnmCluster*);

    J3DCluster* getClusterPointer(u16 index) {
        return &mClusterPointer[index];
    }
    u16 getClusterNum() const { return mClusterNum; }
    u16 getClusterKeyNum() const { return mClusterKeyNum; }
    J3DClusterKey* getClusterKeyPointer(u16 i) {
        return &mClusterKeyPointer[i];
    }
    f32* getVtxPos() { return mVtxPos; }
    f32* getVtxNrm() { return mVtxNrm; }

    u16 mClusterNum;
    u16 mClusterKeyNum;
    u16 mClusterVertexNum;
    J3DCluster* mClusterPointer;
    J3DClusterKey* mClusterKeyPointer;
    J3DClusterVertex* mClusterVertex;
    u16 mVtxPosNum;
    u16 mVtxNrmNum;
    f32* mVtxPos;
    f32* mVtxNrm;
    JUTNameTab* mClusterName;
    JUTNameTab* mClusterKeyName;
};

class J3DClusterVertex {
public:
    void operator=(const J3DClusterVertex& other) {
        mNum = other.mNum;
        field_0x4 = other.field_0x4;
        field_0x8 = other.field_0x8;
    }

    u16 mNum;
    u16* field_0x4;
    u16* field_0x8;
};

#endif
