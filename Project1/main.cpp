#include<iostream>
#include "map.h"
#include "fuite.h"
#include "map2.h"
#include  <list>

using namespace std;


int main() {
	cout << "\n\n map vide;" << endl;
	map<int, char> u = map<int, char>();
	u.afficher();

	u.insert(78);
	u.insert(71);
	cout << "\n\n map 1 ELEMENT;" << endl;
	u.afficher();

	//===============================================================================>AUTO INSERT
	u.clear();
	int accu1 = 0;
	u.insert(78);
	u.insert(13);
	u.insert(4);
	u.insert(9);
	u.insert(45);
	u.insert(2);
	u.insert(53);
	u.insert(42);
	u.insert(19);
	u.insert(423);
	u.insert(18);

	cout << "\n\nu apres insertion DE: " << accu1 << " element en boucle;" << endl;
	u.afficher();
	//===============================================================================>AUTO INSERT



	//===============================================================================>AUTO INSERT
	u.clear();
	int accu = 0;
	for (size_t i = 0; i < 29; i++)
	{
		u.insert(accu);
		accu += 5;
	}
	cout << "\n\nu apres insertion DE: " << accu << " element en boucle;" << endl;
	u.afficher();
	//===============================================================================>AUTO INSERT








	//===========================================================================>low

	auto it = u.lower_bound(40);
	cout << "\n lowerbound 40(present repNormal = 40) est: " << it->first << "\n\n\n";

	it = u.lower_bound(43);
	cout << "\n lowerbound 43(absent (repNrmal = 45) ) est: " << it->first << "\n\n\n";


	it = u.lower_bound(29);

	cout << "\n lowerbound 29(absent (repNrmal = 30) ) est: " << it->first << "\n\n\n";


	it = u.lower_bound(29);

	cout << "\n lowerbound 29(absent (repNrmal = 30) ) est: " << it->first << "\n\n\n";

	it = u.lower_bound(71);
	cout << "\n lower_bound 71(absent (repNrmal = 75) ) est: " << it->first << "\n\n\n";


	it = u.lower_bound(43);

	cout << "\n lowerbound 43(absent (repNrmal = 45) ) est: " << it->first << "\n\n\n";

	//===========================================================================>low






	//===========================================================================>uper

	it = u.upper_bound(43);
	cout << "\n upper_bound 43(absent (repNrmal = 45) ) est: " << it->first << "\n\n\n";

	it = u.upper_bound(20);
	int i = it->first;
	cout << "\n upper_bound 20(present (repNormal 30) ) est: " << i;

	it = u.lower_bound(90);
	i = it->first;
	cout << "\n upper_bound 90(absent) est: " << i;



	//===========================================================================>uper







	//===========================================================================>find

	it = u.find(43);
	cout << "\n find 43(absent (repNrmal = debut) ) est: " << it->first << "\n\n\n";

	it = u.find(20);
	i = it->first;
	cout << "\n find 20(present (repNormal 20) ) est: " << i;

	it = u.find(90);
	i = it->first;
	cout << "\n find present(absent) est: " << i;
	//===========================================================================>find







	//===========================================================================>insert
	cout << "\n insertion de 43 avec ( u.insert(it,43) ) \n\n\n";
	u.insert(it, 43);
	u.afficher();

	it = u.lower_bound(43);
	cout << "\n lower_bound 43(absent (repNrmal = 45) ) est: " << it->first << "\n\n\n";
	it = u.lower_bound(71);
	cout << "\n lower_bound 71(absent (repNrmal = 75) ) est: " << it->first << "\n\n\n";

	it = u.lower_bound(29);
	cout << "\n lower_bound(29) absent (repNrmal = 30 ) ) est: " << it->first << "\n\n\n";

	//===========================================================================>insert



		//===========================================================================>insert

	it = u.upper_bound(43);
	cout << "\n upper_bound 43(absent (repNrmal = 45) ) est: " << it->first << "\n\n\n";
	it = u.upper_bound(71);
	cout << "\n upper_bound 71(absent (repNrmal = 75) ) est: " << it->first << "\n\n\n";

	it = u.upper_bound(30);
	cout << "\n upper_bound(30) present (repNrmal = 35 ) ) est: " << it->first << "\n\n\n";

	//===========================================================================>insert

}