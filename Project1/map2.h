#pragma once
//
//  unordered_set2.h
//  MAP-AVL
//
//  Jean Goulet 17-03-17.
//  Copyleft 2017 UdeS
//
//
//
//
//  DOGOY, HARAN MOURNO SULIMAN (hars1807@usherbrooke.ca)
//
//
//



#ifndef map2_h
#define map2_h

#include "map.h"

///////////////////////////////////////////////////////////////////////////
// lower_bound, upper_bound et find

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::lower_bound(const Tclef& c)const
{
	auto it = iterator(RACINE);
	auto it_low = iterator(RACINE);
	while (it.POINTEUR != APRES->PARENT && it.POINTEUR != AVANT->PARENT)
	{
		if (!(it.POINTEUR->DROITE != nullptr)) {
			it_low = iterator(it);
			break;
		}
		else if (it->first < c) {
			if (it->first < it_low->first)it_low = iterator(it);
			it = iterator(it.POINTEUR->DROITE);
		}
		else if (c < it->first)
		{
			if (it->first < it_low->first)it_low = iterator(it);
			it = iterator(it.POINTEUR->GAUCHE);
		}
		else {
			return it;
		}
	}
	return it_low;
}


// it ++ apel Directm avancer en inordre
template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::upper_bound(const Tclef& c)const
{
	auto it = iterator(RACINE);
	auto it_low = iterator(RACINE);
	while (it.POINTEUR != APRES->PARENT && it.POINTEUR != AVANT->PARENT)
	{
		if (!(it.POINTEUR->DROITE != nullptr)) {
			if (it->first < it_low->first && c < it->first)
				it_low = iterator(it);
			break;
		}
		else if (it->first < c) {
			it = iterator(it.POINTEUR->DROITE);
		}
		else if (c < it->first)
		{
			if (it->first < it_low->first)
				it_low = iterator(it);
			it = iterator(it.POINTEUR->GAUCHE);
		}
		else {
			it = iterator(it.POINTEUR->DROITE);
		}
	}
	return it_low;
}

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::find(const Tclef& c)const
{
	auto it = begin();
	if (!(c < lower_bound(c)->first) && !(lower_bound(c)->first < c)) return  lower_bound(c);
	return it;
}

///////////////////////////////////////////////////////////////////////////
//insert avec indice

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::insert(iterator j, const Tclef& c)
{
	// creer_reference()
	return insert(c).first;
}


///////////////////////////////////////////////////////////////////////////
//erase a partir d'une position

template <typename Tclef, typename Tvaleur>
typename map<Tclef, Tvaleur>::iterator map<Tclef, Tvaleur>::erase(iterator i)
{
	/*noeud* temp;
	auto p = i->POINTEUR;

	if (p == nullptr)
		return nullptr;
	else if (creer_reference(p) != p)
	{
		p->first = temp->first;
		p->DROITE = erase(p->DROITE);
	}
	else
	{
		temp = p;
		if (p->GAUCHE == nullptr)
			p = p->DROITE;
		else if (p->DROITE == nullptr)
			p = p->GAUCHE;
		delete temp;
	}
	if (p == nullptr)
		return p;
	return p;*/

	if (i == end())throw(std::out_of_range("À la fin"));
	erase(i++->first);
	return i;
}



///////////////////////////////////////////////////////////////////////////
// gestion de l'equilibre de l'arbre
//effectuer une rotation simple de la droite vers la gauche
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_droite_gauche(noeud*& p)
{
	int idp = p->DROITE->INDICE;
	int ip = p->INDICE;

	int nip = -idp - std::max(0, -idp) + 1 + ip;
	int nia = idp - std::max(0, -nip) + 1;
	p->DROITE->INDICE = nia;
	p->INDICE = nip;
	p->DROITE->PARENT = p->PARENT;
	p->PARENT = p->DROITE;

	noeud* dp = p->DROITE;
	if (dp->GAUCHE != nullptr) {
		dp->GAUCHE->PARENT = p;
		dp->INDICE += 1;
		p->INDICE = 0;
	}
	p->DROITE = dp->GAUCHE;
	dp->GAUCHE = p;
	p = dp;

}

//effectuer une rotation simple de la gauche vers la droite
template <typename Tclef, typename Tvaleur>
void map<Tclef, Tvaleur>::rotation_gauche_droite(noeud*& p)
{
	int igp = p->GAUCHE->INDICE;
	int ip = p->INDICE;
	int nib = -igp - std::max(0, -igp) - 1 + ip;
	int nia = igp - std::max(0, -nib) - 1;

	p->GAUCHE->INDICE = nia;
	p->INDICE = nib;

	p->GAUCHE->PARENT = p->PARENT;
	p->PARENT = p->GAUCHE;

	noeud* gp = p->GAUCHE;
	if (gp->DROITE != nullptr) {
		gp->DROITE->PARENT = p;
	}
	p->GAUCHE = gp->DROITE;
	gp->DROITE = p;
	p = gp;


}


#endif /* unordered-set2_h*/
