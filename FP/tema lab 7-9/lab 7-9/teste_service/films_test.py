import unittest
from domain_problem.films_data import Film
from domain_problem.film_validator import FilmValidator
from exceptions.exceptions import FilmDoesNotExistException,ValidationException
from repository.film_manager import RepoFileFilm
from service.service_film import ServiceFilm
from utils.auxiliary import clear_file_content, copy_file_content

class TestsFilmService(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        #method that unittest calls before running each test method in a test case class
        copy_file_content('filme_default.txt', 'test_filme.txt')
        film_repo = RepoFileFilm('test_filme.txt')
        film_validator=FilmValidator()
        self.service=ServiceFilm(film_validator,film_repo)

    def test_add_film(self):
        initial_size=len(self.service.get_all())
        self.service.add('It','abc','horror')
        self.assertEqual(len(self.service.get_all()),initial_size+1)
        self.assertRaises(ValidationException,self.service.add,'','abc','horror')
        self.assertRaises(ValidationException,self.service.add,'It','a','horror')
        self.assertRaises(ValidationException,self.service.add,'It','abc','r')

    def test_remove_film(self):
        initial_size=len(self.service.get_all())
        self.service.remove_film(2)
        self.assertEqual(len(self.service.get_all()),initial_size-1)
        self.assertRaises(FilmDoesNotExistException,self.service.remove_film,2)

    def test_replace_film(self):
        self.service.replace(2,'It','abc','horror')
        self.assertEqual(self.service.find_by_id(2),Film('It','abc','horror'))
        self.assertRaises(FilmDoesNotExistException,self.service.replace,999,'It','abc','horror')
        self.assertRaises(ValidationException,self.service.replace,2,'I','a','horror')

    def test_find_by_id(self):
        print(self.service.find_by_id(2))
        self.assertEqual(self.service.find_by_id(2),Film('The Shawshank Redemption','Prietenie intre doi detinuti intr-o inchisoare','Drama'))
        self.assertRaises(FilmDoesNotExistException,self.service.find_by_id,999)

    def test_filtrare(self):
        v=self.service.filtrare('Drama')
        self.assertEqual(len(v),4)
        v=self.service.filtrare('abcd')
        self.assertEqual(len(v), 0)

    def test_filtrare_recursiv(self):
        lst=None
        v=self.service.filtrare_recursiv('Drama',lst,0)
        self.assertEqual(len(v),4)
        lst=None
        v=self.service.filtrare_recursiv('abcd',lst,0)
        self.assertEqual(len(v),0)

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_filme.txt")

if __name__ == '__main__':
    unittest.main()