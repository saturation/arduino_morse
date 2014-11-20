#ifndef Morsee_h
#define Morsee_h

#include "WConstants.h"
#include "binary.h"

typedef struct {
   byte code;    
   byte length;    
 } signal;


class Morsee {
 public:
   Morsee( int pin, int intervail );
   void transmitSign( signal sig );
   void transmitString( char str[], int strlen );
   
   signal letters[26],
          figures[20], 
          spaceBetweenWords, 
          spaceBetweenLetters,
          doubleHyphen,   
          quotationmarks,
          questionMark, 
          commercialAt,    
          startingSignal,  
          endOfWork,   
          wait,         
          invitationToTransmit,             
          error,
          understood;  
          
 private:
    int  _pin;
    int  _dash;
    int  _dot;
};

#endif
