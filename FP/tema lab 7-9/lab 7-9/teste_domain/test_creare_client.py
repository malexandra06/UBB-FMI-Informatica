import unittest

from exceptions.exceptions import ValidationException
from domain_problem.client_validator import ClientValidator
from domain_problem.clients import Client


class TestDomainFilm(unittest.TestCase):
    def setUp(self):
        pass

    def test_create_client(self):
        """
        Functia testeaza daca obiectul de tip Client s-a creat cu succes precum si metodele sale
        :param:-
        :return:-
        """
        client_test = Client('TestName', '1234567890123')
        self.assertEqual(client_test.get_name(), 'TestName')
        self.assertEqual(client_test.get_cnp(), '1234567890123')
        client_test.set_name('TestName2')
        self.assertEqual(client_test.get_name(), 'TestName2')
        client_test.set_cnp('1234567890124')
        self.assertEqual(client_test.get_cnp(), '1234567890124')

    def test_validate_film(self):
        """
        Functia testeaza functia de validare a datelor transmise pentru crearea unui client
        :param:-
        :return:-
        """
        # Numele trebuie sa aiba cel putin 2 caractere
        client_test1 = Client('A', '1234567890124')
        validator_client1 = ClientValidator()
        self.assertRaises(ValidationException)
        # CNP-ul trebuie sa aiba 13 caractere
        client_test2 = Client('TestName', '12345')
        validator_client2 = ClientValidator()
        self.assertRaises(ValidationException)
        # CNP-ul trebuie sa contina doar cifre
        client_test3 = Client('TestName', 'TestCNP')
        validator_client3 = ClientValidator()
        self.assertRaises(ValidationException)

    def test_eq(self):
        """
        Functia testeaza metoda __eq__ din clasa Client
        :param:-
        :return:-
        """
        client_test1 = Client('TestName', '1234567890123')
        client_test2 = Client('TestName', '1234567890123')
        self.assertEqual(client_test1, client_test2)
        client_test3 = Client('TestName', '1234567890124')
        self.assertNotEqual(client_test1, client_test3)

    def tearDown(self):
        pass


if __name__ == '__main__':
    unittest.main()