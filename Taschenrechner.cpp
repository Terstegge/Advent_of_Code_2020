#include "Taschenrechner.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

//Taschenrechner::Taschenrechner() { }

Taschenrechner::Taschenrechner(std::string anfrage)
: _anfrage(anfrage), _stream(anfrage){ }

std::string Taschenrechner::getAnfrage() {
  return _anfrage;
}

long Taschenrechner::getErgebnis() {
  return leseAusdruck();
}

// Elementare Funktionen zum Lesen eines einzelnen Zeichens.
char Taschenrechner::peekZeichen() {
  char c;
  while (isblank(_stream.peek())) {
    _stream >> std::noskipws >> c;
  }
  return _stream.peek();
}

char Taschenrechner::leseZeichen()
{
  char c;
  peekZeichen(); // ueberspringe Leerzeichen...
  _stream.get(c);
  return c;
}

long Taschenrechner::leseZahl() {
  long z = 0;
  if (isdigit(peekZeichen())) {
    while (isdigit(peekZeichen())) {
      z *= 10;
      z += leseZeichen() - '0';
    }
  }
  else {
    std::cerr << "FEHLER: Zahl beginnt mit '"
	          << peekZeichen() << "'!" << std::endl;
    exit(1);
  }
  return z;
}

long Taschenrechner::leseFaktor() {
  char c = peekZeichen();
  switch (c) {
    case '+': { leseZeichen(); return  leseFaktor(); }
    case '-': { leseZeichen(); return -leseFaktor(); }
    case '(': { leseZeichen();
      long z = leseAusdruck();
      c = leseZeichen();
      if (c != ')') {
    	  std::cerr << "FEHLER: ')' erwartet!" << std::endl;
    	  exit(1);
      }
      return z;
    }
  }
  return leseZahl();
}

long Taschenrechner::leseSummand()
{
  long  z = leseFaktor();
  char c = peekZeichen();
  if (c == '+') { leseZeichen(); z +=leseSummand();  }
  if (c == '-') { leseZeichen(); z -= leseSummand(); }
  return z;
}

long Taschenrechner::leseAusdruck()
{
  long erg = leseSummand();
  while(true) {
	  char c = peekZeichen();
  	  if (c == '*') { leseZeichen(); erg *= leseSummand(); }
  	  else
  		  if (c == '/') { leseZeichen(); erg /= leseSummand(); }
  	  	  else
  	  		  break;
  }
  return erg;
}

