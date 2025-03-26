import shutil
import unittest

from domain.domain import Melodie
from repository.repository import Repository


class TesteRepo(unittest.TestCase):
    def setUp(self):
        shutil.copy('default.txt','test.txt')
        repo=Repository('test.txt')
        self.repo=repo

    def test_get_all(self):
        lst=self.repo.get_all()
        with open('test.txt','r') as f:
            lines=f.readlines()
        self.assertEqual(len(lst),len(lines))

    def test_modifica_melodie(self):
        self.repo.modificare_melodie('Test1','Test1','Rock','10.09.2020')
        lst = self.repo.get_all()
        for el in lst:
            if el.get_titlu()=='Test1' and el.get_artist()=='Test1':
                self.assertNotEqual(el.get_gen(), 'Jazz')
                self.assertNotEqual(el.get_data(), '11.12.1930')
                self.assertEqual(el.get_gen(), 'Rock')
                self.assertEqual(el.get_data(), '10.09.2020')
        self.assertRaises(Exception,self.repo.modificare_melodie,'Test4','Test4','Rock','10.09.2020')

    def test_adauga(self):
        lst=self.repo.get_all()
        self.repo.adauga_melodie('Test10','Test10','Rock','10.09.2020')
        self.assertEqual(len(self.repo.get_all()),len(lst)+1)

    def tearDown(self):
        with open('test.txt','w') as f:
            pass