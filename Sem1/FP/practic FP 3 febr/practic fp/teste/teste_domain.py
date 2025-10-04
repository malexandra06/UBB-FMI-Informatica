import unittest

from domain.domain import Melodie


class TestDomain(unittest.TestCase):
    def setUp(self):
        pass

    def test_get(self):
        melodie=Melodie('Test1','Test1','Test1','Test1')
        self.assertEqual(melodie.get_titlu(), 'Test1')
        self.assertEqual(melodie.get_artist(), 'Test1')
        self.assertEqual(melodie.get_gen(), 'Test1')
        self.assertEqual(melodie.get_data(), 'Test1')

    def test_set(self):
        melodie=Melodie('Test1','Test1','Test1','Test1')
        melodie.set_titlu('Test2')
        self.assertEqual(melodie.get_titlu(), 'Test2')
        melodie.set_artist('Test2')
        self.assertEqual(melodie.get_artist(), 'Test2')
        melodie.set_gen('Test2')
        self.assertEqual(melodie.get_gen(), 'Test2')
        melodie.set_data('Test2')
        self.assertEqual(melodie.get_data(), 'Test2')

    def test_eq(self):
        melodie1 = Melodie('Test1', 'Test1', 'Test1', 'Test1')
        melodie2 = Melodie('Test1', 'Test1', 'Test1', 'Test1')
        melodie3 = Melodie('Test3', 'Test3', 'Test3', 'Test3')
        self.assertEqual(melodie1, melodie2)
        self.assertNotEqual(melodie1, melodie3)


    def tearDown(self):
        pass