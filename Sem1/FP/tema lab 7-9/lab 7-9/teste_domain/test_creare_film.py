import unittest

from exceptions.exceptions import ValidationException
from domain_problem.film_validator import FilmValidator
from domain_problem.films_data import Film

class TestDomainFilm(unittest.TestCase):
    def setUp(self):
        pass

    def test_create_film(self):
        """
        Functia testeaza daca obiectul de tip Film s-a creat cu succes precum si metodele sale
        :param:-
        :return:-
        """
        film_test=Film('TestTitle','TestDescription','TestGenre')
        self.assertEqual(film_test.get_title(), 'TestTitle')
        self.assertEqual(film_test.get_description(), 'TestDescription')
        self.assertEqual(film_test.get_genre(), 'TestGenre')
        film_test.set_title('TestTitle2')
        self.assertEqual(film_test.get_title(), 'TestTitle2')
        film_test.set_description('TestDescription2')
        self.assertEqual(film_test.get_description(), 'TestDescription2')
        film_test.set_type('TestGenre2')
        self.assertEqual(film_test.get_genre(), 'TestGenre2')

    def test_validate_film(self):
        """
        Functia testeaza functia de validare a datelor transmise pentru crearea unui film
        :param:-
        :return:-
        """
        #Titlul trebuie sa aiba cel putin un caracter
        film_test1=Film('','TestDescription','TestGenre')
        validator_film=FilmValidator()
        self.assertRaises(ValidationException)
        #Descrierea trebuie sa aiba cel putin 2 caractere
        film_test2=Film('TestTitle','T','TestGenre')
        validator_film2=FilmValidator()
        self.assertRaises(ValidationException)
        #Genul trebuie sa aiba cel putin 2 caractere
        film_test3=Film('TestTitle','TestTitle','T')
        validator_film3 = FilmValidator()
        self.assertRaises(ValidationException)

    def test_eq(self):
        """
        Functia testeaza metoda __eq__ din clasa Film
        :param:-
        :return:-
        """
        film_test1=Film('TestTitle','TestDescription','TestGenre')
        film_test2=Film('TestTitle','TestDescription','TestGenre')
        self.assertEqual(film_test1,film_test2)
        film_test3=Film('TestTitle','TestTitle','T3')
        self.assertNotEqual(film_test1,film_test3)

    def tearDown(self):
        pass

if __name__ == '__main__':
    unittest.main()