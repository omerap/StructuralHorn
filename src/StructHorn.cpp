// StructHorn.cpp : Defines the entry point for the application.
//

#include "StructHorn.h"
#include "Hypergraph.h"

using namespace std;
using namespace structHorn;

void test_hypergraph() {
	hypergraph g;

	node_set sources0;
	sources0.insert(0);
	g.insert_hyperarc(0, sources0, 1, 1);

	node_set sources1;
	sources1.insert(1);
	g.insert_hyperarc(1, sources1, 2, 1);

	node_set sources2;
	sources2.insert(2);
	g.insert_hyperarc(2, sources2, 3, 1);

	node_set sources3;
	sources3.insert(2);
	g.insert_hyperarc(3, sources3, 3, 1);

	node_set sources4;
	sources4.insert(1);
	sources4.insert(3);
	g.insert_hyperarc(4, sources4, 2, 2);

	node_set sources5;
	sources5.insert(1);
	sources5.insert(3);
	g.insert_hyperarc(5, sources5, 1, 2);

	node_set sources6;
	sources6.insert(1);
	sources6.insert(3);
	g.insert_hyperarc(6, sources6, 1, 3);

	node_set sources7;
	sources7.insert(1);
	g.insert_hyperarc(7, sources7, 4, 1);

	cout << g;

	node_set source;
	source.insert(0);
	node_set target;
	target.insert(4);
	// g.shortest_nontrivial_hyperpath_gt0(source,target);
}

int main()
{
	test_hypergraph();
	return 0;
}
