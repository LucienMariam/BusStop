#include "stdafx.h"
#include "OriginalTimetable.h"
#include "ResultingTimetable.h"
#include "FileManager.h"
#include "IFieldsManager.h"


class ConsoleOutput: private IFieldsManager
{
private:
	OriginalTimetable *m_originalTimetable;
	ResultingTimetable *m_resultingTimetable;
	vector<string> *storage;
	vector<Entry> *timetable;
	Entry package;

	void ReadDataFromFile(const string filename);
	void WriteDataToFile(const string filename);
	void ShowOriginalTimetable();
	void ShowResultingTimetable();

	virtual void InitializeFields();
	virtual void FreeFields();

public:
	ConsoleOutput() { InitializeFields(); }
	~ConsoleOutput() { FreeFields(); }

	void ShowExample(const string inFile = m_defaultInDirectory, const string outFile = m_defaultOutDirectory);
};


void ConsoleOutput::InitializeFields()
{
	m_originalTimetable = new OriginalTimetable();
	m_resultingTimetable = new ResultingTimetable();
}

void ConsoleOutput::FreeFields()
{
	delete[] m_originalTimetable;
	delete[] m_resultingTimetable;
}

void ConsoleOutput::ReadDataFromFile(const string filename)
{
	storage = FileManager::GetInstance()->ReadFromFile(filename);

	for (int i = 0; i < storage->size();)
	{
		package.m_brandname = (*storage)[i++];
		package.m_departureTime = (*storage)[i++];
		package.m_arrivalTime = (*storage)[i++];
		m_originalTimetable->Add(package);
	}
}

void ConsoleOutput::WriteDataToFile(const string filename)
{
	timetable = m_resultingTimetable->GetTimetable();
	storage->clear();

	for (int i = 0; i < timetable->size(); i++ )
		storage->push_back((*timetable)[i].m_brandname + " " + (*timetable)[i].m_departureTime 
		                     + " " + (*timetable)[i].m_arrivalTime);

	FileManager::GetInstance()->WriteToFile(storage, filename);
}

void ConsoleOutput::ShowOriginalTimetable()
{
	system("CLS");
	timetable = m_originalTimetable->GetTimetable();
	cout << "Given the following data:\n\n";

	for (int i = 0; i < timetable->size(); i++)
		cout << (*timetable)[i].m_brandname << " " << (*timetable)[i].m_departureTime << " "
		     << (*timetable)[i].m_arrivalTime << endl;
}

void ConsoleOutput::ShowResultingTimetable()
{
	timetable = m_resultingTimetable->GetTimetable();
	cout << "\n\nProgram output:\n\n";

	for (int i = 0; i < timetable->size(); i++)
		cout << (*timetable)[i].m_brandname << " " << (*timetable)[i].m_departureTime << " " 
		     << (*timetable)[i].m_arrivalTime << endl;

	system("PAUSE");
}

void ConsoleOutput::ShowExample(const string inFile, const string outFile)
{
	ReadDataFromFile(inFile);
	ShowOriginalTimetable();
	m_resultingTimetable->Modificate(m_originalTimetable->GetTimetable());
	ShowResultingTimetable();
	WriteDataToFile(outFile);
}