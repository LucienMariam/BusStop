#include "stdafx.h"
#include "OriginalTimetable.h"
#include "Entry.h"

void OriginalTimetable::Add(const Entry entry)
{
	static short counter = 0;

	if (counter >= m_maxEntries)
		return;

	m_timetable->push_back(entry);
	counter++;
}