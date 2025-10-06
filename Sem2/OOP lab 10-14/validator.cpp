#include "validator.h"
#include <vector>
#include <stdexcept>
#include "exception.h"
#include <sstream>
using std::vector;

void Validator::valideaza(const string nume, const string tip, const string producator, const int pret)
{
	vector<string> errors;
	if (nume.length() < 1)
		errors.push_back("Denumirea trebuie sa aiba cel putin 1 caractere.");
	if (tip.length() < 1)
		errors.push_back("Tipul trebuie sa aiba cel putin 1 caractere.");
	if (producator.length() < 1)
		errors.push_back("Producatorul trebuie sa aiba cel putin 1 caractere.");
	if (pret < 1)
		errors.push_back("Pret invalid! Trebuie sa fie un intreg pozitiv");

	if (!errors.empty()) {
		std::stringstream msg;
		for (const auto& err : errors)
			msg << err << "\n";
		throw ValidatorException(msg.str());}}
