//
//  userActionsAfd.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 06/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#include "Afd.hpp"

void Afd::user_setTranzicionet( const int &nr_gjendje, const int &nr_alfabet ) {
    std::cout << "Ju lutem jepni funksionin e tranzicionit per AFD-ne\n";
    std::cout << "Pas cdo rreshti vendosni emrin e gjendjes ku kalon automati me ate shkronje\n";
    user_printGjendjet();
    inicializoTranzicionet(nr_gjendje , nr_alfabet); // inicializon tabelen dhe i ben null te gjitha
    
    std::string em_tr = "";
    for (int i = 0 ; i < nr_gjendje; i++) {
        for (int j = 0 ; j < nr_alfabet; j++) {
            std::cout << gjendjet[i].getname()<<" x "<<alfabet[j].getEmri_i_shkronjes()<<" = ";
            std::cin >> em_tr; bool flag = false;
            for (int k = 0; k < nr_gjendje; k++) {
                if ( em_tr == gjendjet[k].getname() ) {
                    tranzicionet[i][j] = &gjendjet[k]; flag =true;
                }
            }
            if (!flag) {std::cout <<"Gjendja nuk gjendet kujdes inputin."; j-=1;}
        }
    }
    std::cout << "\n----------------\n";
    std::cout << "Fund tranzicionet\n";
}
void Afd::user_printTranzicionet() {
    std::cout << "\nTranzicionet jane: \n\n";
    user_printGjendjet();
    user_printAlfabet();
    for (int i = 0; i < gjendjet.size(); i++) {
        std::cout << "[" + gjendjet[i].getname() + "]";
        for (int j = 0; j < alfabet.size(); j++) {
            std::cout << "    " << tranzicionet[i][j]->getname()<<" ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void Afd::shfaqMenu(){
    int zgjedhja;
    while (true) {
        
        std::cout << "\nZgjidhni se cfare do te beni me automatin:";
        std::cout << "\nShtyp 1 per te testuar nje string:";
        std::cout << "\nShtyp 2 per te minimizuar automatin:";
        std::cout << "\nShtyp 3 per te minimizuar automatin dhe me pas per te testuar nje string:";
        std::cout << "\nOse nje numer tjeter per te terminuar programin. \n";
        std::cin >> zgjedhja;
        
        switch (zgjedhja) {
            case 1:
                testStr();
                break;
            case 2:
                minimizo();
                break;
            case 3:
                minimizo();
                testStr();
            default:
                std::cout << "\n\n\nProgrami po terminohet.    (⌐▀͡ ̯ʖ▀)=/̵͇̿̿/'̿'̿̿̿ ̿ ̿̿̿̿       -   ༼ つ ಥ_ಥ ༽つ -> user jooooo  \n";
                return;
        }
    }
}
void Afd::user_Run() {
    int nr_gjendje = 0 , nr_shkronja = 0;

    std::cout << "Jepni NUMRIN e gjendjeve te automatit:  ";  std::cin >> nr_gjendje;
    user_setGjendjet(nr_gjendje);
    std::cout << "Jepni NUMRIN e shkronjave:  "; std::cin >> nr_shkronja;
    user_setAlfabet(nr_shkronja);
    
    user_setTranzicionet(nr_gjendje, nr_shkronja);
    user_printTranzicionet();
    
    shfaqMenu();
}
