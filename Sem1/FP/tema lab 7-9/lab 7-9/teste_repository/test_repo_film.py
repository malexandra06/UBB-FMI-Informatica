import unittest

from exceptions.exceptions import ValidationException, FilmDoesNotExistException
from repository.film_manager import RepoFileFilm
from domain_problem.film_validator import FilmValidator
from domain_problem.films_data import Film
from utils.auxiliary import *

class TestRepoFilm(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        # method that unittest calls before running each test method in a test case class
        copy_file_content("filme_default.txt","test_filme.txt")
        self.test_file='test_filme.txt'
        self.repo = RepoFileFilm(self.test_file)


    def test_load_from_file_film_whitebox(self):
        """
        Functia testeaza daca datele au fost citite corect din fisier
        :param:-
        :return:-
        """
        films=self.repo.get_all()
        self.assertEqual(len(films), 3)
        self.assertEqual(films[0].get_title(), 'Titanic')
        self.assertEqual(films[0].get_description(), 'O poveste tragica de dragoste')
        self.assertEqual(films[0].get_genre(), 'Romance')

    def test_load_from_file_film_blackbox(self):
        """
        Testează încărcarea datelor din fișier pe principiul blackbox.
        """
        # Pregătește fișierul cu date cunoscute
        with open(self.test_file, 'w') as file:
            file.write("Titanic;O poveste tragica de dragoste;Romance\n")
            file.write("Avatar;A visually stunning movie;Sci-Fi\n")
            file.write("Inception;Un vis in alt vis;Thriller\n")

        # Creează repository-ul și apelează constructorul care citește fișierul
        repo = RepoFileFilm(self.test_file)

        # Obține lista de filme
        films = repo.get_all()

        # Verifică numărul de filme
        self.assertEqual(len(films), 3)

        # Verifică titlurile și genurile
        film_titles = [film.get_title() for film in films]
        film_genres = [film.get_genre() for film in films]

        self.assertIn("Titanic", film_titles)
        self.assertIn("Avatar", film_titles)
        self.assertIn("Inception", film_titles)
        self.assertIn("Romance", film_genres)
        self.assertIn("Sci-Fi", film_genres)
        self.assertIn("Thriller", film_genres)

    def test_add_whitebox(self):
        """
        Testează logica internă a adăugării unui film, inclusiv salvarea în fișier.
        """
        new_film = Film("Interstellar", "O calatorie prin spatiu si timp", "Sci-Fi")
        self.repo.add(new_film)

        # Verificăm starea internă (lista)
        films = self.repo.get_all()
        self.assertEqual(len(films), 4)
        self.assertEqual(films[3].get_title(), "Interstellar")
        self.assertEqual(films[3].get_id(),4)
        self.assertEqual(self.repo.id_counter,5)

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 4)
        self.assertIn("Interstellar;O calatorie prin spatiu si timp;Sci-Fi\n", lines)

    def test_add_blackbox(self):
        """
        Testează comportamentul extern al funcției add.
        """
        new_film = Film("Interstellar", "O calatorie prin spatiu si timp", "Sci-Fi")
        self.repo.add(new_film)

        # Verificăm rezultatul extern (lista)
        films = self.repo.get_all()
        self.assertEqual(len(films), 4)
        self.assertEqual(films[3].get_title(), "Interstellar")

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 4)

    def test_remove_whitebox(self):
        """
        Testează logica internă a ștergerii unui film.
        """
        self.repo.remove_film(1)  # Șterge filmul Titanic

        # Verificăm starea internă
        films = self.repo.get_all()
        self.assertEqual(len(films), 2)
        self.assertNotEqual(films[0].get_title(), "Titanic")

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 2)
        self.assertNotIn("Titanic;O poveste tragica de dragoste;Romance\n", lines)
        self.assertRaises(FilmDoesNotExistException, self.repo.remove_film,1)

    def test_remove_blackbox(self):
        """
        Testează comportamentul extern al funcției remove_film.
        """
        # Se șterge filmul Titanic
        self.repo.remove_film(1)
        films=self.repo.get_all()
        self.assertNotIn("Titanic", [film.get_title() for film in films])  # Titanic nu trebuie să fie în listă
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        # Verificăm că filmul Titanic nu mai este prezent în fișier
        self.assertNotIn("Titanic;O poveste tragica de dragoste;Romance\n",
                         lines)  # Titanic nu trebuie să mai fie în fișier

    def test_replace_film_whitebox(self):
        """
        Testeaza inlocuirea unui film si salvare in fisier
        """
        new_film=Film("Avatar", "A visually stunning movie", "Sci-Fi")
        self.repo.replace(2,new_film)
        films = self.repo.get_all()
        self.assertEqual(len(films), 3)
        self.assertNotEqual(films[1], Film('Iubiri la Apus',' Doi necunoscuti descopera dragostea într-un oras pitoresc','romantic'))
        self.assertEqual(films[1], Film("Avatar", "A visually stunning movie", "Sci-Fi"))
        with open(self.test_file, "r") as file:
            lines = file.readlines()
            self.assertEqual("Avatar;A visually stunning movie;Sci-Fi\n",lines[1])

    def test_replace_blackbox(self):
        """
        Testează comportamentul extern al funcției replace.
        """
        new_film = Film("Avatar", "A visually stunning movie", "Sci-Fi")
        self.repo.replace(2, new_film)  # Înlocuim filmul cu id-ul 2

        # Verificăm lista de filme
        films = self.repo.get_all()
        self.assertEqual(films[1].get_title(), "Avatar")  # Verificăm că filmul a fost înlocuit corect
        self.assertEqual(films[1].get_id(),2)
        self.assertEqual(films[1].get_genre(), "Sci-Fi")
        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertIn("Avatar", [line.split(';')[0] for line in lines])  # Avatar trebuie să fie în fișier

    def test_find_by_id_whitebox(self):
        """
        Testeaza functia de cautare
        """
        film_cautat=self.repo.find_by_id(1)
        self.assertEqual(film_cautat.get_title(), "Titanic")
        self.assertEqual(film_cautat.get_genre(), "Romance")
        self.assertRaises(FilmDoesNotExistException, self.repo.find_by_id,5)

    def test_find_by_id_blackbox(self):
        """
        Testeaza functia de cautare
        """
        self.assertIsNotNone(self.repo.find_by_id(1))
        self.assertRaises(FilmDoesNotExistException,self.repo.find_by_id,999)

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_filme.txt")


if __name__ == '__main__':
    unittest.main()