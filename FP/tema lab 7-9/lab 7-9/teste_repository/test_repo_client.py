import unittest
from domain_problem.clients import Client
from repository.client_manager import RepoFileClient
from exceptions.exceptions import PersonAlreadyExistsException,  PersonDoesNotExistException
from sortari.sortari import insertion_sort, comb_sort
from utils.auxiliary import *

class TestRepoClient(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        # method that unittest calls before running each test method in a test case class
        copy_file_content("clienti_default.txt","test_clienti.txt")
        self.test_file='test_clienti.txt'
        self.repo = RepoFileClient(self.test_file)

    def test_load_from_file_film_whitebox(self):
        """
        Functia testeaza daca datele au fost citite corect din fisier
        :param:-
        :return:-
        """
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 3)
        self.assertEqual(clients[0].get_name(), 'Popescu Andrei')
        self.assertEqual(clients[0].get_cnp(), '1980101123456')
        self.assertEqual(clients[1].get_name(), 'Dumitrescu Ionel')
        self.assertEqual(clients[1].get_cnp(), '1790604123456')
        self.assertEqual(clients[2].get_name(), 'Marin Vasile')
        self.assertEqual(clients[2].get_cnp(), '1800301123456')

    def test_add_whitebox(self):
        """
        Testează logica internă a adăugării unui film, inclusiv salvarea în fișier.
        """
        new_client = Client("Pop Maria", "5678902345678")
        self.repo.add(new_client)

        # Verificăm starea internă (lista)
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 4)
        self.assertEqual(clients[3].get_name(), "Pop Maria")
        self.assertEqual(clients[3].get_cnp(),'5678902345678')

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 4)
        self.assertIn("Pop Maria; 5678902345678\n", lines)
        self.assertEqual(clients[3].get_id(),4)
        self.assertEqual(self.repo.id_counter,5)
        new_client = Client("Pop Georgeta", "5678902345678")
        self.assertRaises(PersonAlreadyExistsException,self.repo.add,new_client)

    def test_remove_whitebox(self):
        """
        Testează logica internă a ștergerii unui film.
        """
        self.repo.remove_client(1)

        # Verificăm starea internă
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 2)
        self.assertNotEqual(clients[0].get_name(), "Popescu Andrei")

        # Verificăm fișierul
        with open(self.test_file, "r") as file:
            lines = file.readlines()
        self.assertEqual(len(lines), 2)
        self.assertNotIn("Popescu Andrei; 1980101123456\n", lines)
        self.assertRaises(PersonDoesNotExistException,self.repo.remove_client,1)

    def test_replace_client(self):
        """
        Testeaza inlocuirea unui film si salvare in fisier
        """
        new_client=Client('Pop Maria', '4563457892345')
        self.repo.replace(2,new_client)
        clients = self.repo.get_all()
        self.assertEqual(len(clients), 3)
        self.assertNotEqual(clients[1], Client('Dumitrescu Ionel', '1790604123456'))
        self.assertEqual(clients[1], Client('Pop Maria', '4563457892345'))
        with open(self.test_file, "r") as file:
            lines = file.readlines()
            self.assertEqual("Pop Maria; 4563457892345\n",lines[1])
        new_client.set_name('Miron Irina')
        self.assertRaises(PersonAlreadyExistsException,self.repo.replace,1,new_client)
        self.assertRaises(PersonDoesNotExistException,self.repo.replace,7,new_client)

    def test_cnp_exist(self):
        """
        Testează logica internă a funcției cnp_exist.
        """
        # Cazul 1: CNP existent
        client = self.repo.cnp_exist("1980101123456")  # CNP care există în fișier
        self.assertIsNotNone(client)
        self.assertEqual(client.get_name(), "Popescu Andrei")
        self.assertEqual(client.get_cnp(), "1980101123456")

        # Cazul 2: CNP inexistent
        client = self.repo.cnp_exist("9999999999999")  # CNP care nu există în fișier
        self.assertIsNone(client)

    def test_find_by_id_whitebox(self):
        """
        Testează logica internă a funcției find_by_id.
        """
        # Cazul 1: ID existent
        client = self.repo.find_by_id(1)  # ID care există în fișier
        self.assertEqual(client.get_name(), "Popescu Andrei")
        self.assertEqual(client.get_cnp(), "1980101123456")

        # Cazul 2: ID inexistent
        with self.assertRaises(PersonDoesNotExistException):
            self.repo.find_by_id(999)  # ID care nu există în fișier

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_filme.txt")

    def test_insertion_sort(self):
        lst=self.repo.get_all()
        insertion_sort(lst, lambda x: x.get_name())
        self.assertEqual(lst, [Client('Dumitrescu Ionel','1790604123456'),Client('Marin Vasile','1800301123456'),Client('Popescu Andrei','1980101123456')])
        insertion_sort(lst, lambda x: x.get_name(), reverse=True)
        self.assertEqual(lst, [Client('Popescu Andrei','1980101123456'),Client('Marin Vasile','1800301123456'),Client('Dumitrescu Ionel','1790604123456')])
        lst=[8,3,5,7,1,8,2]
        insertion_sort(lst)
        self.assertEqual(lst,[1,2,3,5,7,8,8])
        lst=[7,4,6,9,2,1,5,7]
        insertion_sort(lst,reverse=True)
        self.assertEqual(lst,[9,7,7,6,5,4,2,1])

    def test_comb_sort(self):
        lst = self.repo.get_all()
        comb_sort(lst, lambda x: x.get_name())
        self.assertEqual(lst, [Client('Dumitrescu Ionel', '1790604123456'), Client('Marin Vasile', '1800301123456'),
                               Client('Popescu Andrei', '1980101123456')])
        comb_sort(lst, lambda x: x.get_name(), reverse=True)
        self.assertEqual(lst, [Client('Popescu Andrei', '1980101123456'), Client('Marin Vasile', '1800301123456'),
                               Client('Dumitrescu Ionel', '1790604123456')])
        lst = [8, 3, 5, 7, 1, 8, 2]
        comb_sort(lst)
        self.assertEqual(lst, [1, 2, 3, 5, 7, 8, 8])
        lst = [7, 4, 6, 9, 2, 1, 5, 7]
        comb_sort(lst, reverse=True)
        self.assertEqual(lst, [9, 7, 7, 6, 5, 4, 2, 1])

if __name__ == '__main__':
    unittest.main()