//----------------------------------------------------------------------------------------------------------------------
// DmcLib
// Created by Carmelo J. Fdez-Ag�era Tortosa (a.k.a. Technik)
// 2014/Dec/27
//----------------------------------------------------------------------------------------------------------------------
// File implementation for platforms conforming to C++ standard
#ifndef _DMCLIB_CORE_PLATFORM_FILE_FILE_H_
#define _DMCLIB_CORE_PLATFORM_FILE_FILE_H_

#include <string>

/** \brief class used to open system files. 666 Need to be updated
*/
class File {
public:
	File(const std::string& _path); // File must exist
	~File();

	static File* openExisting(const std::string& _path); // Returns nullptr if the file doesn't exist already

	void			readAll		();
	void			setContent	(const void* _buffer, size_t, bool _hardCopy = true);

	const void *	buffer		() const;
	const char *	bufferAsText() const;
	size_t			sizeInBytes	() const;

private:
	size_t		mSize = 0;
	const void*	mBuffer = nullptr;
	bool		mMustWrite = false;
	std::string	mPath;
};

typedef File FileBase;

//------------------------------------------------------------------------------------------------------------------
// Inline implementation
//------------------------------------------------------------------------------------------------------------------
inline const void * File::buffer		() const { return mBuffer; }
inline const char * File::bufferAsText	() const { return reinterpret_cast<const char*>(mBuffer); }
inline size_t		File::sizeInBytes	() const { return mSize; }

#endif // _DMCLIB_CORE_PLATFORM_FILE_FILE_H_