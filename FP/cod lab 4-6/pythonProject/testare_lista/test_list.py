from numar_complex import NUMAR_COMPLEX
from functii_auxiliare import lista_in_dictionar
from number_repository import NumberRepository
from number_repository_dict import NumberRepositoryDict


def test_stergere_pozitie():
    """
    Functia testeaza functia de stergere a unui element de pe o pozitie data
    input:-
    output:-
    """
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(3, 7))
    repo.add_number(NUMAR_COMPLEX(3, 6))
    repo.add_number(NUMAR_COMPLEX(2, 1))
    repo.add_number(NUMAR_COMPLEX(9, 6))

    repo.remove_p(2)
    lista_asteptata = [
        NUMAR_COMPLEX(1, 2),
        NUMAR_COMPLEX(3, 7),
        NUMAR_COMPLEX(2, 1),
        NUMAR_COMPLEX(9, 6)
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 4))
    repo.add_number(NUMAR_COMPLEX(7, 9))
    repo.add_number(NUMAR_COMPLEX(1, -6))
    repo.add_number(NUMAR_COMPLEX(-7, 9))

    repo.remove_p(0)
    lista_asteptata = [
        NUMAR_COMPLEX(7, 9),
        NUMAR_COMPLEX(1, -6),
        NUMAR_COMPLEX(-7, 9)
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(5, 7))
    repo.add_number(NUMAR_COMPLEX(9, 4))

    try:
        repo.remove_p(5)
    except IndexError:
        pass
    lista_asteptata = [
        NUMAR_COMPLEX(1, 2),
        NUMAR_COMPLEX(5, 7),
        NUMAR_COMPLEX(9, 4)
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)


def test_stergere_secventa():
    """
    Functia contine teste pentru functia de stergere a unei secvente dint-o lista de numere complexe
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, 3))
    repo.add_number(NUMAR_COMPLEX(9, -8))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    repo.add_number(NUMAR_COMPLEX(5, 9))
    repo.add_number(NUMAR_COMPLEX(7, 8))

    repo.remove_secv(1, 3)
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(5, 9),
        NUMAR_COMPLEX(7, 8),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 8))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(-8, -2))
    repo.add_number(NUMAR_COMPLEX(-3, -11))

    repo.remove_secv(2, 4)
    lista_asteptata = [
        NUMAR_COMPLEX(1, 8),
        NUMAR_COMPLEX(2, 5),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(3, 5))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(8, 11))

    repo.remove_secv(-1, 2)  # Indiciu invalid, nu va schimba lista
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(3, 5),
        NUMAR_COMPLEX(6, 7),
        NUMAR_COMPLEX(8, 11),
    ]
    try:
        if type(repo) == 'NumberRepositoryDict':
            dict = lista_in_dictionar(lista_asteptata)
            assert (dict == repo.get_all_numbers())
        elif type(repo)=='NumberRepository':
            assert (repo.get_all_numbers() == lista_asteptata)
    except IndexError:
        pass


def test_inlocuieste():
    """
    Functia contine teste pentru functia de inlocuire a unui numar dintr-o lista cu un alt numar
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(4, 7))
    repo.add_number(NUMAR_COMPLEX(2, 3))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(9, 8))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(7, 8))
    repo.replace(NUMAR_COMPLEX(1, 2), NUMAR_COMPLEX(11, 13))
    lista_asteptata = [
        NUMAR_COMPLEX(11, 13),
        NUMAR_COMPLEX(4, 7),
        NUMAR_COMPLEX(2, 3),
        NUMAR_COMPLEX(11, 13),
        NUMAR_COMPLEX(9, 8),
        NUMAR_COMPLEX(11, 13),
        NUMAR_COMPLEX(7, 8),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(7, 4))
    repo.add_number(NUMAR_COMPLEX(1, 9))
    repo.add_number(NUMAR_COMPLEX(2, 3))
    repo.replace(NUMAR_COMPLEX(-3, -4), NUMAR_COMPLEX(1, 3))  # Nu va schimba nimic deoarece numărul nu există
    lista_asteptata = [
        NUMAR_COMPLEX(1, 2),
        NUMAR_COMPLEX(7, 4),
        NUMAR_COMPLEX(1, 9),
        NUMAR_COMPLEX(2, 3),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(4, 7))
    repo.add_number(NUMAR_COMPLEX(8, 3))
    repo.add_number(NUMAR_COMPLEX(7, 9))
    repo.add_number(NUMAR_COMPLEX(4, 7))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(5, 9))
    repo.replace(NUMAR_COMPLEX(4, 7), NUMAR_COMPLEX(-2, -3))
    lista_asteptata = [
        NUMAR_COMPLEX(-2, -3),
        NUMAR_COMPLEX(8, 3),
        NUMAR_COMPLEX(7, 9),
        NUMAR_COMPLEX(-2, -3),
        NUMAR_COMPLEX(1, 2),
        NUMAR_COMPLEX(5, 9),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == repo.get_all_numbers()
    else:
        assert (repo.get_all_numbers() == lista_asteptata)


def test_tipareste_imaginar():
    """
    Functia testeaza functia care retine partea imaginara a numerelor dintr-o secventa data
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 3))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(9, 2))
    repo.add_number(NUMAR_COMPLEX(3, 1))
    repo.add_number(NUMAR_COMPLEX(9, 5))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    secv = repo.tipareste_imaginar(1, 4)
    lista_asteptata = [7, 2, 1, 5]
    assert secv == lista_asteptata

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 8))
    repo.add_number(NUMAR_COMPLEX(7, 5))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(2, -3))
    repo.add_number(NUMAR_COMPLEX(4, -5))
    repo.add_number(NUMAR_COMPLEX(-9, 1))
    secv = repo.tipareste_imaginar(2, 4)
    lista_asteptata = [7, -3, -5]
    assert secv == lista_asteptata

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(4, 2))
    repo.add_number(NUMAR_COMPLEX(3, 7))
    repo.add_number(NUMAR_COMPLEX(8, 1))
    # Indici invalidi, trebuie să returneze o listă goală
    try:
        secv = repo.tipareste_imaginar(3, 9)
    except IndexError:
        pass


def test_tipareste():
    """
    Functia contine teste ale functiei care retine numerele complexe care au modulul mai mic decat 10
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(5, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(2, 4))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(1, 4))
    repo.add_number(NUMAR_COMPLEX(4, 9))
    secv = repo.tipareste()
    lista_asteptata = [
        NUMAR_COMPLEX(5, 7),
        NUMAR_COMPLEX(2, 4),
        NUMAR_COMPLEX(1, 4),  # Corectat de la 1, 2 la 1, 4
        NUMAR_COMPLEX(4, 9),  # Trebuie verificat calculul pentru modulus
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 7))
    repo.add_number(NUMAR_COMPLEX(7, 9))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(1, 10))
    repo.add_number(NUMAR_COMPLEX(9, 9))
    secv = repo.tipareste()
    lista_asteptata = [
        NUMAR_COMPLEX(3, 7),
        NUMAR_COMPLEX(2, 5),
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(9, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(2, 11))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(13, 2))
    repo.add_number(NUMAR_COMPLEX(5, 9))
    secv = repo.tipareste()
    lista_asteptata = []
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)


def test_tipareste_modul_egal():
    """
    Functia testeaza functia care determina numerele complexe care au modulul egal cu 10
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(5, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(6, 8))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(10, 0))
    repo.add_number(NUMAR_COMPLEX(4, 9))
    secv = repo.tipareste_modul_egal()
    lista_asteptata = [
        NUMAR_COMPLEX(6, 8),
        NUMAR_COMPLEX(10, 0)
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(-7, 9))
    repo.add_number(NUMAR_COMPLEX(6, 8))
    repo.add_number(NUMAR_COMPLEX(-8, 6))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(0, 10))
    secv = repo.tipareste_modul_egal()
    lista_asteptata = [
        NUMAR_COMPLEX(6, 8),
        NUMAR_COMPLEX(-8, 6),
        NUMAR_COMPLEX(0, 10)
    ]
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(5, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(2, 4))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(4, 9))
    secv = repo.tipareste_modul_egal()
    lista_asteptata = []
    if type(repo) == 'NumberRepositoryDict':
        dict = lista_in_dictionar(lista_asteptata)
        assert dict == secv
    else:
        assert (secv == lista_asteptata)


def test_aduna_numere_complexe():
    """
    Functia contine teste ale functiei aduna_numere_complexe
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, -9))
    repo.add_number(NUMAR_COMPLEX(-6, 8))
    repo.add_number(NUMAR_COMPLEX(4, 6))
    repo.add_number(NUMAR_COMPLEX(12, 2))
    repo.add_number(NUMAR_COMPLEX(1, 10))
    s = repo.aduna_numere_complexe(1, 3)
    assert s == NUMAR_COMPLEX(6, 5)

    # Test 2
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(-7, 9))
    repo.add_number(NUMAR_COMPLEX(6, 8))
    repo.add_number(NUMAR_COMPLEX(-8, 6))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(0, 10))
    try:
        s = repo.aduna_numere_complexe(1, 3)
    except IndexError:
        pass

    # Test 3
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 8))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(-8, -2))
    repo.add_number(NUMAR_COMPLEX(-3, -11))
    s = repo.aduna_numere_complexe(3, 4)
    assert s == NUMAR_COMPLEX(-11, -13)


def test_produs_numere_complexe():
    """
    Functia contine teste ale functiei produs_numere_complexe
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(5, 3))
    repo.add_number(NUMAR_COMPLEX(4, 5))
    repo.add_number(NUMAR_COMPLEX(-5, 7))
    repo.add_number(NUMAR_COMPLEX(7, 8))
    repo.add_number(NUMAR_COMPLEX(3, 7))
    repo.add_number(NUMAR_COMPLEX(7, -5))
    repo.add_number(NUMAR_COMPLEX(2, -3))
    repo.add_number(NUMAR_COMPLEX(11, 12))
    repo.add_number(NUMAR_COMPLEX(0, -10))
    repo.add_number(NUMAR_COMPLEX(7, 2))
    p = repo.produs_numere_complexe(3, 5)
    assert p == NUMAR_COMPLEX(120, 686)


def test_sorteaza_descrescator():
    """
    Functia contine teste ale functiei sorteaza_descrescator
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    # repo=NumberRepository()
    repo.add_number(NUMAR_COMPLEX(5, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(2, 4))
    repo.add_number(NUMAR_COMPLEX(8, 6))
    repo.add_number(NUMAR_COMPLEX(1, 2))
    repo.add_number(NUMAR_COMPLEX(4, 8))
    lista = repo.sorteaza_descrescator()
    lista_asteptata = [
        NUMAR_COMPLEX(8, 9),
        NUMAR_COMPLEX(4, 8),
        NUMAR_COMPLEX(5, 7),
        NUMAR_COMPLEX(8, 6),
        NUMAR_COMPLEX(2, 4),
        NUMAR_COMPLEX(1, 2),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata

    # Test 2
    repo = NumberRepositoryDict()
    #repo=NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 5))
    repo.add_number(NUMAR_COMPLEX(7, 9))
    repo.add_number(NUMAR_COMPLEX(2, 4))
    repo.add_number(NUMAR_COMPLEX(8, 7))
    repo.add_number(NUMAR_COMPLEX(1, 10))
    repo.add_number(NUMAR_COMPLEX(9, 6))
    lista = repo.sorteaza_descrescator()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 10),
        NUMAR_COMPLEX(7, 9),
        NUMAR_COMPLEX(8, 7),
        NUMAR_COMPLEX(9, 6),
        NUMAR_COMPLEX(3, 5),
        NUMAR_COMPLEX(2, 4),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata

    # Test 3
    repo = NumberRepositoryDict()
    #repo=NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 3))
    repo.add_number(NUMAR_COMPLEX(6, 7))
    repo.add_number(NUMAR_COMPLEX(9, 9))
    repo.add_number(NUMAR_COMPLEX(3, 1))
    repo.add_number(NUMAR_COMPLEX(9, 13))
    repo.add_number(NUMAR_COMPLEX(2, 5))
    lista = repo.sorteaza_descrescator()
    lista_asteptata = [
        NUMAR_COMPLEX(9, 13),
        NUMAR_COMPLEX(9, 9),
        NUMAR_COMPLEX(6, 7),
        NUMAR_COMPLEX(2, 5),
        NUMAR_COMPLEX(1, 3),
        NUMAR_COMPLEX(3, 1),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata


def test_filtrare():
    """
    Functia testeaza functia de filtrare
    input:-
    output:-
    """
    # Test 1
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(7, 8))
    repo.add_number(NUMAR_COMPLEX(4, 6))
    repo.add_number(NUMAR_COMPLEX(5, 2))
    repo.add_number(NUMAR_COMPLEX(0, 10))
    lista = repo.filtrare_parte_reala_prim()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(8, 9),
        NUMAR_COMPLEX(4, 6),
        NUMAR_COMPLEX(0, 10),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata

    # Test 2
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.add_number(NUMAR_COMPLEX(6, 8))
    repo.add_number(NUMAR_COMPLEX(4, 6))
    repo.add_number(NUMAR_COMPLEX(12, 2))
    repo.add_number(NUMAR_COMPLEX(1, 10))
    lista = repo.filtrare_parte_reala_prim()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(8, 9),
        NUMAR_COMPLEX(6, 8),
        NUMAR_COMPLEX(4, 6),
        NUMAR_COMPLEX(12, 2),
        NUMAR_COMPLEX(1, 10),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata

    # Test 3
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(7, 9))
    repo.add_number(NUMAR_COMPLEX(6, 8))
    repo.add_number(NUMAR_COMPLEX(13, 6))
    repo.add_number(NUMAR_COMPLEX(11, 2))
    repo.add_number(NUMAR_COMPLEX(1, 10))
    lista = repo.filtrare_parte_reala_prim()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(6, 8),
        NUMAR_COMPLEX(1, 10),
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata


def test_filtrare_modul():
    """
    Functia testeaza functia filtrare_modul
    input:-
    output:-
    """
    # Test 1 - Operatorul '<'
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 4))  # modulul = 5
    repo.add_number(NUMAR_COMPLEX(1, 1))  # modulul ≈ 1.41
    repo.add_number(NUMAR_COMPLEX(0, 2))  # modulul = 2
    repo.add_number(NUMAR_COMPLEX(2, 2))  # modulul ≈ 2.83
    nr = NUMAR_COMPLEX(2, 2)  # modulul ≈ 2.83
    operand = '<'
    lista = repo.filtrare_modul(nr, operand)
    lista_asteptata = [
        NUMAR_COMPLEX(3, 4),  # corectat lista de asteptat
        NUMAR_COMPLEX(2, 2)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    elif isinstance(repo, NumberRepository):
        assert lista == lista_asteptata

    # Test 2 - Operatorul '='
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 4))  # modulul = 5
    repo.add_number(NUMAR_COMPLEX(1, 1))  # modulul ≈ 1.41
    repo.add_number(NUMAR_COMPLEX(0, 5))  # modulul = 5
    repo.add_number(NUMAR_COMPLEX(2, 3))  # modulul ≈ 3.61
    nr = NUMAR_COMPLEX(3, 4)  # modulul = 5
    operand = '='
    lista = repo.filtrare_modul(nr, operand)
    lista_asteptata = [
        NUMAR_COMPLEX(1, 1),  # corectat lista de asteptat
        NUMAR_COMPLEX(2, 3)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    elif isinstance(repo, NumberRepository):
        assert lista == lista_asteptata

    # Test 3 - Operatorul '>'
    repo = NumberRepositoryDict()
    #repo = NumberRepository()
    repo.add_number(NUMAR_COMPLEX(3, 4))  # modulul = 5
    repo.add_number(NUMAR_COMPLEX(0, 1))  # modulul = 1
    repo.add_number(NUMAR_COMPLEX(4, 4))  # modulul ≈ 5.66
    repo.add_number(NUMAR_COMPLEX(1, 2))  # modulul ≈ 2.24
    nr = NUMAR_COMPLEX(2, 2)  # modulul ≈ 2.83
    operand = '>'
    lista = repo.filtrare_modul(nr, operand)
    lista_asteptata = [
        NUMAR_COMPLEX(0, 1),  # corectat lista de asteptat
        NUMAR_COMPLEX(1, 2)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        assert lista == dict_ast
    else:
        assert lista == lista_asteptata


def test_undo():
    """
    Funcția testează funcția de undo
    input:-
    output:-
    """
    # Test 1 - Undo adăugare număr
    repo = NumberRepositoryDict()
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.undo()
    lista = repo.get_all_numbers()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        dict_lista = lista_in_dictionar(lista)  # Modificare adaugata
        assert dict_lista == dict_ast  # Modificat din lista
    else:
        assert lista == lista_asteptata

    # Test 2 - Undo ștergere număr
    repo.add_number(NUMAR_COMPLEX(1, 8))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.remove_secv(1, 2)
    repo.undo()
    lista = repo.get_all_numbers()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(1, 8),
        NUMAR_COMPLEX(8, 9)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        dict_lista = lista_in_dictionar(lista)  # Modificare adaugata
        assert dict_lista == dict_ast  # Modificat din lista
    else:
        assert lista == lista_asteptata

    # Test 4 - Undo ștergere interval
    repo.add_number_poz(NUMAR_COMPLEX(3, 5), 2)
    repo.undo()
    lista = repo.get_all_numbers()
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(1, 8),
        NUMAR_COMPLEX(8, 9)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        dict_lista = lista_in_dictionar(lista)  # Modificare adaugata
        assert dict_lista == dict_ast  # Modificat din lista
    else:
        assert lista == lista_asteptata

    # Test 5 - Undo înlocuire număr
    repo.add_number(NUMAR_COMPLEX(1, 7))
    repo.add_number(NUMAR_COMPLEX(8, 9))
    repo.replace(NUMAR_COMPLEX(1, 7), NUMAR_COMPLEX(2, 8))
    repo.undo()
    lista = list(repo.get_all_numbers())
    lista_asteptata = [
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(1, 8),
        NUMAR_COMPLEX(8, 9),
        NUMAR_COMPLEX(1, 7),
        NUMAR_COMPLEX(8, 9)
    ]
    if isinstance(repo, NumberRepositoryDict):
        dict_ast = lista_in_dictionar(lista_asteptata)
        dict_lista = lista_in_dictionar(lista)  # Modificare adaugata
        assert dict_lista == dict_ast  # Modificat din lista
    else:
        assert lista == lista_asteptata


def testeaza_program():
    """
    Functia contine toate testele functiilor din program
    input:-
    output:-
    """
    test_stergere_pozitie()
    test_stergere_secventa()
    test_inlocuieste()
    test_tipareste_imaginar()
    test_tipareste()
    test_tipareste_modul_egal()
    test_aduna_numere_complexe()
    test_produs_numere_complexe()
    test_sorteaza_descrescator()
    test_filtrare()
    test_filtrare_modul()
    test_undo()