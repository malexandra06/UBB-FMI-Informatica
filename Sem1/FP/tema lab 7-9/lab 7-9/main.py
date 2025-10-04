
from repository.inchirieri_manager import RepoFileInchirieri
from ui.console import *
from teste_domain.test_creare_inchiriere import *
from domain_problem.client_validator import ClientValidator
from domain_problem.film_validator import FilmValidator
from repository.client_manager import RepoFileClient
from repository.film_manager import RepoFileFilm
from domain_problem.inchiriere_validator import InchiriereValidator

def main():
    """
    Functia principala a programului
    """
    validator1=FilmValidator()
    film_manager=RepoFileFilm('data/filme.txt')
    service_f=ServiceFilm(validator1,film_manager)
    validator2 = ClientValidator()
    client_manager=RepoFileClient('data/clienti.txt')
    service_c = ServiceClient(validator2, client_manager)
    validator3=InchiriereValidator()
    inchiriere=RepoFileInchirieri('data/inchirieri.txt')
    s_inchirieri=ServiceInchirieri(inchiriere,service_f.get_repo(),service_c.get_repo(),validator3)
    console = Console(service_f,service_c,s_inchirieri)
    console.start()

if __name__=="__main__":
    main()
    unittest.main()
