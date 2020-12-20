#ifndef _TASCHENRECHNER_H_
#define _TASCHENRECHNER_H_

#include <string>
#include <sstream>

class Taschenrechner
{
  public:
    Taschenrechner(std::string anfrage);
    
    std::string getAnfrage();
    long getErgebnis();
    
  private:
    char peekZeichen();
    char leseZeichen();
    
    long leseZahl();
    long leseFaktor();
    long leseSummand();
    long leseAusdruck();
    
  private:
    std::string _anfrage;
    std::istringstream _stream;
};

#endif // _TASCHENRECHNER_H_