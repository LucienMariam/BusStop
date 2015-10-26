#include "BusTimetable.h"

class OriginalTimetable: public BusTimetable
{
private:
	const short m_maxEntries = 50;

public:
	OriginalTimetable() { }
	~OriginalTimetable() { }

	void Add(const Entry entry);
};