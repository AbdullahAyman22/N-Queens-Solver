#include<iostream>
#include<stdio.h>

#define size 10
using namespace std;
class cnode
{
public:
	char info[size][size];
	int cr;
	cnode* pnext;
};
class clist
{
public:
	cnode* phead;
	cnode* ptail;
	clist()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clist()
	{
		cnode* ptmp;
		cnode* ptrav = phead;
		while (ptrav != NULL)
		{
			ptmp = ptrav->pnext;
			delete ptrav;
			ptrav = ptmp;
		}
	}
	void attach(cnode* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}
};
class cstack
{
public:
	cnode* phead;
	cstack()
	{
		phead = NULL;
	}
	~cstack()
	{
		cnode* ptmp;
		cnode* ptrav = phead;
		while (ptrav != NULL)
		{
			ptmp = ptrav->pnext;
			delete ptrav;
			ptrav = ptmp;
		}
	}
	void push(cnode* pnn)
	{
		pnn->pnext = phead;
		phead = pnn;
	}
	cnode* pop()
	{
		if (phead == NULL)
		{
			return NULL;
		}
		cnode* ptrv = phead;
		phead = phead->pnext;
		ptrv->pnext = NULL;
		return ptrv;
	}
};
cnode* creatinitialstate()
{
	cnode* pnn = new cnode;
	for (int r = 0; r < size; r++)
	{
		for (int k = 0; k < size; k++)
		{
			pnn->info[r][k] = 254;
		}
	}
	pnn->cr = 0;
	pnn->pnext = NULL;
	return pnn;
}
void disp(cnode* pnn)
{
	for (int r = 0; r < size; r++)
	{
		for (int k = 0; k < size; k++)
		{
			cout << pnn->info[r][k] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void expandonelevelofchildred(cnode* pcurr, cstack& s, int& ct)
{

	cnode* pnn;
	int flag, r, c;
	int o = pcurr->cr;
	for (int i = 0; i < size; i++)
	{
		pnn = new cnode;
		for (int r = 0; r < size; r++)
		{
			for (int k = 0; k < size; k++)
			{
				pnn->info[r][k] = pcurr->info[r][k];
			}
		}
		pnn->cr = pcurr->cr + 1;
		pnn->info[o][i] = 'Q';
		pnn->pnext = NULL;
		flag = 1;
		r = o - 1;
		c = i - 1;
		while (r >= 0 && c >= 0)
		{
			if (pnn->info[r][c] == 'Q')
			{
				flag = 0;
				break;
			}
			c--;
			r--;
		}
		r = o - 1;
		c = i;
		while (r >= 0)
		{
			if (pnn->info[r][c] == 'Q')
			{
				flag = 0;
				break;
			}
			r--;
		}
		r = o - 1;
		c = i + 1;
		while (r >= 0 && c < size)
		{
			if (pnn->info[r][c] == 'Q')
			{
				flag = 0;
				break;
			}
			r--;
			c++;
		}
		if (flag == 1)
		{

			if (pnn->cr < size)
			{
				s.push(pnn);
			}
			else
			{
				ct++;
				cout << ct << endl;
				disp(pnn);
			}
		}
	}
}
void bk()
{
	int ct = 0;
	cnode* pnn = creatinitialstate();
	cstack s;
	s.push(pnn);
	while (s.phead != NULL)
	{
		cnode* pcurr = s.pop();
		expandonelevelofchildred(pcurr, s, ct);
	}
}


void main()
{
	bk();
}




