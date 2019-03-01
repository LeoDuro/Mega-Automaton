//
//  Gjendje.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#ifndef Gjendje_hpp
#define Gjendje_hpp

class Gjendje {
private:
    std::string emri;
    bool eshteFinale;
    bool eshteFillestare;
    std::vector < Gjendje > subGjendje; // minimized || afjd future
    bool kaSubGjendje = false;
public:
    
    bool operator == (const Gjendje& a) const {
        if ( a.emri   ==  this -> emri &&
             a.eshteFinale   ==  this -> eshteFinale &&
             a.eshteFillestare ==  this -> eshteFillestare ) return true;
        return false;
    }
    
    // metoda te gjendjes
    bool isFinal(){
        return this->eshteFinale;
    }
    bool isInitial(){
        return this->eshteFillestare;
    }
    std::string getname(){
        return this->emri;
    }
    void setAtributet( const std::string &name , bool finale, bool initial ){
        this -> emri = name;
        this -> eshteFinale = finale;
        this -> eshteFillestare = initial;
    }
    void clearGjendje(){
        emri = "";
        eshteFinale = false;
        eshteFillestare = false;
        subGjendje.clear();
        kaSubGjendje = false;
    }
    
    
    // metoda te subgjendjeve
    bool kaSubgjendje(){
        return this->kaSubGjendje;
    }
    void setSubGjendje ( Gjendje &gj ){
        kaSubGjendje = true;
        this -> subGjendje.push_back(gj);
    }
    std::vector < Gjendje > getSubGjendje () {
        return this -> subGjendje;
    }
    void setSubGjendjeTotale( std::vector < Gjendje > &subGjendje ){
        kaSubGjendje = true;
        this -> subGjendje = subGjendje;
    }
    void clearSubGjendje() {
        this -> subGjendje.clear();
        kaSubGjendje = false;
    }
    
    static Gjendje bashko( Gjendje &gj1, Gjendje &gj2){
        Gjendje ebashkuar;
        std::string e = gj1.getname();
        
        if ( e == "" && gj2.getname() == "" ){
            ebashkuar.setAtributet( e, false, false );
            return ebashkuar;
        }else if (e == ""){
            ebashkuar.setAtributet( gj2.getname(), gj2.isFinal(), gj2.isInitial() );
            std::vector <Gjendje> gj2Sub = gj2.getSubGjendje();
            if ( !gj2Sub.empty() ) ebashkuar.setSubGjendjeTotale(gj2Sub);
            return ebashkuar;
        }else if ( gj2.getname() == "" ) {
            ebashkuar.setAtributet( gj1.getname(), gj1.isFinal(), gj1.isInitial() );
            std::vector <Gjendje> gj1Sub = gj1.getSubGjendje();
            if ( !gj1Sub.empty() ) ebashkuar.setSubGjendjeTotale(gj1Sub);
            return ebashkuar;
        }
        
        
        bool f = gj1.isFinal() || gj2.isFinal();
        bool i = gj1.isInitial() || gj2.isInitial();
        
        
        bool flag = true;
        
        std::vector <Gjendje> gj1Sub = gj1.getSubGjendje();
        if( gj1Sub.empty() ) { gj1Sub.push_back(gj1); }
        
        std::vector <Gjendje> gj2Sub = gj2.getSubGjendje();
        if( gj2Sub.empty() ) { gj2Sub.push_back(gj2); }
        
        
        // vendos flag = true
        // nqs gjendja gjendet te sub1 flag = false
        // nqs pas iterimit nuk gjendet flag do te jete true
        // e shtojme te gj1Sub ate gjendje qe nuk gjendet te gj1Sub
        // dhe emrin e saj ja shtojm gjendjes gj1
        for (int i = 0; i < gj2Sub.size(); i++) {
            flag = true;
            for (int j = 0; j < gj1Sub.size(); j++) {
                if ( gj2Sub[i] == gj1Sub[j] )  flag = false;
            }
            
            if (flag) {
                gj1Sub.push_back( gj2Sub[i] );
                e.append( gj2Sub[i].getname() );
            }
        }
        
        
        ebashkuar.setSubGjendjeTotale(gj1Sub);
        ebashkuar.setAtributet( e, f, i );
        return ebashkuar;
    }
};

#endif /* Gjendje_hpp */
