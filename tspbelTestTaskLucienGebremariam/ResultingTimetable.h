#include "BusTimetable.h"
#include "TimetableModificator.h"

class ResultingTimetable: public BusTimetable
{
private:
	TimetableModificator *m_modificator;

public:
	ResultingTimetable() { }
	~ResultingTimetable() { delete m_modificator; }

	TimetableModificator* CreateModificator(const vector<Entry> *timetable) {
		return new TimetableModificator(timetable); }

	void Modificate(const vector<Entry> *timetable)
	{
		m_modificator = CreateModificator(timetable);
		m_timetable = m_modificator->Modificate();
	}
	
};