from generari_random.consola_noua import *
from tests.teste_filme import *
from tests.teste_clienti import *
from tests.teste_inchiriere import *
from client_validator import ClientValidator


def main():
    """
    Functia principala a programului
    (main secundar)
    """
    validator1=FilmValidator()
    film_manager=RepositoryFilm()
    service_f=ServiceFilm(validator1,film_manager)
    client_manager=RepositoryClient()
    validator2=ClientValidator()
    service_c=ServiceClient(validator2,client_manager)
    console = Console(service_f,service_c)
    console.start()

if __name__=="__main__":
    main()
