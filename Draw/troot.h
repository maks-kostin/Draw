#pragma once
#include <stdlib.h>
#include <stdio.h>
#include< iostream>
#include <stack>
#include <cstdlib>
#include "windows.h"
#include "../Draw/MyForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class TChart;
class TPoint;
struct TLine {
	TChart* pChart;
	TPoint* pFp, * pLp;
};

class TRoot
{
protected:
	bool Visible, Active;
public:
	TRoot(bool _visible = false, bool _active = false) : Visible(_visible), Active(_active) {}

	bool IsVisible() { return Visible; }
	bool IsActive() { return Active; }

	virtual void Show(Graphics^ gr) = 0;
	virtual void Hide(Graphics^ gr) = 0;
};

class TPoint : public TRoot
{
protected:
	int x, y;
public:
	TPoint(int _x, int _y) : x(_x), y(_y) {}
	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; }
	void Show(Graphics^ gr) override
	{
		gr->DrawEllipse(Pens::Black, x - 2, y - 2, 4, 4);
		Visible = true;
	}
};

class TChart : public TRoot
{
protected:
	TRoot* pFirst, * pLast;
	std::stack <TLine> st;
public:
	TChart() : pFirst(NULL), pLast(NULL) {}
	int GetSize()
	{
		int size = 0;
		if (pFirst)
			size++;
		if (pLast)
			size++;
		return size;
	}
	TRoot* GetFirst() { return pFirst; }
	TRoot* GetLast() { return pLast; }
	void SetFirst(TRoot* p);
	void SetLast(TRoot* p);
	void Show(Graphics^ gr) override;
	TRoot* ShowRec(Graphics^ gr, TRoot* p);
};
