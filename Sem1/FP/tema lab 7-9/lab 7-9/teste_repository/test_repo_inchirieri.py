import unittest
from domain_problem.inchiriere import Inchiriere
from exceptions.exceptions import RentAlreadyExistsException,  RentDoesNotExistException
from repository.inchirieri_manager import RepoFileInchirieri
from utils.auxiliary import *

class TestRepoInchirieri(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        # method that unittest calls before running each test method in a test case class
        copy_file_content("inchirieri_default.txt","test_inchirieri.txt")
        self.test_file='test_inchirieri.txt'
        self.repo = RepoFileInchirieri(self.test_file)

    def test_load_from_file(self):
        """
        Functia testeaza daca datele au fost citite corect din fisier
        :param:-
        :return:-
        """
        inchirieri = self.repo.get_all()
        self.assertEqual(len(inchirieri), 5)
        self.assertEqual(inchirieri[0].get_id_client(), 1)
        self.assertEqual(inchirieri[0].get_id_film(), 1)
        self.assertEqual(inchirieri[1].get_id_client(), 1)
        self.assertEqual(inchirieri[1].get_id_film(), 2)
        self.assertEqual(inchirieri[2].get_id_client(), 1)
        self.assertEqual(inchirieri[2].get_id_film(), 3)
        self.assertEqual(inchirieri[3].get_id_client(), 2)
        self.assertEqual(inchirieri[3].get_id_film(), 3)
        self.assertEqual(inchirieri[4].get_id_client(), 2)
        self.assertEqual(inchirieri[4].get_id_film(), 1)

    def test_add_whitebox(self):
        """
        Testează logica internă a adăugării unei inchirieri, inclusiv salvarea în fișier.
        """
        new_rent = Inchiriere(4,5,True)
        self.repo.add(new_rent)
        inchirieri = self.repo.get_all()
        self.assertEqual(len(inchirieri), 6)
        self.assertEqual(inchirieri[5].get_id_client(), 4)
        self.assertEqual(inchirieri[5].get_id_film(), 5)

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 6)
        self.assertIn("4,5,True\n", lines)
        new_rent = Inchiriere(4,5,False)
        self.assertRaises(RentAlreadyExistsException,self.repo.add,new_rent)

    def test_remove_whitebox(self):
        """
        Testează logica internă a ștergerii unei inchirieri
        """
        self.repo.remove_inchiriere(1,2)

        # Verificăm starea internă
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 4)
        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 4)
        self.assertNotIn('1,2,True\n', lines)
        self.assertRaises(RentDoesNotExistException,self.repo.remove_inchiriere,1,2)

    def test_return(self):
        """
        Testeaza returnarea unui film
        :return:
        """
        new_rent = Inchiriere(1,3,True)
        self.repo.return_film(new_rent)
        inchirieri = self.repo.get_all()
        self.assertEqual(len(inchirieri), 5)
        l=-1
        for i in inchirieri:
            l+=1
            if i.get_id_client() == 1 and i.get_id_film() == 3:
                self.assertEqual(i.get_inchiriat(), False)
                break
        with open(self.test_file, "r") as file:
            lines = file.readlines()
            self.assertEqual('1,3,False\n', lines[l])
        self.assertRaises(RentDoesNotExistException,self.repo.return_film,Inchiriere(9,10,True))
        #self.assertRaises(RentReturnedException,self.repo.return_film,Inchiriere(1,3,True))

    def test_find_by_id_whitebox(self):
        """
        Testează logica internă a funcției find_by_id.
        """
        # Cazul 1: ID existent
        rent = self.repo.find_by_id(1,3)  # ID care există în fișier
        self.assertTrue(rent)
        rent = self.repo.find_by_id(2,10)
        self.assertFalse(rent)

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_filme.txt")


if __name__ == '__main__':
    unittest.main()