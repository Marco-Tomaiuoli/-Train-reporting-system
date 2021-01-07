//Studente: Trevisiol Riccardo 1216353


#ifndef LOCALE_H
#define LOCALE_H
#include "Principale.h"
#include <string>
class Locale : public Principale
{
public:
	Locale(std::string, int);
	int is_arriving(bool, int) override;
private:
	int fast_platform_gone;
	int fast_platform_back;
};
#endif