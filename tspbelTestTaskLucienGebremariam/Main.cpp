#include "stdafx.h"
#include "ConsoleOutput.h"

int main()
{
	ConsoleOutput screenOutput;
	screenOutput.ShowExample();
	screenOutput.ShowExample(m_defaultInDirectory2, m_defaultOutDirectory2);
	return 0;
}
