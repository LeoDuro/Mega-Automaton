//
//  Afjd_e.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#ifndef Afjd_e_hpp
#define Afjd_e_hpp

#include "../Jodeterminist.hpp"

class Afjd_e : public Jodeterminist {
public:
    // userActions
    void userShfaqMenu(){
        std::cout << "Shtyp numrin 1 per te konvertuar Ɛ-AFJD ne AFJD : ";
        int zgjedhje;
        std::cin>>zgjedhje;
        
        (zgjedhje == 1) ? konverto() : void();
    }
    
    // konvertoNeAfjd.hpp
    std::vector<Gjendje> getMeEpsilon( Gjendje &gj );
    std::vector<Gjendje> getEpsilonMbyllje( Gjendje &gj );
    std::vector<Gjendje> getMeShkronje ( const std::vector<Gjendje> &epsilonMbyllje, Karakter &k );
    void konverto();
};

#endif /* Afjd_e_hpp */
