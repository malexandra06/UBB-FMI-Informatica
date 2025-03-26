import unittest

from domain_problem.inchiriere import Inchiriere


class TestDomainInchiriere(unittest.TestCase):
    def setUp(self):
        pass

    def test_create_inchiriere(self):
        """
        Functia testeaza daca obiectul de tip Inchiriere s-a creat cu succes precum si metodele sale
        :param:-
        :return:-
        """
        rent_test = Inchiriere(1,2,True)
        self.assertEqual(rent_test.get_id_client(), 1)
        self.assertEqual(rent_test.get_id_film(), 2)
        self.assertEqual(rent_test.get_inchiriat(),True)
        rent_test.returnat()
        self.assertEqual(rent_test.get_inchiriat(),False)
        rent_test.inchiriat()
        self.assertEqual(rent_test.get_inchiriat(),True)

    def test_eq(self):
        """
        Functia testeaza metoda __eq__ din clasa Inchiriere
        :param:-
        :return:-
        """
        test1 = Inchiriere(1,2,True)
        test2 = Inchiriere(1,2,False)
        self.assertEqual(test1, test2)
        test3 = Inchiriere(2,2,True)
        self.assertNotEqual(test1, test3)

    def tearDown(self):
        pass


if __name__ == '__main__':
    unittest.main()