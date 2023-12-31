//
//  map.h
//  MAP-AVL
//
//  Jean Goulet 22-03-18
//  Copyleft 2022 UdeS
//

#ifndef map_h
#define map_h


#include <vector>
#include <set>
#include <string>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "fuite.h"

template <typename Tclef, typename Tvaleur>
class map
{
public:
	class iterator;
	friend class iterator;
	typedef std::pair<const Tclef, Tvaleur> PAIRE;
private:
	struct noeud
	{
		PAIRE* CONTENU;
		noeud* PARENT, * GAUCHE, * DROITE;
		int INDICE;
		noeud(const Tclef& c, noeud* PAR, noeud* GAU = nullptr, noeud* DRO = nullptr)
			: PARENT(PAR), GAUCHE(GAU), DROITE(DRO), INDICE(0) {
			CONTENU = new PAIRE(c, Tvaleur());
			++OBJET::NB_CELLULES;
		}

		noeud() :CONTENU(nullptr), PARENT(nullptr), GAUCHE(nullptr), DROITE(nullptr), INDICE(0) {
			++OBJET::NB_CELLULES;
		}

		noeud(const noeud&) = delete;

		~noeud() {
			delete CONTENU;
			CONTENU = nullptr;
			PARENT = GAUCHE = DROITE = nullptr;
			--OBJET::NB_CELLULES;
		}
	};

	noeud* APRES;
	noeud* AVANT;
	noeud* RACINE;
	noeud noeud_AVANT;
	noeud noeud_APRES;
	size_t SIZE;

	//fonctions privees
	noeud*& creer_reference(noeud*);
	bool plus_petit(const Tclef&, noeud*)const;
	bool plus_petit(noeud*, const Tclef&)const;

	void clear(noeud*&);

	bool insert(const Tclef&, noeud*&, iterator&);
	bool ajoute_gauche(const Tclef&, noeud*&, iterator&);
	bool ajoute_droite(const Tclef&, noeud*&, iterator&);

	bool erase(const Tclef&, noeud*&, noeud*&);
	bool enleve_gauche(const Tclef&, noeud*&, noeud*&);
	bool enleve_droite(const Tclef&, noeud*&, noeud*&);
	bool eliminer(noeud*&, noeud*&);

	void allonger_a_gauche(noeud*&);
	void allonger_a_droite(noeud*&);
	void rotation_gauche_droite(noeud*&);
	void rotation_droite_gauche(noeud*&);

	void afficher(noeud*, size_t, std::vector<std::string>&, double&, size_t&) const;
	void afficher_barres(std::vector<std::string>&, size_t)const;
public:
	map();
	~map();
	map(const map&);
	map& operator=(const map&);

	size_t size()const { return SIZE; }
	bool empty()const { return SIZE == 0; }
	void clear();

	iterator find(const Tclef&)const;
	iterator lower_bound(const Tclef&)const;
	iterator upper_bound(const Tclef&)const;

	Tvaleur& operator[](const Tclef&);
	Tvaleur& at(const Tclef&);
	std::pair<iterator, bool> insert(const Tclef&);
	iterator insert(iterator, const Tclef&);

	size_t erase(const Tclef&);
	iterator erase(iterator);

	//fonction d'iteration
	iterator begin()const;
	iterator end()const;

	//fonction de mise au point
	int verifier_hauteurs(noeud* = nullptr)const;
	void afficher()const;
};

template <typename Tclef, typename Tvaleur>
class map<Tclef, Tvaleur>::iterator
{
private:
	noeud* POINTEUR;
	static void avancer(noeud*&);
	static void reculer(noeud*&);
	friend class map<Tclef, Tvaleur>;
public:
	explicit iterator(noeud* p = nullptr) : POINTEUR(p) {}

	iterator(const iterator&) = default;
	iterator& operator=(const iterator&) = default;
	PAIRE& operator*() const { return *(POINTEUR->CONTENU); }
	PAIRE* operator->() const { return POINTEUR->CONTENU; }
	iterator& operator++() { avancer(POINTEUR); return *this; }                          //++i
	iterator operator++(int) { iterator copie(*this); avancer(POINTEUR); return copie; } //i++
	iterator& operator--() { reculer(POINTEUR); return *this; }                          //--i
	iterator operator--(int) { iterator copie(*this); reculer(POINTEUR); return copie; } //i--
	bool operator==(const iterator& dr) const { return POINTEUR == dr.POINTEUR; }
	bool operator!=(const iterator& dr) const { return POINTEUR != dr.POINTEUR; }
};

///////////////////////////////////////////////////////////////////////////
// fonctions d'iteration

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::begin() const
{
	noeud* p = AVANT;
	map<Tclef, Tvaleur>::iterator::avancer(p);
	return iterator(p);
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::end() const
{
	return iterator(APRES);
}

///////////////////////////////////////////////////////////////////////////
// fonctions supplementaires de la class iterator

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::iterator::avancer(noeud*& p)
{
	//AVANCER le pointeur p vers le prochain noeud en inordre
	//cette fonction fait automatiquement exception
	//si on avance au-dela de la fin
	if (p->DROITE != nullptr)
		for (p = p->DROITE; p->GAUCHE != nullptr; p = p->GAUCHE);
	else
	{
		noeud* pa;
		for (pa = p->PARENT; pa->GAUCHE != p; p = pa, pa = p->PARENT);
		p = pa;
	}
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::iterator::reculer(noeud*& p)
{
	//RECULER le pointeur p vers le noeud precedent en inordre
	//p sera nullptr si on recule au-dela du debut
	//cas limite: reculer de la fin
	if (p->GAUCHE != nullptr)
		for (p = p->GAUCHE; p->DROITE != nullptr; p = p->DROITE);
	else
	{
		noeud* pa;
		for (pa = p->PARENT; pa->DROITE != p; p = pa, pa = p->PARENT);
		p = pa;
	}
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees


template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::plus_petit(const Tclef& V, noeud* PTR)const {
	if (PTR == APRES)return true;
	else if (PTR == AVANT)return false;
	else return V < PTR->CONTENU->first;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::plus_petit(noeud* PTR, const Tclef& V)const {
	if (PTR == AVANT)return true;
	else if (PTR == APRES)return false;
	else return PTR->CONTENU->first < V;
}


template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::noeud*& map<Tclef, Tvaleur>::creer_reference(noeud* p)
{
	if (p == RACINE)
		return RACINE;
	else if (p->PARENT->GAUCHE == p)
		return p->PARENT->GAUCHE;
	else
		return p->PARENT->DROITE;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::clear(noeud*& p)
{
	if (p == nullptr)return;
	clear(p->GAUCHE);
	clear(p->DROITE);
	if (p != AVANT && p != APRES) {
		delete p;
		p = nullptr;
	}
}


///////////////////////////////////////////////////////////////////////////
// fonctions privees d'insertion

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::insert(const Tclef& c, noeud*& p, iterator& r) {
	if (plus_petit(c, p))
		return ajoute_gauche(c, p, r);
	else if (plus_petit(p, c))
		return ajoute_droite(c, p, r);
	else {
		r = iterator(p);
	}
	return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::ajoute_gauche(const Tclef& c, noeud*& p, iterator& r) {
	//std::cout<<"ajoute_gauche de "<<p<<" "<<c<<endl;
	if (p->GAUCHE == nullptr)
	{
		//nouvelle feuille
		p->GAUCHE = new noeud(c, p);
		r = iterator(p->GAUCHE);
		++SIZE;
		return(++(p->INDICE) == 1);
	}
	else if (insert(c, p->GAUCHE, r))
	{ //ajout general a gauche
		allonger_a_gauche(p);
		return p->INDICE != 0;
	}
	else
		return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::ajoute_droite(const Tclef& c, noeud*& p, iterator& r)
{
	//std::cout<<"ajoute_droite de "<<p<<" "<<c<<endl;
	if (p->DROITE == nullptr)
	{
		//nouvelle feuille
		p->DROITE = new noeud(c, p);
		r = iterator(p->DROITE);
		++SIZE;
		return(--(p->INDICE) == -1);
	}
	else if (insert(c, p->DROITE, r))
	{ //ajout general a droite
		allonger_a_droite(p);
		return p->INDICE != 0;
	}
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions privees d'elimination

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::erase(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
	//cout<<"Erase "<<c<<" � partir de "<<p<<endl;
	if (plus_petit(c, p))
		return enleve_gauche(c, p, aRemplacer);
	else if (plus_petit(p, c))
		return enleve_droite(c, p, aRemplacer);
	else
	{
		aRemplacer = p;
		if (p->GAUCHE == AVANT)return enleve_droite(c, p, aRemplacer);
		else return enleve_gauche(c, p, aRemplacer);
	}
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::enleve_gauche(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
	//cout<<"Enleve � gauche "<<c<<" de "<<p->CONTENU<<endl;
	if (p->GAUCHE == nullptr)
		return eliminer(p, aRemplacer);
	else if (erase(c, p->GAUCHE, aRemplacer))
	{
		allonger_a_droite(p);
		return p->INDICE == 0;
	}
	else
		return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::enleve_droite(const Tclef& c, noeud*& p, noeud*& aRemplacer)
{
	//cout<<"Enleve � droite "<<c<<" de "<<p->CONTENU<<endl;
	if (p->DROITE == nullptr)
		return eliminer(p, aRemplacer);
	else if (erase(c, p->DROITE, aRemplacer))
	{
		allonger_a_gauche(p);
		return p->INDICE == 0;
	}
	else
		return false;
}

template <typename Tclef, typename Tvaleur>
bool map<Tclef, Tvaleur>::eliminer(noeud*& p, noeud*& aRemplacer)
{
	if (aRemplacer != nullptr)
	{
		delete aRemplacer->CONTENU;
		aRemplacer->CONTENU = p->CONTENU;
		p->CONTENU = nullptr;
		aRemplacer = p;
		if (p->GAUCHE == nullptr)
			p = p->DROITE; else p = p->GAUCHE;
		if (p != nullptr)
			p->PARENT = aRemplacer->PARENT;
		delete aRemplacer;
		--SIZE;
		return true;
	}
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////
// fonctions publiques
//
//
//


template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::map() {
	noeud_APRES.GAUCHE = AVANT = &noeud_AVANT;          // noeud non initialiser
	AVANT->PARENT = APRES = RACINE = &noeud_APRES;        // noeud non initialiser
	APRES->INDICE = 1;
	SIZE = 0;
}

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::~map()
{
	clear();
}

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>::map(const map& source) :map()
{
	for (const auto& x : source) {
		(*this)[x.first] = x.second;
	}

}

template <typename Tclef, typename Tvaleur>
map<Tclef, Tvaleur>& map<Tclef, Tvaleur>::operator=(const map& source)
{
	if (this != &source)
	{
		this->clear();
		for (const auto& x : source)
			(*this)[x.first] = x.second;
	}
	return *this;
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::clear()
{
	clear(RACINE);
	RACINE = APRES;
	APRES->INDICE = 1;
	APRES->GAUCHE = AVANT;
	APRES->PARENT = nullptr;
	AVANT->INDICE = 0;
	AVANT->PARENT = APRES;
	SIZE = 0;
}

template <typename Tclef, typename Tvaleur>
Tvaleur& map<Tclef, Tvaleur>::at(const Tclef& c)
{
	auto p = lower_bound(c);
	if (plus_petit(c, p.POINTEUR))
		throw std::out_of_range("valeur absente du map");
	return p->second;
}


template <typename Tclef, typename Tvaleur>
Tvaleur& map<Tclef, Tvaleur>::operator[](const Tclef& c)
{
	auto r = this->insert(c);
	auto i = r.first;
	PAIRE* pa = i.POINTEUR->CONTENU;
	return pa->second;
}

template <typename Tclef, typename Tvaleur>
std::pair<typename map<Tclef, Tvaleur>::iterator, bool> map<Tclef, Tvaleur>::insert(const Tclef& c)
{
	iterator retour;
	size_t SIZE_avant = SIZE;
	insert(c, RACINE, retour);
	return std::make_pair(retour, SIZE != SIZE_avant);
}

template <typename Tclef, typename Tvaleur>
size_t map<Tclef, Tvaleur>::erase(const Tclef& c)
{
	size_t SIZE_avant = SIZE;
	if (SIZE != 0)
	{
		noeud* aRemplacer = nullptr;
		erase(c, RACINE, aRemplacer);
	}
	return SIZE_avant - SIZE;
}

///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre

//incrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::allonger_a_gauche(noeud*& p)
{
	//si le neoud *p est trop haut a gauche
	//faire les rotations necessaires
	//std::cout<<"vers la droite de "<<p->CONTENU->first<<" ("<<p->INDICE<<")"<<std::endl;
	++(p->INDICE);
	if (p->INDICE != 2)
		return;
	if (p->GAUCHE->INDICE == -1) {
		rotation_droite_gauche(p->GAUCHE);
	}
	rotation_gauche_droite(p);
}

//decrementer l'indice et verifier
//si on doit transferer des elements et le faire
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::allonger_a_droite(noeud*& p)
{
	//si le neoud *p est trop haut a droite
	//faire les rotations necessaires
	//std::cout<<"vers la gauche de "<<p->CONTENU->first<<" ("<<p->INDICE<<")"<<std::endl;
	--(p->INDICE);
	if (p->INDICE != -2)
		return;
	if (p->DROITE->INDICE == 1)
		rotation_gauche_droite(p->DROITE);
	rotation_droite_gauche(p);
}



///////////////////////////////////////////////////////////////////////////
// fonctions de mise au point


template <typename Tclef, typename Tvaleur>
int map<Tclef, Tvaleur>::verifier_hauteurs(noeud* p)const
{
	using namespace std;
	if (p == nullptr)
	{ //pour l'appel initial sans parametres
		if (RACINE == nullptr)
			return true;
		else
			p = RACINE;
	}
	int hg = 0, hd = 0;
	if (p->GAUCHE != nullptr)
		hg = verifier_hauteurs(p->GAUCHE);
	if (hg == -1)
		return -1;
	if (p->DROITE != nullptr)
		hd = verifier_hauteurs(p->DROITE);
	if (hd == -1)
		return -1;
	int ind = hg - hd;
	if (ind > 1 || ind < -1)
	{
		cerr << "le noeud " << p->CONTENU->first;
		cerr << " n'est pas en equilibre: gauche=" << hg;
		cerr << ", droite=" << hd << endl;
		return -1;
	}
	else
		return 1 + std::max(hg, hd);
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher()const
{
	using namespace std;
	double total = 0.;
	size_t max = 0;
	cout << "-------------------------------" << endl;
	vector<string> barres;
	barres.push_back("    ");
	afficher(RACINE, 1, barres, total, max);
	total = total / SIZE;
	cout << SIZE << " element"; if (SIZE > 1)cout << "s"; cout << endl;
	cout << "log(" << SIZE << "): " << log2(double(SIZE)) << endl;
	cout << "hauteur moyenne: " << total << endl;
	cout << "hauteur maximale: " << max << endl;
	cout << "-------------------------------" << endl;
}


template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher(typename map<Tclef, Tvaleur>::noeud* p, size_t niveau, std::vector<std::string>& barres, double& total, size_t& max) const
{
	using namespace std;
	if (p == 0)
		return;
	total += niveau;
	if (niveau > max)
		max = niveau;
	if (niveau >= barres.size())
		barres.push_back("    ");

	afficher(p->DROITE, niveau + 1, barres, total, max);

	//si on est un enfant de gauche arreter les barres a ce niveau
	if (p->PARENT != 0 && p->PARENT->GAUCHE == p)
		barres[niveau - 1] = "    ";

	//cout<<niveau;
	afficher_barres(barres, niveau);
	cout << "---> ";
	PAIRE* CO = p->CONTENU;
	if (p == AVANT)cout << "AVANT ";
	else if (p == APRES)cout << "APRES ";
	else {
		cout << "[" << CO->first << "," << CO->second << "] ";
	}
	//cout<<p<<" ";
	//cout<<"par="<<p->PARENT<<" ";
	//cout<<"gau="<<p->GAUCHE<<" ";
	//cout<<"dro="<<p->DROITE<<" ";
	cout << "(" << p->INDICE << ")" << endl;

	//si on est un enfant de droite barre a mon niveau
	if (p->PARENT != nullptr && p->PARENT->DROITE == p)
		barres[niveau - 1] = "   |";

	//si on a un enfant a gauche mettre des barres apres
	if (p->GAUCHE != nullptr)
		barres[niveau] = "   |";
	else
		barres[niveau] = "    ";

	//cout<<niveau;
	afficher_barres(barres, niveau + 1);
	cout << endl;

	afficher(p->GAUCHE, niveau + 1, barres, total, max);
}

template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::afficher_barres(std::vector<std::string>& barres, size_t n) const
{
	for (size_t i = 0; i < n; ++i)
		std::cout << barres[i];
}


#include<vector>


#endif /* map_h */
