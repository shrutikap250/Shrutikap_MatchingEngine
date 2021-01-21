#include "OrderBook.h"

//Checks if order book is empty
bool OrderBook::isEmpty() const{
    return Buys.empty() && Sells.empty();
}

//adds buy request into order book
void OrderBook::add_buys(char trader, char stock, int price) {
    add(trader, stock, price,true);
}

//adds sell request into order book
void OrderBook::add_sells(char trader, char stock, int price) {
    add(trader, stock, price, false);
}

//Order book entries
void OrderBook::add(char trader, char stock, int price, bool side) {


    if(side) {bid[stock] = price;Buys[trader] = bid;}
    else     {ask[stock] = price;Sells[trader] = ask;}
}

//Match Engine to find matched orders and send success status
bool OrderBook::matchEngine() {

    //iterations to check every Sell request against Buy request
    for(int i=0;i<=Buys.size();++i)
    {
       auto itrB = Buys.begin();
       auto itrS = Sells.begin();
       auto ptrS = itrS->second.begin();
       auto ptrB = itrB->second.begin();
       //Check if order against same stock
       if(ptrB->first == ptrS->first)
        {
           //check if order have exact same price
            if(ptrB->second == ptrS->second)
            {
                std::cout << "Hi " << itrS->first << " transaction is successful" << std::endl;
                std::cout << "Hi " << itrB->first << " transaction is successful" << std::endl;
                Sells.erase(itrS->first);
                Buys.erase(itrB->first);
            }
            //check for different price
            else if (ptrB->second > ptrS->second) {
                ptrB->second = ptrB->second - ptrS->second;
                std::cout << "Hi " << itrS->first << " transaction is successful" << std::endl;
                 Sells.erase(itrS->first);

            } else {
                ptrS->second = ptrS->second - ptrB->second;
                std::cout << "Hi " << itrB->first << " transaction is successful" << std::endl;
                Buys.erase(itrB->first);
            }

        }
        else
        {
            //moving to next order if stock name does not match
            if(itrS!=Sells.end()) itrS++;
            else  break;
        }
        //breaking loop if no sells order or no buys order
        if(Sells.size()== 0 || Buys.size() == 0)  break;

    }
    return 1;
}
