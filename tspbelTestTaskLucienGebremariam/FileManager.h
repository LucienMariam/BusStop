#include "stdafx.h"
#include <fstream>
#include <windows.h>


class FileManager
{
private:
	fstream m_file;
	static FileManager *instance;

	FileManager() { }

	char* AdaptFilePath(const string filename);

public:
	~FileManager() { delete[] instance; }

	static FileManager* GetInstance();
	vector<string>* ReadFromFile(const string filename = m_defaultInDirectory);
	void WriteToFile(const vector<string> *data, const string filename = m_defaultOutDirectory);
};


FileManager* FileManager::instance = NULL;

FileManager* FileManager::GetInstance()
{
	if (!instance)
		instance = new FileManager();

	return instance;
}

char* FileManager::AdaptFilePath(const string filename)
{
	char *fileDirectory;
	fileDirectory = new char[filename.length() + 1];
	OemToChar(filename.c_str(), fileDirectory);
	filename.~basic_string();
	return fileDirectory;
}

vector<string>* FileManager::ReadFromFile(const string filename)
{
	string temp;
	vector<string> *array = new vector < string >;
	m_file.open(AdaptFilePath(filename), ios::in);

	while (!m_file.eof())
	{
		m_file >> temp;
		array->push_back(temp);
	}

	m_file.close();
	return array;
}

void FileManager::WriteToFile(const vector<string> *data, const string filename)
{
	m_file.open(AdaptFilePath(filename), ios::out);
	
	for (int i = 0; i < data->size(); i++)
	{
		m_file << (*data)[i];
		m_file << "\n";
	}

	m_file.close();
}