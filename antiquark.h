#ifndef ANTIQUARK
#define ANTIQUARK 

class Antiquark
{
    public:
        Antiquark(char flavor, char color);
        char getFlavor(){ return this->flavor; };
        char getColor(){ return this->color; };
        double getCharge(){ return this->charge; };
        void info();
    private:
        char flavor;
        char color;
        double charge;
};

#endif /* ifndef ANTIQUARK */
