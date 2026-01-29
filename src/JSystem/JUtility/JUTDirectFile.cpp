#include "JSystem/JSystem.h"
#include "JSystem/JUtility/JUTDirectFile.h"
/* #include "dolphin/os.h"
#include "global.h"
#include <stdint.h> */

int JUTDirectFile::fetch32byte() {
	std::cout << "JUTDirectFile::fetch32byte() is stubbed" << std::endl;
	return -1;
}

JUTDirectFile::JUTDirectFile() {
	std::cout << "JUTDirectFile::JUTDirectFile() is stubbed" << std::endl;
	mLength      = 0;
	mPos         = 0;
	mToRead      = 0;
	mSectorStart = 0;
	mIsOpen      = false;
}

JUTDirectFile::~JUTDirectFile() {
	std::cout << "JUTDirectFile::~JUTDirectFile() is stubbed" << std::endl;
	mIsOpen = false;
}

bool JUTDirectFile::fopen(const char* filename) {
	std::cout << "JUTDirectFile::fopen() is stubbed" << std::endl;
	return false;
}

void JUTDirectFile::fclose() {
	std::cout << "JUTDirectFile::fclose() is stubbed" << std::endl;
}

int JUTDirectFile::fgets(void* buf, int len) {
	std::cout << "JUTDirectFile::fgets() is stubbed" << std::endl;
	return -1;
}
