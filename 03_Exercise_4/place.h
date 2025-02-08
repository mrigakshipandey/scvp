#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
class placeInterface: public sc_interface
{
    public:
    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;

};

// Place Channel:
// TODO
class place: public placeInterface
{
    private:
    unsigned int tokens;

    public:
    place(unsigned int t){
        tokens = t;
    }

    virtual void addTokens(unsigned int n) {
        tokens += n;
    }

    virtual void removeTokens(unsigned int n) {
        tokens -= n;
    }

    virtual unsigned int testTokens() {
        return tokens;
    }
};

#endif // PLACE_H
