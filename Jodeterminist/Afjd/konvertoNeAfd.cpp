//
//  konvertoNeAfd.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 14/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#include "Afjd.hpp"
#include "../../Determinist/Afd.hpp"


bool isInvers ( Gjendje &a, Gjendje &b ){
    
    // krahason subgj.a --me-- subgj.b
    // p.sh {2,3} = {3,2} sepse jane e njeta gjendje thjesht me emer te çrregullt.
    // p.sh {1,2,3} = {3,1,2}
    
    if ( a.kaSubgjendje() && b.kaSubgjendje() ){
        std::vector<Gjendje> sgjA = a.getSubGjendje();
        std::vector<Gjendje> sgjB = b.getSubGjendje();
        
        if (sgjA.size() != sgjB.size()) return false;
        
        bool flag = false;
        
        for (int i = 0; i < sgjA.size(); i++) {
            flag = false;
            for (int j = 0; j < sgjB.size(); j++) {
                if( sgjA[i] == sgjB[j] ) {
                    flag = true;
                }
            }
            if (!flag) {return false;}
        }
        
        return true;
    }
    
    return false;
}

int ndodhetNeTabele( Gjendje &gj, std::vector<Gjendje> &gjendjet ){
    
    for (int i = 0; i < gjendjet.size(); i++) {
        if ( gj == gjendjet[i] ) return i;
        if ( isInvers(gj, gjendjet[i]) ) return i;
    }
    
    return -1;
}

void Afjd::konverto(){
    
    std::vector <Gjendje> gjendjet_afd;
    std::vector < std::vector <int> > tranzicionet_afd;
    // alfabeti i afd njesoj si afjd prandaj
    
    gjendjet_afd.push_back( gjendjet[gjejIndexGjendjeFillestare()] );
    
    
    int madhesi = int ( gjendjet_afd.size() );
    
    for ( int i = 0; i < madhesi; i++ ) { /* per cdo gj nga gjendjet_afd*/
        std::vector <int> rreshtBosh;
        tranzicionet_afd.push_back(rreshtBosh);
        for (int j = 0; j < alfabet.size(); j++) { // per cdo shkronje nga alfabeti
            if ( gjendjet_afd[i].getname() == "-" ) {// gjendja e vdekur/boshe e shenuar me '-'
                tranzicionet_afd[i].push_back( gjejIndexGjendjeNgaTabela( gjendjet_afd[i], gjendjet_afd ) );
                // nqs vjen kjo gjendje beji te gjitha tranzicionet me alfabet boshe
                
            }else { // gjendja qe erdhi nuk eshte boshe
                
                if ( gjendjet_afd[i].kaSubgjendje() ) {
                    std::vector<Gjendje> subGjendjet = gjendjet_afd[i].getSubGjendje();
                    Gjendje eBashkuar;
                    
                    for (auto subGj:subGjendjet){
                        // vektori me subgjendje bashkohet
                        std::vector <Gjendje*> perBashkim = gjejIndexGjxSh(subGj, alfabet[j]);
                        if (perBashkim.empty()) {continue;}
                        
                        Gjendje tmp = bashkoji(perBashkim);
                        eBashkuar = Gjendje::bashko( eBashkuar, tmp);
                        tmp.clearGjendje();
                    }
                    
                    if (eBashkuar.getname() == "" ) {
                        eBashkuar.setAtributet( "-", false, false );
                    }
                    
                    int ndodhet = ndodhetNeTabele(eBashkuar, gjendjet_afd);
                    if ( ndodhet != -1  ) {
                        // nqs kjo gj e re e gjeneruar nga subgj[x] x sh gjendet atehere vendos tranzicionet te ajo gjendje
                        tranzicionet_afd[i].push_back( ndodhet );
                    }else {
                        // nk gjendjet shtoje ne gjendjet_aft rrit madhesine me 1
                        gjendjet_afd.push_back(eBashkuar);
                        tranzicionet_afd[i].push_back( gjejIndexGjendjeNgaTabela(eBashkuar, gjendjet_afd) );
                        madhesi += 1;
                    }
                    
                    eBashkuar.clearGjendje();
                    
                }else { //  vjen nje gjendje pa subgjendje
                    Gjendje eBashkuar;
                    std::vector <Gjendje*> perBashkim = gjejIndexGjxSh(gjendjet_afd[i], alfabet[j]);
                    
                    if ( perBashkim.empty() ) {
                        eBashkuar.setAtributet("-", false, false);
                    }else {
                        eBashkuar =  bashkoji(perBashkim);
                    }
                                            
                    int ndodhet = ndodhetNeTabele(eBashkuar, gjendjet_afd);
                    if ( ndodhet != -1  ) {
                        // nqs kjo gj e re e gjeneruar nga subgj[x] x sh gjendet atehere vendos tranzicionet te ajo gjendje
                        tranzicionet_afd[i].push_back( ndodhet );
                    }else {
                        // nk gjendjet shtoje ne gjendjet_aft rrit madhesine me 1
                        gjendjet_afd.push_back(eBashkuar);
                        tranzicionet_afd[i].push_back( gjejIndexGjendjeNgaTabela( eBashkuar, gjendjet_afd ) );
                        madhesi += 1;
                    }
                        
                    eBashkuar.clearGjendje();
                    
                } // fund else 2
                
            } // fund else 1
            
        } // fund for shkronja
        
    } // fund for gjendjeve
    
    // gjendja e pare eshte fillestarja
    // nisemi nga gjendja e dyte dhe heqim nga cdo gjendje atributin e fillestar
    for (int i = 1; i < gjendjet_afd.size(); i++ ) {
        gjendjet_afd[i].setAtributet(gjendjet_afd[i].getname(), gjendjet_afd[i].isFinal(), false);
        gjendjet_afd[i].clearSubGjendje();
    }
    
    std::cout << "\n Afjd po konvertohet ne Afd \n";
    
    Afd perKthim;
    perKthim.setAlfabetTotal(this->getAlfabet());
    perKthim.vendosGjendjetSipasIndexit(tranzicionet_afd, gjendjet_afd);
    perKthim.user_printTranzicionet();
    perKthim.shfaqMenu();
    
}
