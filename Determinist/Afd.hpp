//
//  Afd.hpp
//  Mega Automaton
//
//  Created by Leo Duro on 31/01/2019.
//  Copyright © 2019 Leo Duro. All rights reserved.
//

#ifndef Afd_hpp
#define Afd_hpp

#include "../Automat.hpp"

class Afd : public Automat {
private:
    std::vector < std::vector < Gjendje* > > tranzicionet;
public:
    
    // set/get parametrat ne total
    void inicializoTranzicionet( const int &nr_gjendje, const int &nr_alfabet ) {
        std::vector<std::vector<Gjendje*>> v(nr_gjendje, std::vector<Gjendje*>(nr_alfabet, NULL));
        this->tranzicionet = v;
    }
    void setTranzicionetTotal( std::vector < std::vector < Gjendje* > > tranzicionet ){
        this-> tranzicionet = tranzicionet;
    }
    std::vector < std::vector < Gjendje* > > getTranzicionet(){
        return this -> tranzicionet;
    }
   

    // user_Inputet merren nga perdoruesi userActions.hpp
    void user_setTranzicionet(const int &nr_gjendje, const int &nr_alfabet);
    void user_printTranzicionet();
    
    
    // testim stringu testStringAFD.hpp
    int gjejIndexGjxSh( Gjendje &gj, const std::string &shkronje );
    int gjejIndexGjxSh( Gjendje &gj, Karakter &k );
    void updateIndexGjendje(int &gjendje_index, const int &shkronje_index);
    bool pranonEpsilon(const int &gjendje_index, const std::string &karakter);
    bool shfaqValidoKalimet( const int &gjendje_index, const int &shkronje_index );
    void testStr();
    
    
    // minimizimi i automatit (metoda e tabeles) minimizim.hpp
    void vendosGjendjetSipasIndexit(const std::vector <std::vector <int> > &tabela, std::vector<Gjendje> &gjendjet);
    void hiqTePakapshmet();
    std::vector < std::vector <int> > getTabelaEMinimizuar();
    std::vector <Gjendje> getDyshet(const std::vector < std::vector <int> > &tabela );
    std::vector < Gjendje > bashkoEkuivalentet( const std::vector < Gjendje > &gjendjet_e_reja );
    std::vector <Gjendje> shtoEkuivalentet(const std::vector < std::vector <int> > &tabela );
    int gjejTranzicionetESubgjendjes( Gjendje &gjendje, Karakter &karakter, std::vector <Gjendje> &ekuiv);
    void rregTranzicionet();
    void minimizo();
    
    // menu userActions.hpp
    void shfaqMenu();
    void user_Run();
        
};

#endif /* Afd_hpp */
