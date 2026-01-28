#ifndef JKRARCHIVE_H
#define JKRARCHIVE_H

#include "JSystem/JKernel/JKRCompression.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "global.h"

class JKRHeap;

struct SArcHeader {
    u32 signature;
    u32 file_length;
    u32 header_length;
    u32 file_data_offset;
    u32 file_data_length;
    u32 field_0x14;
    u32 field_0x18;
    u32 field_0x1c;
};

struct SArcDataInfo {
    u32 num_nodes;
    u32 node_offset;
    u32 num_file_entries;
    u32 file_entry_offset;
    u32 string_table_length;
    u32 string_table_offset;
    u16 next_free_file_id;
    bool sync_file_ids_and_indices;
    u8 field_1b[5];
};

inline u32 read_big_endian_u32(void* ptr) {
    u8* uptr = (u8*)ptr;
    return ((u32)uptr[0] << 0x18) | ((u32)uptr[1] << 0x10) | ((u32)uptr[2] << 8) | (u32)uptr[3];
}

inline u16 read_big_endian_u16(void* ptr) {
    u8* uptr = (u8*)ptr;
    return ((u16)uptr[0] << 8) | ((u16)uptr[1]);
}

extern u32 sCurrentDirID__10JKRArchive;

class JKRArchive : public JKRFileLoader {
public:
    struct SDirEntry {
        u8 flags;
        u8 padding;
        u16 id;
        const char* name;
    };

    struct SDIDirEntry {
        u32 type;
        u32 name_offset;
        u16 field_0x8;
        u16 num_entries;
        u32 first_file_index;
    };

    struct SDIFileEntry {
        u16 file_id;
        u16 name_hash;
        u32 type_flags_and_name_offset;
        u32 data_offset;
        u32 data_size;
        void* data;

        u32 getNameOffset() const { return type_flags_and_name_offset & 0xFFFFFF; }
        u16 getNameHash() const { return name_hash; }
        u32 getFlags() const { return type_flags_and_name_offset >> 24; }
        u32 getAttr() const { return getFlags(); }
        u16 getFileID() const { return file_id; }
        bool isDirectory() const { return (getFlags() & 0x02) != 0; }
        bool isUnknownFlag1() const { return (getFlags() & 0x01) != 0; }
        bool isCompressed() const { return (getFlags() & 0x04) != 0; }
        // was needed for open__14JKRAramArchiveFl
        u8 getCompressFlag() const { return (getFlags() & 0x04); }
        bool isYAZ0Compressed() const { return (getFlags() & 0x80) != 0; }
        u32 getSize() const { return data_size; }
    };

    enum EMountMode {
        UNKNOWN_MOUNT_MODE = 0,
        MOUNT_MEM = 1,
        MOUNT_ARAM = 2,
        MOUNT_DVD = 3,
        MOUNT_COMP = 4,
    };

    enum EMountDirection {
        UNKNOWN_MOUNT_DIRECTION = 0,
        MOUNT_DIRECTION_HEAD = 1,
        MOUNT_DIRECTION_TAIL = 2,
    };

    class CArcName {
    public:
        CArcName() {}
        CArcName(char const* data) { this->store(data); }
        CArcName(char const** data, char endChar) { *data = this->store(*data, endChar); }

        void store(char const* data);
        const char* store(char const* data, char endChar);

        u16 getHash() const { return mHash; }

        const char* getString() const { return mData; }

    private:
        u16 mHash;
        u16 mLength;
        char mData[256];
    };

protected:
    JKRArchive();
    JKRArchive(s32, EMountMode);

public:
    bool getDirEntry(SDirEntry*, u32) const;
    void* getIdxResource(u32);
    void* getResource(u16);
    u32 readIdxResource(void*, u32, u32);
    u32 readResource(void*, u32, u16);
    u32 countResource(void) const;
    u32 getFileAttribute(u32) const;

    SDIFileEntry* findNameResource(const char*) const;
    bool isSameName(CArcName&, u32, u16) const;
    SDIDirEntry* findResType(u32) const;
    SDIDirEntry* findDirectory(const char*, u32) const;
    SDIFileEntry* findTypeResource(u32, const char*) const;
    SDIFileEntry* findFsResource(const char*, u32) const;
    SDIFileEntry* findIdxResource(u32) const;
    SDIFileEntry* findPtrResource(const void*) const;
    SDIFileEntry* findIdResource(u16) const;

public:
    virtual bool becomeCurrent(const char*);
    virtual void* getResource(const char*);
    virtual void* getResource(u32, const char*);
    virtual u32 readResource(void*, u32, const char*);
    virtual u32 readResource(void*, u32, u32, const char*);
    virtual void removeResourceAll(void);
    virtual bool removeResource(void*);
    virtual bool detachResource(void*);
    virtual u32 getResSize(const void*) const;
    virtual u32 countFile(const char*) const;
    virtual JKRFileFinder* getFirstFile(const char*) const;
    virtual u32 getExpandedResSize(const void* res) const { return getResSize(res); }
    virtual void* fetchResource(SDIFileEntry*, u32*) = 0;
    virtual void* fetchResource(void*, u32, SDIFileEntry*, u32*) = 0;
    virtual void setExpandSize(SDIFileEntry*, u32);
    virtual u32 getExpandSize(SDIFileEntry*) const;
    virtual ~JKRArchive();

    u32 countFile() const { return mArcInfoBlock->num_file_entries; }
    s32 countDirectory() const { return mArcInfoBlock->num_nodes; }
    u8 getMountMode() const { return mMountMode; }
    bool isFileEntry(u32 param_0) {
        return getFileAttribute(param_0) & 1;
    }

public:
    JKRHeap* mHeap;
    u8 mMountMode;
    u8 field_0x3d[3];
    s32 mEntryNum;
    SArcDataInfo* mArcInfoBlock;
    SDIDirEntry* mNodes;
    SDIFileEntry* mFiles;
    s32* mExpandedSize;
    const char* mStringTable;

protected:
    u32 field_0x58;
    JKRCompression mCompression;
    EMountDirection mMountDirection;

public:
    static JKRArchive* check_mount_already(s32, JKRHeap*);
    static JKRArchive* mount(const char*, EMountMode, JKRHeap*, EMountDirection);
    static JKRArchive* mount(void*, JKRHeap*, EMountDirection);
    static JKRArchive* mount(s32, EMountMode, JKRHeap*, EMountDirection);
    static void* getGlbResource(u32, const char*, JKRArchive*);

    static JKRCompression convertAttrToCompressionType(int attr) {
#define JKRARCHIVE_ATTR_COMPRESSION 0x04
#define JKRARCHIVE_ATTR_YAZ0 0x80

        if (!(attr & JKRARCHIVE_ATTR_COMPRESSION)) {
            return COMPRESSION_NONE;
        } else if (attr & JKRARCHIVE_ATTR_YAZ0) {
            return COMPRESSION_YAZ0;
        } else {
           return COMPRESSION_YAY0;
        }
    }

    static u32 getCurrentDirID() { return sCurrentDirID; }
    static void setCurrentDirID(u32 dirID) { sCurrentDirID = dirID; }

protected:
    static u32 sCurrentDirID;
};

inline JKRCompression JKRConvertAttrToCompressionType(int attr) {
    return JKRArchive::convertAttrToCompressionType(attr);
}

inline void* JKRGetResource(u32 node, const char* path, JKRArchive* archive) {
    return JKRArchive::getGlbResource(node, path, archive);
}

inline void* JKRGetTypeResource(u32 tag, const char* name, JKRArchive* arc) {
    return JKRArchive::getGlbResource(tag, name, arc);
}

inline bool JKRRemoveResource(void* resource, JKRFileLoader* fileLoader) {
    return JKRFileLoader::removeResource(resource, fileLoader);
}

inline JKRArchive* JKRMountArchive(void* ptr, JKRHeap* heap, JKRArchive::EMountDirection mountDirection) {
    return JKRArchive::mount(ptr, heap, mountDirection);
}

inline void JKRUnmountArchive(JKRArchive* arc) {
    arc->unmount();
}

inline u32 JKRReadIdxResource(void* buffer, u32 bufsize, u32 resIdx, JKRArchive* archive) {
    return archive->readIdxResource(buffer, bufsize, resIdx);
}

#endif
