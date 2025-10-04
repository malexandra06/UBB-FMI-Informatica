import unittest

from domain_problem.inchiriere_validator import InchiriereValidator
from exceptions.exceptions import RentDoesNotExistException,ValidationException
from repository.film_manager import RepoFileFilm
from repository.client_manager import RepoFileClient
from repository.inchirieri_manager import RepoFileInchirieri
from service.service_inchirieri import ServiceInchirieri
from utils.auxiliary import clear_file_content, copy_file_content

class TestsRatingService(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        #method that unittest calls before running each test method in a test case class
        copy_file_content('filme_default.txt', 'test_filme.txt')
        film_repo = RepoFileFilm('test_filme.txt')

        copy_file_content('clienti_default.txt', 'test_clienti.txt')
        client_repo = RepoFileClient('test_clienti.txt')

        copy_file_content('inchirieri_default.txt', 'test_inchirieri.txt')
        rent_repo = RepoFileInchirieri("test_inchirieri.txt")
        rent_validator = InchiriereValidator()
        self.rent_service = ServiceInchirieri(rent_repo,film_repo, client_repo, rent_validator)

    def test_add_inchiriere(self):
        initial_size = len(self.rent_service.get_all())
        self.rent_service.add(5,7,'True')
        self.assertEqual(len(self.rent_service.get_all()), initial_size + 1)

        self.assertRaises(ValidationException, self.rent_service.add, 5,7,'True')
        self.assertRaises(ValidationException, self.rent_service.add, 99,1,'False')
        self.assertRaises(ValidationException, self.rent_service.add, 1, 99,'True')
        self.assertRaises(ValidationException, self.rent_service.add, 5, 6, 'ABCD')

    def test_remove_inchiriere(self):
        initial_size = len(self.rent_service.get_all())
        self.rent_service.remove_inchiriere(5,9)
        self.assertEqual(len(self.rent_service.get_all()), initial_size - 1)

    def test_return_film(self):
        self.rent_service.return_film(1,5)
        for i in self.rent_service.get_all():
            if i.get_id_client==1 and i.get_id_film==5:
                self.assertEqual(i.get_inchiriat(), False)
        self.assertRaises(RentDoesNotExistException, self.rent_service.return_film, 1,20)

    def test_find_by_id(self):
        self.assertTrue(self.rent_service.find_by_id(1,2))
        self.assertFalse(self.rent_service.find_by_id(2,20))

    def test_cele_mai_inchiriate_filme(self):
        dto_list = self.rent_service.cele_mai_inchiriate_filme()
        self.assertEqual(len(dto_list), 10)

        dto1 = dto_list[0]
        self.assertEqual(dto1.get_title(), "The Shawshank Redemption")
        self.assertEqual(dto1.get_nr(),5)

        dto1 = dto_list[1]
        self.assertEqual(dto1.get_title(), "La La Land")
        self.assertEqual(dto1.get_nr(), 4)

        dto1 = dto_list[2]
        self.assertEqual(dto1.get_title(), "Inception")
        self.assertEqual(dto1.get_nr(), 3)

    def test_clienti_inchirieri(self):
        dto_list=self.rent_service.clienti_inchirieri()
        self.assertEqual(len(dto_list), 9)
        dto1 = dto_list[0]
        self.assertEqual(dto1.get_name(),'Popescu Andrei')
        self.assertEqual(dto1.get_nr(),5)
        dto1 = dto_list[1]
        self.assertEqual(dto1.get_name(),'Dumitrescu Ionel')
        self.assertEqual(dto1.get_nr(),3)
        dto1 = dto_list[2]
        self.assertEqual(dto1.get_name(),'Marin Vasile')
        self.assertEqual(dto1.get_nr(),3)

    def test_top_30(self):
        dto_list=self.rent_service.top_30()
        self.assertEqual(len(dto_list), 2)
        self.assertEqual(dto_list[0].get_name(),'Popescu Andrei')
        self.assertEqual(dto_list[0].get_nr(),5)
        self.assertEqual(dto_list[1].get_name(),'Dumitrescu Ionel')
        self.assertEqual(dto_list[1].get_nr(),3)

    def test_top_5_gen(self):
        dto_list=self.rent_service.top_5_gen()
        self.assertEqual(len(dto_list), 5)
        self.assertEqual(dto_list[0].get_gen(),'Drama')
        self.assertEqual(dto_list[0].get_nr(),12)
        self.assertEqual(dto_list[1].get_gen(),'SF')
        self.assertEqual(dto_list[1].get_nr(),5)
        self.assertEqual(dto_list[2].get_gen(),'Romantic')
        self.assertEqual(dto_list[2].get_nr(),4)
        self.assertEqual(dto_list[3].get_gen(),'Aventura')
        self.assertEqual(dto_list[3].get_nr(),2)
        self.assertEqual(dto_list[4].get_gen(),'Actiune')
        self.assertEqual(dto_list[4].get_nr(),1)

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_clienti.txt")
        clear_file_content("test_filme.txt")
        clear_file_content("test_inchirieri.txt")

if __name__ == '__main__':
    unittest.main()