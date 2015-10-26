#pragma once
#include "stdafx.h"

class IFieldsManager
{
public:
	virtual void InitializeFields() = 0;
	virtual void FreeFields() = 0;
};