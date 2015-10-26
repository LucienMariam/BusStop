#include "stdafx.h"
#include "TimetableModificator.h"
#include "Entry.h"

TimetableModificator::TimetableModificator(const vector<Entry> *timetable)
{
	InitializeFields();
	*m_resultArray = *timetable;
	target = m_resultArray->begin();
}

void TimetableModificator::InitializeFields()
{
	m_tempArray = new vector < Entry >;
	m_resultArray = new vector < Entry >;
}

void TimetableModificator::FreeFields()
{
	delete m_tempArray;
	delete m_resultArray;
}

void TimetableModificator::CleanEqualEntries()
{
	for (int j = 0; j < m_resultArray->size() - 1; j++)
	{
		m_currentNode = *(target + j);
		
		for (int i = j + 1; i < m_resultArray->size(); i++)
			if ((target + i)->m_departureTime == m_currentNode.m_departureTime && 
				(target + i)->m_arrivalTime == m_currentNode.m_arrivalTime)
				if ((target + i)->m_brandname == m_busBrandName2)
					m_resultArray->erase(target + i);
		 
				else if (m_currentNode.m_brandname == m_busBrandName2)
					m_resultArray->erase(target + j);
	}
}

void TimetableModificator::FindEfficientEntry()
{
	m_currentNode = (*m_resultArray)[0];
	target = m_resultArray->begin();
	m_catchedId = 0;

	for (short i = 0; i < m_resultArray->size(); i++)
		if ((*m_resultArray)[i].m_arrivalTime < m_currentNode.m_arrivalTime)
		{
		    m_currentNode = (*m_resultArray)[i];
			m_catchedId = i;
		}

	for (short i = 0; i < m_resultArray->size(); i++)
		if ((*m_resultArray)[i].m_arrivalTime == m_currentNode.m_arrivalTime &&
			(*m_resultArray)[i].m_departureTime > m_currentNode.m_departureTime)
		{
		    m_currentNode = (*m_resultArray)[i];
			m_catchedId = i;
		}
}

void TimetableModificator::CleanUnefficientEntries()
{
	for (short i = 0; i < m_resultArray->size(); i++)
		if ((*m_resultArray)[i].m_departureTime < m_currentNode.m_departureTime &&
			(*m_resultArray)[i].m_arrivalTime >= m_currentNode.m_arrivalTime)
		{
		    m_resultArray->erase(target + i);

			if (i < m_catchedId)
				m_catchedId--;
		}

	target = m_resultArray->begin();
}

Entry TimetableModificator::CreateBlankLine()
{
	Entry blankLine;
	blankLine.m_arrivalTime = " ";
	blankLine.m_brandname = "";
	blankLine.m_departureTime = "";
	return blankLine;
}

void TimetableModificator::FormPoshResult()
{
	for (short i = 0; i < m_tempArray->size(); i++)
		if ((*m_tempArray)[i].m_brandname == m_busBrandName1)
			m_resultArray->push_back((*m_tempArray)[i]);

	m_resultArray->push_back(CreateBlankLine());
}

void TimetableModificator::FormGrottyResult()
{
	for (short i = 0; i < m_tempArray->size(); i++)
		if ((*m_tempArray)[i].m_brandname == m_busBrandName2)
			m_resultArray->push_back((*m_tempArray)[i]);
}

vector<Entry>* TimetableModificator::Modificate()
{
	CleanEqualEntries();

	while (!m_resultArray->empty())
	{
		FindEfficientEntry();
		CleanUnefficientEntries();
		m_tempArray->push_back(m_currentNode);
		m_resultArray->erase(target + m_catchedId);
	}

	target = m_tempArray->begin();
	FormPoshResult();
	FormGrottyResult();

	return m_resultArray;
}