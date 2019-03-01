//
//  main.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#include <iostream>

#include "Determinist/Afd.hpp"
#include "Jodeterminist/Afjd/Afjd.hpp"
#include "Jodeterminist/Afjd_e/Afjd_e.hpp"

int main () {
    while (true) {
        
        std::string zgjedhje;
        std::cout << "Zgjidhni nje prej opsioneve te meposhtem.\n";
        std::cout << "Shtyp 1 per: Ɛ-Afjd -> Afjd -> Afd -> Minimizim -> Testo String.\n";
        std::cout << "Shtyp 2 per: Afjd -> Afd -> Minimizim -> Testo String.\n";
        std::cout << "Shtyp 3 per: Afd -> Minimizim -> Testo String.\n";
        std::cout << "Shtyp cdo buton tjeter per te dale.\n";
        std::cout << "Zgjedhja juaj: ";
        std::cin  >> zgjedhje;
        std::cout << "\n";
        
        if ( zgjedhje == "1" ) {
            Afjd_e e;
            e.user_Run(1);
            e.userShfaqMenu();
        }else if ( zgjedhje == "2" ) {
            Afjd j;
            j.user_Run(0);
            j.userShfaqMenu();
        }else if ( zgjedhje == "3" ) {
            Afd a;
            a.user_Run();
        }else {
            return 0;
        }
        
    }
    
    return 0;
}
