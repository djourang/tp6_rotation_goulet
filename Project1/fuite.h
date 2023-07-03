//
//  fuite.h
//  
//
//  Jean Goulet 17-02-10.
//
//

#ifndef fuite_h
#define fuite_h

#include <iostream>
using namespace std;

struct OBJET {
    double rep;
    static int NOMBRE;
    static int COMPARAISONS;
    static int NB_CELLULES;
    static OBJET* PREMIER;
    OBJET(double i = 0);
    OBJET(const OBJET& x);
    ~OBJET();
    OBJET& operator=(const OBJET& x);
    bool operator<(const OBJET& droite)const;
    bool operator<=(const OBJET& droite)const;
    bool operator>(const OBJET& droite)const;
    bool operator>=(const OBJET& droite)const;
    bool operator==(const OBJET& droite)const;
    bool operator!=(const OBJET& droite)const;
    int nb_comparaisons();
};

std::ostream& operator<<(std::ostream& out, const OBJET& O);


//
//  fuite.cpp
//
//


int OBJET::NOMBRE = 0;
int OBJET::COMPARAISONS = 0;
int OBJET::NB_CELLULES = 0;
OBJET* OBJET::PREMIER = nullptr;

OBJET::OBJET(double i) {
    rep = i;
    if (PREMIER == nullptr) { PREMIER = this; }
    ++OBJET::NOMBRE;
}

OBJET::OBJET(const OBJET& x) :OBJET(x.rep) {}

OBJET:: ~OBJET() {
    --OBJET::NOMBRE;
    if (this == PREMIER) {
        std::cout << OBJET::NOMBRE << " objets non détruits" << std::endl;
        std::cout << OBJET::NB_CELLULES << " cellules encore actives" << endl;
    }
}

OBJET& OBJET::operator=(const OBJET& x) {
    rep = x.rep;
    return *this;
}

bool OBJET::operator<(const OBJET& droite)const {
    ++OBJET::COMPARAISONS;
    return rep < droite.rep;
}

bool OBJET::operator<=(const OBJET& droite)const {
    static bool premier = true;
    if (premier) {
        premier = false;
        std::cout << "L'opérateur <= est INTERDIT!" << endl;
    }
    ++OBJET::COMPARAISONS;
    return rep <= droite.rep;
}

bool OBJET::operator>(const OBJET& droite)const {
    static bool premier = true;
    if (premier) {
        premier = false;
        std::cout << "L'opérateur > est INTERDIT!" << endl;
    }
    ++OBJET::COMPARAISONS;
    return rep > droite.rep;
}

bool OBJET::operator>=(const OBJET& droite)const {
    static bool premier = true;
    if (premier) {
        premier = false;
        std::cout << "L'opérateur >= est INTERDIT!" << endl;
    }
    ++OBJET::COMPARAISONS;
    return rep >= droite.rep;
}

bool OBJET::operator==(const OBJET& droite)const {
    static bool premier = true;
    if (premier) {
        premier = false;
        std::cout << "L'opérateur == est INTERDIT!" << endl;
    }
    ++OBJET::COMPARAISONS;
    return rep == droite.rep;
}

bool OBJET::operator!=(const OBJET& droite)const {
    static bool premier = true;
    if (premier) {
        premier = false;
        std::cout << "L'opérateur != est INTERDIT!" << endl;
    }
    ++OBJET::COMPARAISONS;
    return rep != droite.rep;
}

std::ostream& operator<<(std::ostream& out, const OBJET& x) {
    return out << x.rep;
}

int OBJET::nb_comparaisons() {
    int avant = OBJET::COMPARAISONS;
    OBJET::COMPARAISONS = 0;
    return avant;
}

#endif /* fuite_h */
