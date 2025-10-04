from domain_problem.films_data import Film
from exceptions.exceptions import ValidationException

class FilmValidator:
    """
    Clasa care verifica daca datele introduse pentru a forma un obiect de tip Film sunt valide
    """
    def validate(self, film: Film):
        errors=[]
        if len(film.get_title())<1:
            errors.append("Titlul filmului trebuie sa aiba cel putin un caracter!")
        if len(film.get_genre())<2:
            errors.append("Tipul filmului trebuie sa aiba cel putin 2 caractere!")
        if len(film.get_description())<2:
            errors.append("Descrierea filmului trebuie sa aiba cel putin 2 caractere!")
        if len(errors) > 0:
            error_message = '\n'.join(errors)
            raise ValidationException(error_message)