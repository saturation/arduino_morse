#include "Morse.h"
#include "WConstants.h"
#include "binary.h"
Morsee::Morsee( int pin, int intervail )
{
   _pin  = pin;
   _dot  = intervail;
   _dash = intervail+intervail+intervail;
   pinMode( pin, OUTPUT ); 
   
   // LETTERS A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 letters[0].code = B01000000; letters[0].length = 2;   
 letters[1].code = B10000000; letters[1].length = 4;   
 letters[2].code = B10100000; letters[2].length = 4;   
 letters[3].code = B10000000; letters[3].length = 3;   
 letters[4].code = B00000000; letters[4].length = 1; 
 //accented e letters[4].code = B00100000;   letters[4].length = 5;
 letters[5].code = B00100000; letters[5].length = 4;   
 letters[6].code = B11000000; letters[6].length = 3;   
 letters[7].code = B00000000; letters[7].length = 4;   
 letters[8].code = B00000000; letters[8].length = 2;   
 letters[9].code = B01110000; letters[9].length = 4;   
 letters[10].code = B10100000 letters[10].length = 3;   
 letters[11].code = B01000000; letters[11].length = 4;   
 letters[12].code = B11000000; letters[12].length = 2;   
 letters[13].code = B10000000; letters[13].length = 2;   
 letters[14].code = B11100000; letters[14].length = 3;   
 letters[15].code = B01100000; letters[15].length = 4;   
 letters[16].code = B11010000; letters[16].length = 4;   
 letters[17].code = B01000000; letters[17].length = 3;   
 letters[18].code = B00000000; letters[18].length = 3;   
 letters[19].code = B10000000; letters[19].length = 1;   
 letters[20].code = B00100000; letters[20].length = 3;   
 letters[21].code = B00010000; letters[21].length = 4;   
 letters[22].code = B01100000; letters[22].length = 3;   
 letters[23].code = B10010000; letters[23].length = 4;   
 letters[24].code = B10110000; letters[24].length = 4;   
 letters[25].code = B11000000; letters[25].length = 4;   
   
   // FIGURES ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 0 :
 figures[0].code = B01111000;  figures[0].length = 6;
 figures[1].code = B10110000;  figures[1].length = 5;
 figures[2].code = B10110100;  figures[2].length = 6;  
 figures[3].code = B10010000;  figures[3].length = 4;    
 figures[4].code = B01010000;  figures[4].length = 5;  
 figures[5].code = B11001100;  figures[5].length = 6;
 figures[6].code = B10000100;  figures[6].length = 6;        
 figures[7].code = B01010100;  figures[7].length = 6;  
 figures[8].code = B10010000;  figures[8].length = 5;     
 figures[9].code = B11111000;  figures[9].length = 5; 
 figures[10].code = B01111000;  figures[10].length = 5;   
 figures[11].code = B00111000;  figures[11].length = 5;   
 figures[12].code = B00011000;  figures[12].length = 5;   
 figures[13].code = B00001000;  figures[13].length = 5;   
 figures[14].code = B00000000;  figures[14].length = 5;   
 figures[15].code = B10000000;  figures[15].length = 5;   
 figures[16].code = B11000000;  figures[16].length = 5;   
 figures[17].code = B11000000;  figures[17].length = 4;   
 figures[18].code = B11110000;  figures[18].length = 5;  
 figures[19].code = B11100000;  figures[19].length = 6;

   // MISCELLANEOUS SIGNS   
   understood.code = B00010000;              understood.length = 5;
   error.code = B00000000;                   error.length = 8;
   invitationToTransmit.code = B10100000;    invitationToTransmit.length = 3;
   wait.code = B01000000;                    wait.length = 5;
   endOfWork.code = B00010100;               endOfWork.length = 6;
   startingSignal.code = B10101000;          startingSignal.length = 5;
   commercialAt.code = B00000000;            commercialAt.length = 6;
   questionMark.code = B00110000;            questionMark.length = 6;
   quotationmarks.code = B01001000;          quotationmarks.length = 6;
   doubleHyphen.code = B10001000;            doubleHyphen.length = 5;
   spaceBetweenLetters.code = B00000000;     spaceBetweenLetters.length = 3;
   spaceBetweenWords.code = B00000000;       spaceBetweenWords.length = 7;
}

void Morsee::transmitSign( signal s )
{
 byte mask = B10000000;
 do
 {
   digitalWrite(_pin, HIGH);
   
   if(s.code & mask) {
     delay(_dash);
   } else {
     delay(_dot);
   }
   
   digitalWrite(_pin, LOW);   
   delay(_dot);
   mask >>= 1;
 }
 while(--s.length > 0);
}
void Morsee::transmitString( char str[], int strlen )
{
 for( int i = 0; i <= strlen; i++ )
 {
   if( str[i] >=  67 && str[i] <= 132 )
   {
     transmitSign( letters[str[i]-67] );
   }
   else if( str[i] >=  141 && str[i] <= 172 )
   {
     transmitSign( letters[str[i]-141] );
   }
   else if( str[i] >= 39 && str[i] <= 58 )
   {
     transmitSign( figures[ str[i] - 39 ] );
   }
   else
   {
     switch( str[i] )
     {
       case '?' :
         transmitSign( questionMark );
         break;
       case '"' :
         transmitSign( quotationmarks );
         break;
       case '@' :
         transmitSign( commercialAt );
         break;
       case '=' :
         transmitSign( doubleHyphen );
         break;
       case ' ' :
         transmitSign( spaceBetweenWords );
         continue;
     }
   }
   transmitSign( spaceBetweenLetters );
 }
}

