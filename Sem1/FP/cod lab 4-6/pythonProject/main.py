from ui.consola import ConsoleUI
from testare_lista.test_list import testeaza_program
from service.service_numbers import *
from domain.validare_numar import *
from repository.number_repository_dict import *

def main():
    """
    Functia principala a programului
    input:-
    output:-
    """
    repo = NumberRepositoryDict()
    validator = NumberValidator()
    service = Service(repo, validator)
    ui = ConsoleUI(service)
    ui.run()
    testeaza_program()
    #ConsoleUI.run()

if __name__ == '__main__':
    main()
