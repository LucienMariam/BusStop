#pragma once
#include "Entry.h"
#include "IFieldsManager.h"

class TimetableModificator: private IFieldsManager
{
private:
	int m_catchedId;
	Entry m_currentNode;
	vector<Entry> *m_tempArray;
	vector<Entry> *m_resultArray;
	vector<Entry>::iterator target;

	void CleanEqualEntries();
	void FindEfficientEntry();
	void CleanUnefficientEntries();
	void FormPoshResult();
	void FormGrottyResult();
	Entry CreateBlankLine();

	virtual void InitializeFields();
	virtual void FreeFields();

public:
	TimetableModificator(const vector<Entry> *timetable);
	~TimetableModificator() { FreeFields(); }

	vector<Entry>* Modificate();
};