import shutil
import unittest

from domain.domain import Melodie
from domain.validator import Validator
from repository.repository import Repository
from service.service import Service


class TesteRepo(unittest.TestCase):
    def setUp(self):
        shutil.copy('default.txt', 'test.txt')
        repo = Repository('test.txt')
        validator=Validator()
        self.service = Service(repo, validator)

    def test_get_all(self):
        lst = self.service.get_all()
        with open('test.txt', 'r') as f:
            lines = f.readlines()
        self.assertEqual(len(lst), len(lines))

    def test_modifica_melodie(self):
        self.service.modificare_melodie('Test1', 'Test1', 'Rock', '10.09.2020')
        lst = self.service.get_all()
        for el in lst:
            if el.get_titlu() == 'Test1' and el.get_artist() == 'Test1':
                self.assertNotEqual(el.get_gen(), 'Jazz')
                self.assertNotEqual(el.get_data(), '11.12.1930')
                self.assertEqual(el.get_gen(), 'Rock')
                self.assertEqual(el.get_data(), '10.09.2020')

    def test_adauga(self):
        lst=self.service.get_all()
        self.service.adauga_melodie('Test2', 'Test10', 'Rock', '10.09.2020')
        self.assertEqual(len(lst)+1,len(self.service.get_all()))

    def test_adauga_random(self):
        lst=self.service.get_all()
        titluri='A1,A2,A3,A4'
        artisti='B1,B2,B3,B4'
        self.service.genereaza_random(4, titluri, artisti)
        self.assertEqual(len(lst)+4, len(self.service.get_all()))

    def test_cautare(self):
        self.assertEqual(self.service.cautare('Test1','Test1'),True)
        self.assertEqual(self.service.cautare('Test2','Test1'),False)

    def test_statistici(self):
        melodie_veche,melodie_noua,dict_gen,artist_max,max=self.service.statistici()
        self.assertEqual(melodie_veche,Melodie('Test3','Test3','Rock','10.08.1760'))
        self.assertEqual(melodie_noua,Melodie('Test2','Test3','Rock','11.11.1950'))
        self.assertEqual(dict_gen["Rock"],2)
        self.assertEqual(dict_gen["Jazz"],1)
        self.assertEqual(dict_gen["Pop"],0)
        self.assertEqual(artist_max,'Test3')
        self.assertEqual(max,2)

    def tearDown(self):
        with open('test.txt', 'w') as f:
            pass