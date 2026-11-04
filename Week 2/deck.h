//
//  deck.h
//  Deck_of_cards_objects
//
//  Created by Senir Dinar on 20/09/2022.
//

#ifndef deck_h
#define deck_h


#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

//memory saving measures
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;




const std::string suitstr = "_CDHS";//Clubs, Diamond, Heart and Spade. Const as will never change
const std::string facecards = "ATJQK";//Ace, Ten, Jack, Queen, King. Const as will never change.
constexpr uint8 default_deck = 52; // Every deck of cards must include 52 cards
constexpr uint8 max_decks = 10; // on start, the programmer can initiate a maximum of 10 packs in a deck
constexpr uint8 suitcount = 4; //There are 4 possible suit
constexpr uint8 rankcount = 13; // there are 13 different ranking in a deck 2 to 10 +jack, Queen, king and Ace

// what are constexpr:
//  Cannot change at run time
//  Evaluate expression at Compile time
//  Easier to maintain

/*
 Both constexpr and const are constants, and you cannot* modify them.
 only constexpr is a compile-time constant. It will be initialized at compile time.
 const may be initialized at compile time or run time.
 only constexpr can be used in a context that requires a compile-time constant.
 */


//A card is made up of a rank of a particular suite.
typedef struct {
    uint8 suit : 4;
    uint8 rank : 4;
} Card;

class Deck
{
private:
    
    uint8 cardsPerDeck = 0;
    uint8 numDecks = 0;
    uint16 remainingCardCount = 0;
    std::vector<Card> deck;
public:
    //used unsigned casting as otherwise it'll assign the ascii value of 52, which is four
    Deck() : cardsPerDeck((unsigned) default_deck), numDecks(1)
    {
        init();
    }
    Deck(uint8 n) : cardsPerDeck((unsigned)default_deck), numDecks(n)
    {
        init();
    }
    void init()
    {
        srand((unsigned) time(nullptr));  // seed rand for later
        rand();     // this helps on some systems (MSVC)
        create_deck();
        shuffle_deck();

    }
    
    
    void create_deck()
    {
        if(numDecks > max_decks)
            std::cout<<"\n Too many decks (max 10)";
        else
        {
            if(deck.size()>0)
                delete_deck();
            remainingCardCount = numDecks * cardsPerDeck;
            for(uint8 n_deck = 0; n_deck < numDecks; ++n_deck)
            {
                for(uint8 n_suit = 1; n_suit <= suitcount; ++n_suit)
                {
                    for(uint8 n_rank = 1; n_rank <= rankcount; ++n_rank)
                    {
                        Card temp = {n_suit,n_rank};
                        deck.push_back(temp);
                    }
                }
            }
            
        }

    }
    
    void delete_deck()
    {
        if(deck.size()>0)
           deck.empty();
    }
    
        
    void shuffle_deck() {
        uint16 ncards = remaining();
        
        // The code in this section has been deleted
        // how would you go about shuffling a deck of cards. 
        // ncards is the value of cards you need to shuffle
        
    }
    
    uint16 remaining() const {
        return remainingCardCount;
    }

    void new_deck() {
        create_deck();
        shuffle_deck();
    }

    void new_deck(uint8 n) {
        numDecks = n;
        create_deck();
        shuffle_deck();
    }
    
    const Card & get_card(uint16 index) const {
        if(index >= remainingCardCount)
            std::cout<<"\n Deck: card out of range";
        return deck[index];
    }

    const Card deal_card() {
        if(remainingCardCount == 0)
        {
            std::cout<<" \n Deck: cannot deal from empty deck";
            Card temp={0,0};
            return temp;
        }
        else
        {
            Card temp = deck[deck.size()-1];
            deck.erase(deck.begin()+deck.size()-1);
            remainingCardCount=deck.size();
            return temp;
        }
    }
    const std::vector<Card> deal_hand(uint8 n)
    {
        std::vector<Card> temp;
        if(remainingCardCount < n)
        {
            std::cout<<" \n Deck: cannot deal these many cards";
            
            return temp;
        }
        else
        {
           
            for(int i=0;i<n;++i)
            {
                Card tempCard = deck[deck.size()-1];
                deck.erase(deck.begin()+deck.size()-1);
                temp.push_back(tempCard);
            }
            remainingCardCount=deck.size();
            return temp;
        }
    }
    
};
std::ostream& operator<<(std::ostream & o,const Card & c)
{
  
    char rank ='x';
    if(c.rank == 1)
    {
        rank=facecards[0];// It's ACE =  "ATJQK"
    }
    else if (c.rank > 9)
    {
        rank = facecards[c.rank-9];
    }
    else
    {
        rank=(unsigned)c.rank+48;
    }
    
    o<<"\n"<<std::string()<<rank<<suitstr[c.suit];//+suitstr[c.suit];
    return o;
}
bool operator==(Card a , Card b)
{
    return (a.rank == b.rank && a.suit == b.suit );
}

#endif /* deck_h */


