//
//  main.cpp
//  Deck_of_cards_objects
//
//  Created by Senir Dinar on 20/09/2022.
//

#include <iostream>
#include "deck.h"

int main()
{
    Deck deck;
 
    std::cout<< " \n There are "<<deck.remaining()<<" cards remaining\n";
    const Card temp = deck.deal_card();
    
    std::cout<<"\n dealt card is: "<<temp;
    std::cout<<"\n There are "<<deck.remaining()<<" cards remaining";
    
    const std::vector<Card> CardVec = deck.deal_hand(9);
    if(CardVec[0] == CardVec[1])
        std::cout<<"\n oh dear... two identical cards";
    else
        std::cout<<"\n They don't match";
    
    for( int i=0;i< CardVec.size();++i)
    {
        std::cout<<CardVec[i];
    }
    std::cout<< " \n There are "<<deck.remaining()<<" cards remaining";
    
    deck.new_deck(4);
    
    std::cout<< " \n There are "<<deck.remaining()<<" cards remaining\n";
    return 0;
}
