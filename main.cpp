#include "graph.h"
int main()
{
	Digraph a;
	KosarajuSCC x(&a);
	cout << x.get_count() << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < a.get_v(); j++)
		{
			if (x.get_id(j) == i)
				cout << j << ' ';
		}
		cout << endl;
	}
}