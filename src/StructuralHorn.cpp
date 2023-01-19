// StructHorn.cpp : Defines the entry point for the application.
//

#include "StructuralHorn.h"
#include "Hypergraph.h"

using namespace std;
using namespace structuralHorn;

void test_hypergraph() {
	hypergraph g(0,4);

	node_multiset sources0;
	sources0.insert(0);
	g.insert_hyperarc(0, sources0, 1);

	node_multiset sources1;
	sources1.insert(1);
	g.insert_hyperarc(1, sources1, 2);

	node_multiset sources2;
	sources2.insert(2);
	g.insert_hyperarc(2, sources2, 3);

	node_multiset sources3;
	sources3.insert(2);
	g.insert_hyperarc(3, sources3, 3);

	node_multiset sources4;
	sources4.insert(1);
	sources4.insert(3);
	g.insert_hyperarc(4, sources4, 2, 2);

	node_multiset sources5;
	sources5.insert(1);
	sources5.insert(3);
	g.insert_hyperarc(5, sources5, 1, 2);

	node_multiset sources6;
	sources6.insert(1);
	sources6.insert(3);
	sources6.insert(3);
	g.insert_hyperarc(6, sources6, 1, 3);

	node_multiset sources7;
	sources7.insert(1);
	g.insert_hyperarc(7, sources7, 4);

	cout << g;

	hyperarc_set optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	while (!optimal_hyperpath.empty()) {
		cout << "\nOptimal hyperpath: {";
		bool first_hyperarc = true;
		for (int hyperarc : optimal_hyperpath) {
			if (first_hyperarc) {
				first_hyperarc = false;
				cout << hyperarc;
			}
			else {
				cout << ", " << hyperarc;
			}
		}
		cout << "}\n";
		optimal_hyperpath = g.shortest_nontrivial_hyperpath_gt0();
	}
}

int main()
{
	test_hypergraph();
	return 0;
}
