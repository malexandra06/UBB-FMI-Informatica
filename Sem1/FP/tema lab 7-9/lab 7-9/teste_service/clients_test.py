import unittest
from domain_problem.clients import Client
from domain_problem.client_validator import ClientValidator
from exceptions.exceptions import PersonDoesNotExistException,PersonAlreadyExistsException,ValidationException
from repository.client_manager import RepoFileClient
from service.service_client import ServiceClient
from utils.auxiliary import clear_file_content, copy_file_content

class TestsClientiService(unittest.TestCase):
    def setUp(self):
        print("setUp called")
        #method that unittest calls before running each test method in a test case class
        copy_file_content('clienti_default.txt', 'test_clienti.txt')
        client_repo = RepoFileClient('test_clienti.txt')
        client_validator=ClientValidator()
        self.service=ServiceClient(client_validator,client_repo)

    def test_add_client(self):
        initial_size=len(self.service.get_all())
        self.service.add('Popescu Ioana','3453453453456')
        self.assertEqual(len(self.service.get_all()),initial_size+1)
        self.assertRaises(ValidationException,self.service.add,'Popescu Maria','34534534534ab')
        self.assertRaises(ValidationException,self.service.add,'Popescu Maria','34534534534789')
        self.assertRaises(ValidationException,self.service.add,'P','34534534534a')


    def test_remove_client(self):
        initial_size=len(self.service.get_all())
        self.service.remove_client(2)
        self.assertEqual(len(self.service.get_all()),initial_size-1)
        self.assertRaises(PersonDoesNotExistException,self.service.remove_client,2)

    def test_replace_client(self):
        self.service.replace(2,'Pascal Maria','3456765456374')
        self.assertEqual(self.service.find_by_id(2),Client('Pascal Maria','3456765456374'))
        self.assertRaises(PersonDoesNotExistException,self.service.replace,999,'Pascal Maria','3456765456374')
        self.assertRaises(ValidationException,self.service.replace,2,'I','3456765456374')
        self.assertRaises(ValidationException,self.service.replace,2,'Iarghdks','34567654563747')
        self.assertRaises(ValidationException,self.service.replace,2,'I','3456765456374avbjg')

    def test_find_by_id(self):
        self.assertEqual(self.service.find_by_id(2),Client('Dumitrescu Ionel', '1790604123456'))
        self.assertRaises(PersonDoesNotExistException,self.service.find_by_id,999)

    def test_filtrare(self):
        v=self.service.filtrare('Dumitrescu')
        self.assertEqual(len(v),3)
        v=self.service.filtrare('Popa')
        self.assertEqual(len(v),0)

    def test_filtrare_recursiv(self):
        lst=None
        v = self.service.filtrare_recursiv('Dumitrescu',lst,0)
        self.assertEqual(len(v), 3)
        lst=None
        v = self.service.filtrare_recursiv('Popa',lst,0)
        self.assertEqual(len(v), 0)

    def tearDown(self) -> None:
        print("tearDown called")
        #method that unittest calls after running each test method in a test case class
        clear_file_content("test_filme.txt")

if __name__ == '__main__':
    unittest.main()