#pragma once
#include "Entry.h"

class BusTimetable
{
protected:
	vector<Entry> *m_timetable;

public:
	BusTimetable() { m_timetable = CreateTimetable(); }
	virtual ~BusTimetable() { }

	vector<Entry>* CreateTimetable() { return new vector<Entry>; }
	vector<Entry>* GetTimetable() { return m_timetable; }
};