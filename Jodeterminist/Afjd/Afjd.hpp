//
//  Afjd.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#ifndef Afjd_hpp
#define Afjd_hpp

#include "../Jodeterminist.hpp"

class Afjd : public Jodeterminist {
public:
    //userActions
    void userShfaqMenu(){
        std::cout << "Shtyp numrin 1 per te konvertuar AFJD ne AFD : ";
        int zgjedhje;
        std::cin>>zgjedhje;
        
        (zgjedhje == 1) ? konverto() : void();
    }
    
    // konvertoNeAfd.cpp
    void konverto();
};

#endif /* Afjd_hpp */
