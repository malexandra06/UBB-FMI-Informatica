from service.service_inchirieri import *
from inchiriere import Inchiriere
from inchiriere_validator import InchiriereValidator
from films_data import Film
from clients import Client

def test_add():
    """
    Functia testeaza functia de adaugare a unei inchirieri in lista
    """
    validator=InchiriereValidator()
    repof=RepositoryFilm()
    repoc=RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoi=RepositoryInchirieri()
    service = ServiceInchirieri(repoi,repof, repoc, validator)
    service.add(1,1)
    service.add(2,3)
    service.add(1,2)
    expected=[Inchiriere(Client('Pop Maria', '2893021256744'),Film('Titanic', 'Actori buni.', 'romance')),
              Inchiriere(Client('Popescu Andrei', '3422167489223'),Film('Barbie', 'Actori buni.', 'romance')),
              Inchiriere(Client('Pop Maria', '2893021256744'),Film('Oppenheimer', 'A castigat Oscarul', 'action'))]
    assert service.get_all()==expected

def test_remove():
    """
    Functia testeaza functia de stergere a unei inchirieri din lista de inchirieri
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoi=RepositoryInchirieri()
    service = ServiceInchirieri(repoi,repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    service.remove_inchiriere(1,1)
    expected=[  Inchiriere(Client('Popescu Andrei', '3422167489223'), Film('Barbie', 'Actori buni.', 'romance')),
                Inchiriere(Client('Pop Maria', '2893021256744'),Film('Oppenheimer', 'A castigat Oscarul', 'action'))]
    assert service.get_all() == expected

def test_returnare():
    """
    Functia testeaza functia de returnare a unei inchirieri din lista de inchirieri
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoi=RepositoryInchirieri()
    service = ServiceInchirieri(repoi,repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    service.return_film(1,2)
    assert repoi.find_by_id(1,2).get_inchiriere()==False
    service.return_film(1,1)
    assert repoi.find_by_id(1,1).get_inchiriere()==False
    assert repoi.find_by_id(2,3).get_inchiriere()==True
    assert repoi.find_by_id(1,2).get_inchiriere()==False

def test_find():
    """
    Functia testeaza functia de cautare a unei inchirieri din lista de inchirieri
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoi=RepositoryInchirieri()
    service = ServiceInchirieri(repoi,repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    assert service.find_by_id(1,1)==Inchiriere(Client('Pop Maria', '2893021256744'),Film('Titanic', 'Actori buni.', 'romance'))


def test_raport_film():
    """
    Functia testeaza generarea de rapoarte a filmelor
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repof.add(Film('Singur acasa', 'Actori buni.', 'comedie'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoc.add(Client('Ionascu Matei','6789012345677'))
    repoc.add(Client('Maria Maria','5678901234566'))
    repoi = RepositoryInchirieri()
    service = ServiceInchirieri(repoi, repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    service.add(3,1)
    service.add(3,2)
    service.add(1,4)
    service.add(2,2)
    lista=service.cele_mai_inchiriate_filme()
    assert lista==[ReportFilm('Oppenheimer',3),ReportFilm('Titanic',2),ReportFilm('Barbie',1),ReportFilm('Singur acasa',1)]

def test_raport_clienti():
    """
    Functia testeaza generarea de rapoarte a clientilor
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repof.add(Film('Singur acasa', 'Actori buni.', 'comedie'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoc.add(Client('Ionascu Matei', '6789012345677'))
    repoc.add(Client('Maria Maria', '5678901234566'))
    repoi = RepositoryInchirieri()
    service = ServiceInchirieri(repoi, repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    service.add(3, 1)
    service.add(4, 2)
    service.add(1, 4)
    service.add(2, 2)
    lista=service.clienti_inchirieri()
    assert lista==[ReportClient('Pop Maria',3),ReportClient('Popescu Andrei',2),ReportClient('Ionascu Matei',1),ReportClient('Maria Maria',1)]

def test_top_30():
    """
    Functia testeaza generarea topului de 30% clienti care au cele mai multe inchirieri
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repof.add(Film('Singur acasa', 'Actori buni.', 'comedie'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoc.add(Client('Ionascu Matei', '6789012345677'))
    repoc.add(Client('Maria Maria', '5678901234566'))
    repoi = RepositoryInchirieri()
    service = ServiceInchirieri(repoi, repof, repoc, validator)
    service.add(1, 1)
    service.add(2, 3)
    service.add(1, 2)
    service.add(3, 1)
    service.add(4, 2)
    service.add(1, 4)
    service.add(2, 2)
    lista=service.top_30()
    assert lista==[ReportClient('Pop Maria',3)]

def test_top5():
    """
    Functia testeaza generarea topului de 5 genuri care au cele mai multe inchirieri
    """
    validator = InchiriereValidator()
    repof = RepositoryFilm()
    repoc = RepositoryClient()
    repof.add(Film('Titanic', 'Actori buni.', 'romance'))
    repof.add(Film('Oppenheimer', 'A castigat Oscarul', 'action'))
    repof.add(Film('Barbie', 'Actori buni.', 'romance'))
    repof.add(Film('Singur acasa', 'Actori buni.', 'comedie'))
    repof.add(Film('Ion','film bazat pe o carte','drama'))
    repof.add(Film('The Nun','filmat in Romania','horror'))
    repof.add(Film('The Notebook','super','thriller'))
    repoc.add(Client('Pop Maria', '2893021256744'))
    repoc.add(Client('Popescu Andrei', '3422167489223'))
    repoc.add(Client('Ionascu Matei', '6789012345677'))
    repoc.add(Client('Maria Maria', '5678901234566'))
    repoi = RepositoryInchirieri()
    service = ServiceInchirieri(repoi, repof, repoc, validator)
    service.add(1, 1)
    service.add(1,3)
    service.add(1,4)
    service.add(1,5)
    service.add(2, 3)
    service.add(2, 4)
    service.add(2, 5)
    service.add(2, 6)
    service.add(3, 1)
    service.add(3, 2)
    service.add(3, 6)
    service.add(4, 1)
    service.add(4, 3)
    service.add(4, 4)
    service.add(4, 6)
    service.add(4, 5)
    service.add(1, 7)
    service.add(2, 7)
    lista=service.top_5_gen()
    assert lista==[ReportGen('romance',6),ReportGen('comedie',3),ReportGen('drama',3),ReportGen('horror',3),ReportGen('thriller',2)]
def test_inchiriere():
    """
    Functia testeaza toate functiile de inchiriere
    """
    test_add()
    test_remove()
    test_returnare()
    test_find()
    test_raport_film()
    test_raport_clienti()
    test_top_30()
    test_top5()