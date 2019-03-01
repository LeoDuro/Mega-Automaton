//
//  konvertoNeAfjd.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 20/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

// Shembull :
//              e-mbyllje -- meShkronje -- e-mbyllje
// Gjendje: A       AB           AC             ABD     -> gjendjet qe dalin ketu (e-mbyllje e dyte),
// jane gjendjet ku kalon afjd me ate karakter(meShkronje).

#include "Afjd_e.hpp"
#include "../Afjd/Afjd.hpp"

std::vector<Gjendje> Afjd_e::getMeEpsilon( Gjendje &gj ) {
    // kurr nuk eshte empty
    std::vector<Gjendje> meEpsilon;
    
    if ( !gjejIndexGjxSh( gj, alfabet[ alfabet.size()-1 ] ).empty() ) {
        meEpsilon.push_back(gj);
        for ( auto i : gjejIndexGjxSh( gj, alfabet[ alfabet.size()-1 ] ) ) {
            meEpsilon.push_back(*i);
        }
    }else meEpsilon.push_back(gj);
    
    return meEpsilon;
}

std::vector<Gjendje> Afjd_e::getEpsilonMbyllje( Gjendje &gj ){
    std::vector<Gjendje> mbyllje = getMeEpsilon(gj);
    
    int gjat = int( mbyllje.size() );
    if ( gjat == 1 ) return mbyllje;
    
    for ( int i = 1; i < gjat; i++ ) {
        std::vector<Gjendje> tmp = getMeEpsilon( mbyllje[i] );
        for (auto tp: tmp){
            if ( std::find( mbyllje.begin(), mbyllje.end(), tp ) == mbyllje.end() ){
                mbyllje.push_back(tp); gjat+=1;
            }
        }
    }
    
    return mbyllje;
}

std::vector<Gjendje> Afjd_e::getMeShkronje ( const std::vector<Gjendje> &epsilonMbyllje, Karakter &k ){
    std::vector<Gjendje> meShkronje;
    
    for (auto i : epsilonMbyllje) {
        for (auto j : gjejIndexGjxSh(i, k) ) {
            if (std::find(meShkronje.begin(), meShkronje.end(), *j) != meShkronje.end() ) continue;
            meShkronje.push_back(*j);
        }
    }
    
    return meShkronje;
}

void Afjd_e::konverto(){
    std::vector < std::vector <std::vector<int> > > tranzicionet_afjd( gjendjet.size(), std::vector<std::vector<int>>( alfabet.size()-1 ) );
    
    for (int i = 0; i < gjendjet.size(); i++) {
        for (int shk = 0; shk < alfabet.size()-1; shk++) {
            std::vector<Gjendje> meShkronje = getMeShkronje( getEpsilonMbyllje( gjendjet[i] ), alfabet[shk] );
            if (meShkronje.empty()) continue;
            
            std::vector<Gjendje> teBashkuara;
            for ( auto meShk : meShkronje ) {
//                duhen bashkuar te gjitha ne nje vektor te vetem
                for ( auto eps2: getEpsilonMbyllje( meShk ) ) {
                    if ( std::find(teBashkuara.begin(), teBashkuara.end(), eps2) != teBashkuara.end() ) continue;
                    teBashkuara.push_back(eps2);
                }
                
            }
//            fund shkronjat
            for (auto e2 : teBashkuara) {
                tranzicionet_afjd[i][shk].push_back( gjejIndexGjendje(e2) );
            }
            teBashkuara.clear();
        }
//        fund gjend
    }
 
    Afjd eKonvertuar;
    this->alfabet.pop_back(); // heqim epsilonin;
    eKonvertuar.setAlfabetTotal(this->alfabet);
    eKonvertuar.setGjendjetTotal(this->gjendjet);
    eKonvertuar.vendosTranzicionetNgaTabela(tranzicionet_afjd);
    eKonvertuar.user_printTranzicionet();
    eKonvertuar.userShfaqMenu();
}
