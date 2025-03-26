from client_manager import RepositoryClient
from client_validator import ClientValidator
from clients import Client
from service_client import ServiceClient


def test_add():
    """
    Functia testeaza functia de adaugare de persoane in lista de clienti
    """
    validator=ClientValidator()
    list=RepositoryClient()
    service_c=ServiceClient(validator,list)
    service_c.add('Pop Maria','2893021256744')
    service_c.add('Popescu Andrei','3422167489223')
    expected=[Client('Pop Maria','2893021256744'),
              Client('Popescu Andrei','3422167489223')]
    assert service_c.get_all()==expected
    service_c.add( 'Popescu Alin', '1422167189223')
    expected = [Client( 'Pop Maria', '2893021256744'),
                Client( 'Popescu Andrei', '3422167489223'),
                Client( 'Popescu Alin', '1422167189223')]
    assert service_c.get_all()==expected
    service_c.add('Ionescu Ionel','5627893812335')
    expected = [Client( 'Pop Maria', '2893021256744'),
                Client( 'Popescu Andrei', '3422167489223'),
                Client( 'Popescu Alin', '1422167189223'),
                Client( 'Ionescu Ionel', '5627893812335')]
    assert service_c.get_all()==expected

def test_remove():
    """
    Functia testeaza functia de stergere a unui client din lista de clienti
    """
    validator = ClientValidator()
    list = RepositoryClient()
    service_c = ServiceClient(validator, list)
    service_c.add('Pop Maria', '2893021256744')
    service_c.add( 'Popescu Andrei', '3422167489223')
    service_c.add( 'Popescu Ana', '2422167189223')
    service_c.add( 'Popescu Alin', '1422167189223')
    service_c.remove_client(1)
    expected=[Client( 'Popescu Andrei', '3422167489223'),
              Client('Popescu Ana', '2422167189223'),
              Client( 'Popescu Alin', '1422167189223')]
    assert service_c.get_all()==expected
    service_c.remove_client(3)
    expected=[Client( 'Popescu Andrei', '3422167489223'),
              Client( 'Popescu Alin', '1422167189223')]
    assert service_c.get_all()==expected
    service_c.remove_client(4)
    expected=[Client('Popescu Andrei', '3422167489223')]
    assert service_c.get_all()==expected

def test_replace():
    """
    Functia testeaza functia de inlocuire a unui client din lista de clienti
    """
    validator = ClientValidator()
    list = RepositoryClient()
    service_c = ServiceClient(validator, list)
    service_c.add('Pop Maria', '2893021256744')
    service_c.add( 'Popescu Andrei', '3422167489223')
    service_c.add( 'Popescu Ana', '2422167189223')
    service_c.add( 'Popescu Alin', '1422167189223')
    service_c.replace(1,'Ionascu Ion','3456778901234')
    expected=[Client('Ionascu Ion','3456778901234'),
              Client( 'Popescu Andrei', '3422167489223'),
              Client( 'Popescu Ana', '2422167189223'),
              Client('Popescu Alin', '1422167189223')]

    assert service_c.get_all()==expected
    service_c.replace(2,'Popescu Lina','4567890123456')
    expected = [Client( 'Ionascu Ion', '3456778901234'),
                Client('Popescu Lina','4567890123456'),
                Client( 'Popescu Ana', '2422167189223'),
                Client( 'Popescu Alin', '1422167189223')]
    assert service_c.get_all()==expected
    service_c.replace(3,'Maria Maria','3452671236789')
    expected = [Client( 'Ionascu Ion', '3456778901234'),
                Client( 'Popescu Lina', '4567890123456'),
                Client('Maria Maria','3452671236789'),
                Client( 'Popescu Alin', '1422167189223')]
    assert service_c.get_all()==expected

def test_find():
    """
    Functia testeaza functia de cautare a unui client din lista de clienti
    """
    validator = ClientValidator()
    list = RepositoryClient()
    service_c = ServiceClient(validator, list)
    service_c.add( 'Pop Maria', '2893021256744')
    service_c.add( 'Popescu Andrei', '3422167489223')
    service_c.add( 'Popescu Ana', '2422167189223')
    service_c.add( 'Popescu Alin', '1422167189223')
    assert Client( 'Popescu Andrei', '3422167489223')==service_c.find_by_id(2)
    assert Client( 'Popescu Ana', '2422167189223')==service_c.find_by_id(3)
    assert Client('Pop Maria', '2893021256744')==service_c.find_by_id(1)

def test_filtrare():
    """
    Functia testeaza functia de filtrare a listei de clienti
    """
    validator = ClientValidator()
    list = RepositoryClient()
    service_c = ServiceClient(validator, list)
    service_c.add('Pop Maria', '2893021256744')
    service_c.add('Popescu Andrei', '3422167489223')
    service_c.add('Popescu Ana', '2422167189223')
    service_c.add('Popescu Alin', '1422167189223')
    service_c.add('Pop Marian','5637893812335')
    lista,ok=service_c.filtrare('Popescu')
    assert lista==[Client('Popescu Andrei', '3422167489223'),Client('Popescu Ana', '2422167189223'),
                   Client('Popescu Alin','1422167189223')]
    assert ok==1
    lista,ok=service_c.filtrare('Pop')
    assert lista==[Client('Pop Maria', '2893021256744'),Client('Pop Marian','5637893812335')]
    assert ok==1
    lista,ok=service_c.filtrare('Marius')
    assert ok==0
    assert lista==[]

def test_clienti():
    """
    Functia apeleaza toate functiile care testeaza functiile care actioneaza asupra listei de clienti
    """
    test_add()
    test_remove()
    test_replace()
    test_find()
    test_filtrare()