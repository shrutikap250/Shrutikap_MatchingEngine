#ifndef MATCHINGENGINE_ORDERBOOK_H
#define MATCHINGENGINE_ORDERBOOK_H

#include<map>
#include<iostream>


class optional;

class OrderBook {
    std::map<char,int> bid,ask;
    std::map<char, std::map<char,int>>  Buys, Sells;
    void add(char trader, char stock, int price, bool side);

public:

    bool isEmpty() const;
    void add_buys(char trader, char stock, int price);
    void add_sells(char trader, char stock, int price);
    bool matchEngine();
};


#endif //MATCHINGENGINE_ORDERBOOK_H
