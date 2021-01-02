#ifndef LOCALE_H
#define LOCALE_H
#include "Principale.h"
#include <string>
class Locale : public Principale
{
public:
	Locale(std::string, int);
	bool is_arriving(bool, int);
private:
	int fast_platform_gone;
	int fast_platform_back;
};
#endif