//
//  Karakter.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#ifndef Karakter_hpp
#define Karakter_hpp

class Karakter {
private:
    std::string emri_i_shkronjes;
public:
    
    bool operator == ( const Karakter &a) const {
        if ( this -> emri_i_shkronjes == a.emri_i_shkronjes ) return true;
        return false;
    }
    
    void setEmri_i_shkronjes(std::string name){
        this -> emri_i_shkronjes = name;
    }
    std::string getEmri_i_shkronjes(){
        return this -> emri_i_shkronjes;
    }
};
#endif /* Karakter_hpp */
