#include "troot.h"


void TChart::SetFirst(TRoot* p)
{
	TPoint* pPoint = dynamic_cast<TPoint*>(p);
	TChart* pChart = dynamic_cast<TChart*>(p);
	if (pPoint || pChart)
		pFirst = p;
}

void TChart::SetLast(TRoot* p)
{
	TPoint* pPoint = dynamic_cast<TPoint*>(p);
	TChart* pChart = dynamic_cast<TChart*>(p);
	if (pPoint || pChart)
		pLast = p;
}

void TChart::Show(Graphics^ gr)
{
	TLine CurrLine;
	TRoot* pr;
	TPoint* pp;
	CurrLine.pChart = this;
	CurrLine.pFp = CurrLine.pLp = NULL;
	while (!st.empty())
		st.pop();
	st.push(CurrLine);
	while (!st.empty())
	{
		CurrLine = st.top();
		st.pop();
		while (!CurrLine.pFp)
		{
			pr = CurrLine.pChart->GetFirst();
			pp = dynamic_cast<TPoint*> (pr);
			if (pp)
			{
				CurrLine.pFp = pp;
				pp->Show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
			}
		}
		if (!CurrLine.pLp)
		{
			pr = CurrLine.pChart->GetLast();
			pp = dynamic_cast<TPoint*>(pr);
			if (pp)
			{
				CurrLine.pLp = pp;
				pp->Show(gr);
			}
			else
			{
				st.push(CurrLine);
				CurrLine.pChart = dynamic_cast<TChart*>(pr);
				CurrLine.pFp = NULL;
				st.push(CurrLine);
			}
		}
		if (CurrLine.pFp && CurrLine.pLp)
		{
			gr->DrawLine(Pens::Black, CurrLine.pFp->GetX(), CurrLine.pFp->GetY(), CurrLine.pLp->GetY(), CurrLine.pLp->GetY());
			pp = CurrLine.pLp;
			if (!st.empty())
			{
				CurrLine = st.top();
				st.pop();
				if (!CurrLine.pFp)
					CurrLine.pFp = pp;
				else
					CurrLine.pLp = pp;
			}
			st.push(CurrLine);
		}
	}
}

TRoot* TChart::ShowRec(Graphics^ gr, TRoot* p)
{
	TPoint* pF, * pL;
	TChart* pCh;
	TRoot* pR;
	pF = dynamic_cast<TPoint*>(p);
	if (pF)
	{
		pF->Show(gr);
		return pF;
	}
	else
	{
		pCh = dynamic_cast<TChart*> (p);
		pR = ShowRec(gr, pCh->GetFirst());
		pL = dynamic_cast<TPoint*>(pR);
		if (pF && pL)
		{
			gr->DrawLine(Pens::Black, pF->GetX(), pF->GetY(), pL->GetY(), pL->GetY());
			return pL;
		}
	}
}