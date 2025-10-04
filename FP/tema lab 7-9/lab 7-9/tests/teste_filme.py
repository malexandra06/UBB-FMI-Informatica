from film_manager import RepositoryFilm
from film_validator import *
from service_film import ServiceFilm


def test_add():
    """
    Functia testeaza functia de adaugare de numere in lista de filme
    input:-
    output:-
    """
    validator=FilmValidator()
    films=RepositoryFilm()
    service=ServiceFilm(validator,films)
    service.add('Titanic','Actori buni.','romance')
    service.add('Oppenheimer','A castigat Oscarul','action')
    expected=[Film('Titanic','Actori buni.','romance'),
              Film('Oppenheimer','A castigat Oscarul','action')]
    assert service.get_all()==expected
    service.add('Barbie','Actori buni.','romance')
    expected = [Film( 'Titanic', 'Actori buni.', 'romance'),
                Film('Oppenheimer', 'A castigat Oscarul', 'action'),
                Film( 'Barbie', 'Actori buni.', 'romance')]
    assert service.get_all() == expected

def test_remove():
    """
    Functia testeaza functia de stergere a unui film dintr-o lista de filme
    input:-
    output:-
    """
    validator = FilmValidator()
    films = RepositoryFilm()
    service = ServiceFilm(validator, films)
    service.add('Titanic', 'Actori buni.', 'romance')
    service.add( 'Oppenheimer', 'A castigat Oscarul', 'action')
    service.add('Barbie','Actori buni.','romance')
    service.remove_film(1)
    expected = [Film( 'Oppenheimer', 'A castigat Oscarul', 'action'),
                Film( 'Barbie', 'Actori buni.', 'romance')]
    assert service.get_all() == expected
    service.add('FNAF', 'Actori buni.','horror')
    service.remove_film(2)
    expected = [Film('Barbie', 'Actori buni.', 'romance'),
        Film('FNAF', 'Actori buni.', 'horror')]
    assert service.get_all() == expected

def test_replace():
    """
    Functia testeaza functia de inlocuire a unui film din lista de filme
    """
    validator = FilmValidator()
    films = RepositoryFilm()
    service = ServiceFilm(validator, films)
    service.add('Titanic', 'Actori buni.', 'romance')
    service.add('Oppenheimer', 'A castigat Oscarul', 'action')
    service.add('Barbie', 'Actori buni.', 'romance')
    service.replace(1,'Divergent','super','action')
    expected = [
                Film( 'Divergent', 'super', 'action'),
                Film( 'Oppenheimer', 'A castigat Oscarul', 'action'),
                Film( 'Barbie', 'Actori buni.', 'romance')]
    assert service.get_all() == expected
    service.replace(3,'The Notebook','super','romance')
    expected = [Film('Divergent', 'super', 'action'),
                Film('Oppenheimer', 'A castigat Oscarul', 'action'),
                Film('The Notebook','super','romance')]
    assert service.get_all() == expected

def test_find():
    """
    Functia testeaza functia de cautare a unui film din lista de filme
    """
    validator = FilmValidator()
    films = RepositoryFilm()
    service = ServiceFilm(validator, films)
    service.add('Titanic', 'Actori buni.', 'romance')
    service.add('Oppenheimer', 'A castigat Oscarul', 'action')
    service.add('Barbie', 'Actori buni.', 'romance')
    assert service.find_by_id(1)==Film('Titanic','Actori buni.','romance')
    assert service.find_by_id(2)==Film( 'Oppenheimer', 'A castigat Oscarul', 'action')
    assert service.find_by_id(3)==Film( 'Barbie', 'Actori buni.', 'romance')

def test_filtrare():
    """
    Functia testeaza functia de filtrare a listei de filme
    """
    validator = FilmValidator()
    films = RepositoryFilm()
    service = ServiceFilm(validator, films)
    service.add('Titanic', 'Actori buni.', 'romance')
    service.add('Oppenheimer', 'A castigat Oscarul', 'action')
    service.add('Barbie', 'Actori buni.', 'romance')
    service.add('FNAF', 'Actori buni.','horror')
    service.add('The Notebook','super','romance')
    lista,ok=service.filtrare('romance')
    assert lista==[Film('Titanic','Actori buni.','romance'),Film('Barbie','Actori buni.','romance'),Film('The Notebook','super','romance')]
    assert ok==1
    lista,ok=service.filtrare('comedie')
    assert lista==[]
    assert ok==0
    lista,ok=service.filtrare('action')
    assert lista==[Film('Oppenheimer', 'A castigat Oscarul', 'action')]
    assert ok==1

def test_filme():
    """
    Functia apeleaza toate testele functiilor care actioneaza asupra listei de filme
    """
    test_add()
    test_remove()
    test_replace()
    test_find()
    test_filtrare()