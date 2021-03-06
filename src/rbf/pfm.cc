#include "pfm.h"

#include <iostream>
#include <fstream>
#include <cstdio>

PagedFileManager* PagedFileManager::_pf_manager = 0;

PagedFileManager* PagedFileManager::instance()
{
    if(!_pf_manager)
        _pf_manager = new PagedFileManager();

    return _pf_manager;
}


PagedFileManager::PagedFileManager()
{
}


PagedFileManager::~PagedFileManager()
{
}


RC PagedFileManager::createFile(const string &fileName)
{
	// Check if file already exists. Fail if it does.
	std::ifstream existingFile(fileName);
	if (existingFile.good()) {
		existingFile.close();
		return -1;
	}

	// Create a new file.
	std::ofstream newFile;
	newFile.open(fileName, ios::out);
	newFile.close();
    return 0;
}


RC PagedFileManager::destroyFile(const string &fileName)
{
	// Check if file already exists before deleting it.
	std::ifstream existingFile(fileName);
	if (existingFile.good()) {
		existingFile.close();

		// Delete file now that we're sure it exists.
		std::remove(fileName.c_str());
		return 0;
	}

	return -1;
}


RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle)
{
	// Check if file already exists before opening it.
	std::ifstream existingFile(fileName);
	if (!existingFile.good()) {
		return -1;
	}
	existingFile.close();

	// Check if the file handle already handles another file.
	if (fileHandle.stream.is_open()) {
		return -1;
	}

	// Initialize new file handle
	fileHandle.stream.open(fileName,
			std::fstream::in | std::fstream::out | std::fstream::app);
	return 0;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle)
{
	// Check if the fileHandle's stream is open before closing it.
	if (fileHandle.stream.is_open()) {
		fileHandle.stream.close();
		return 0;
	}
    return -1;
}


FileHandle::FileHandle()
{
    readPageCounter = 0;
    writePageCounter = 0;
    appendPageCounter = 0;
}


FileHandle::~FileHandle()
{
}


RC FileHandle::readPage(PageNum pageNum, void *data)
{
    return -1;
}


RC FileHandle::writePage(PageNum pageNum, const void *data)
{
    return -1;
}


RC FileHandle::appendPage(const void *data)
{
    return -1;
}


unsigned FileHandle::getNumberOfPages()
{
    return 0;
}


RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount)
{
    return -1;
}
