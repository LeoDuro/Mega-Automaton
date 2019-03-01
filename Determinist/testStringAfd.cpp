//
//  testStringAfd.cpp
//  Mega Automaton
//
//  Created by Leo Duro on 06/02/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#include "Afd.hpp"

int Afd::gjejIndexGjxSh( Gjendje &gj, const std::string &str ){
    int gjendje_index  = gjejIndexGjendje(gj);
    int shkronje_index = gjejIndexShkronje(str);
    
    return gjejIndexGjendje( *tranzicionet[gjendje_index][shkronje_index] );
}

int Afd::gjejIndexGjxSh( Gjendje &gj, Karakter &shkronje ){
    int gjendje_index  = gjejIndexGjendje(gj);
    int shkronje_index = gjejIndexShkronje(shkronje);
    
    return gjejIndexGjendje( *tranzicionet[gjendje_index][shkronje_index] );
}

void Afd::updateIndexGjendje(int &gjendje_index,const int &shkronje_index){
    // funksioni updaton parametrin gjendje_index te marre me reference
    for( int m = 0; m < gjendjet.size(); m++){
        if ( *tranzicionet[gjendje_index][shkronje_index] == gjendjet[m] ){
            gjendje_index = m;
            break;
            //break sepse current index u updatua dhe po u ekzekutua
            //perseri do kemi gabim per shkak te if (tran[current_index][] <----
        }
    }
}

bool Afd::pranonEpsilon(const int &gjendje_index, const std::string &karakter){
    if (gjendjet[gjendje_index].isFinal() &&
        gjendjet[gjendje_index].isInitial() &&
        karakter == "Ɛ"){ return true; }
    return false;
}

bool Afd::shfaqValidoKalimet( const int &gjendje_index, const int &shkronje_index ){
    if ( tranzicionet[gjendje_index][shkronje_index]->isFinal() ) {
        std::cout << " --" << alfabet[shkronje_index].getEmri_i_shkronjes()
        << "---> " << tranzicionet[gjendje_index][shkronje_index]->getname()<<"!F!";
        return true;
    }else {
        std::cout << " --" << alfabet[shkronje_index].getEmri_i_shkronjes()
        << "---> " << tranzicionet[gjendje_index][shkronje_index]->getname();
        return false;
    }
}

void Afd::testStr(){
    std::cout << "\n\nJepni nje string per te testuar automatin nqs e pranon ose jo ate string.\n";
    std::cout << "Kujdes !!! Stringu nuk do te pranohet nqs ka shkronja qe nuk jane pjese te alfabetit.\n";
    std::cout << "Epsiloni shenohet me 'Ɛ' dhe do te pranohet vetem kur gjendja eshte FILLESTARE dhe PERFUNDIMTARE.\n";
    std::cout << "Kujdes !!! nqs stringu fillon/mbaron me karakter te dyfishte si 'dh' atehere ai duhet formatuar:\n";
    std::cout << "Fillim ->  ,dh,aab,dh,abba,dh,,dh,baaba,dh,  <- kur ndodhet ne fund.";
    std::cout << "Shkruaj NDALO per te perfunduar testimin\n";
    std::cout << "Shkruani stringun ne linjen me poshte: \n";
    
    std::string string_test = "";
    std::string karakter = "";
    
    int shkronje_index = -1;
    bool pranohet = false;
    
    while (true) {
        std::cin >> string_test;
        if ( string_test == "NDALO" ) break;
        
        // gjendja e pare
        int gjendje_index = gjejIndexGjendjeFillestare();
        std::cout << "-->" << gjendjet[gjendje_index].getname();
        if (gjendjet[gjendje_index].isFinal() ) std::cout << "!F!";
        
        for (int i = 0 ; i < string_test.length(); i++) {
            karakter = string_test[i];
            //epsilon pranohet vetem kur gjendja eshte fillestare dhe finale karakteri eshte "`"
            if ( pranonEpsilon(gjendje_index, karakter) ) { pranohet = true; break; }
            
            if ( karakter == "," ) {
                for (int l = i+1; l < string_test.length(); l++) {// gjejme presjen tj
                    karakter = string_test[l];
                    if ( karakter == "," ) {
                        karakter = string_test.substr( i+1, l-i-1 );
                        i = l;
                        break;}
                }
                
                shkronje_index = gjejIndexShkronje( karakter );
                if ( shkronje_index == -1 ) { pranohet = false; break; }
                pranohet = shfaqValidoKalimet(gjendje_index, shkronje_index);
                updateIndexGjendje(gjendje_index, shkronje_index); }
            else {
                shkronje_index = gjejIndexShkronje( karakter );
                if ( shkronje_index == -1 ) { pranohet = false; break; }
                pranohet = shfaqValidoKalimet( gjendje_index, shkronje_index );
                updateIndexGjendje( gjendje_index, shkronje_index ); }
        }
        pranohet? std::cout << "\nStringu pranohet.\n" : std::cout << "\nStringu nuk pranohet.\n" ;
    }
}
