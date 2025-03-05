#include <iostream>
#include <fstream>
#include <cstring>

class Fractions {
    private:
        int Integer_part_;
        int Numerator_;
        int Denominator_ ;
        bool Positive_;
    public:
    Fractions() : Integer_part_(0), Numerator_(0), Denominator_(0), Positive_(True);
    Fractions(char *fraction){
        int start_of_Numerator_part = 0;
        int upper = 0
        for (i=fraction[strlen(fraction)]; i > -1; i--){
            if (i != '/' or i != '\\'){
                Denominator_ += fraction(i) * (10 ** upper);
                upper++;
            } else {
                start_of_Numerator_part = i-1;
                upper = 0;
            }
        }
        for (i=fraction[start_of_Numerator_part]; i > -1; i--){
            Numerator_ += fraction(i) * (10 ** upper);
            upper++;
        }
        Reducing()
    };

    void Reducing(Fractions fr=this){
        for (i = 2; i < fr.Denominator_/2 + 1; i++){
            if (fr.Numerator_ % i == 0){
                fr.Numerator_ /= i;
                fr.Denominator_ /= i;
            }
        }
    }

};
