#ifndef JUTDIRECTFILE_H
#define JUTDIRECTFILE_H

// #include <dolphin/dvd.h>

#define JUTDF_BUFSIZE (0x800)

struct JUTDirectFile {
    int fetch32byte();
    JUTDirectFile();
    ~JUTDirectFile();
    bool fopen(char const*);
    void fclose();
    int fgets(void*, int);

    bool isOpened() const { return mIsOpen; }

    u8 mBuffer[0x820];
	u8* mSectorStart;
	u32 mToRead;
	u32 mLength;
	u32 mPos;
	bool mIsOpen;
	DVDFileInfo mFileInfo;
};

#endif
