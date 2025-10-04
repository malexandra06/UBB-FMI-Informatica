from generare import genereaza_titlu, genereaza_descriere, genereaza_gen, genereaza_nume, genereaza_cnp
from service_client import ServiceClient
from utils.auxiliary import InvalidCommand
from service.service_film import ServiceFilm

class ConsoleFilm:
    """
    Clasa care gestioneaza interactiunea cu utilizatorul a operatiilor privind filmele din repository
    """
    def __init__(self,service_film:ServiceFilm):
        self.service_film=service_film

    def afiseaza_filme(self):
        """
        Programul afiseaza lista de filme
        """
        print("Lista de filme:")
        for i in self.service_film.get_all():
            print(i)

    def adauga_film_ui(self):
        """
        Functia adauga un film in repository daca este valid
        """
        title=genereaza_titlu()
        description=genereaza_descriere()
        genre=genereaza_gen()
        self.service_film.add(title, description, genre)

    def remove_film_ui(self):
        """
        Functia sterge un film din repository pe baza id-ului daca este valid
        """
        try:
            id_dat = int(input("Introduceti id-ul filmului pe care doriti sa il stergeti: "))
            self.service_film.remove_film(id_dat)
        except ValueError :
            print("ID invalid!")

    def replace_film_ui(self):
        """
        Functia inlocuieste un anumit film cu id dat cu alt obiect de tip film introdus de utilizator
        """
        try:
            id_dat=int(input("Introduceti id-ul filmului pe care doriti sa il inlocuiti: "))
            title=genereaza_titlu()
            description=genereaza_descriere()
            genre=genereaza_gen()
            self.service_film.replace(id_dat,title,description,genre)
        except ValueError:
            print("ID invalid!")

    def filtrare_ui(self):
        gen=input("Introduceti genul dupa care doriti sa filtrati filmele:")
        v,ok=self.service_film.filtrare(gen)
        if ok==1:
            for i in v:
                print(i)
        else:
            print("Nu exista filme cu genul dat in lista!")

    def edit_film_list(self,option):
        """
        Functia gestioneaza operatiile asupra repository-ului de filme
        """
        match option.strip():
            case "1.1":
                self.adauga_film_ui()
            case "1.2":
                self.remove_film_ui()
            case "1.3":
                self.replace_film_ui()
            case "1.4":
                self.afiseaza_filme()
            case "1.5":
                self.filtrare_ui()
            case _:
                raise InvalidCommand(f"Comanda {option} nu este valida!")

class ConsoleClient:
    """
    Clasa care gestioneaza operatiile asupra repository-ului de clienti
    """
    def __init__(self,service_client:ServiceClient):
        self.service_client=service_client


    def afiseaza_clienti(self):
        """
        Functia afiseaza toti clientii
        """
        print("Lista de clienti:")
        lista = self.service_client.get_all()
        for i in lista:
            print(i)

    def adauga_client_ui(self):
        """
        Functia adauga un client in repository daca este valid
        """
        nume=genereaza_nume()
        cnp=genereaza_cnp()
        self.service_client.add(nume,cnp)

    def remove_client_ui(self):
        """
        Functia sterge un client din repository daca id-ul este valid
        """
        try:
            id_dat = int(input("Introduceti id-ul clientului pe care doriti sa il stergeti: "))
            self.service_client.remove_client(id_dat)
        except ValueError:
            print("ID invalid!")
        except BaseException as e:
            print(e)

    def replace_client_ui(self):
        """
        Functia inlocuieste un client din repository daca este valid
        """
        try:
            id_dat=int(input("Introduceti id-ul clientului pe care doriti sa il inlocuiti: "))
            name=genereaza_nume()
            cnp=genereaza_cnp()
            self.service_client.replace(id_dat,name,cnp)
        except ValueError:
            print("ID invalid!")

    def filtrare_ui(self):
        nume_dat=input("Introduceti numele clientului dupa care doriti sa filtrati lista: ")
        v,ok=self.service_client.filtrare(nume_dat)
        if ok==1:
            for i in v:
                print(i)
        else:
            print("In lista de clienti nu se afla persoane cu numele acesta.")

    def edit_client_list(self,option):
        """
        Functia gestioneaza operatiile asupra repository-ului de clienti
        """
        match option.strip():
            case "2.1":
                self.adauga_client_ui()
            case "2.2":
                self.remove_client_ui()
            case "2.3":
                self.replace_client_ui()
            case "2.4":
                self.afiseaza_clienti()
            case "2.5":
                self.filtrare_ui()
            case _:
                raise InvalidCommand(f"Comanda {option} nu este valida!")

class Console:
    """
    Clasa care gestioneaza operatiile generale, precum si relatia dintre Clienti si Filme
    """
    def __init__(self, service_film,client_manager):
        self.film_console = ConsoleFilm(service_film)
        self.client_console=ConsoleClient(client_manager)

    @staticmethod
    def print_menu():
        """
        Afiseaza meniul principal
        """
        print("Operatii asupra listei de filme:")
        print("     1.1.Adauga filme  1.2.Sterge filme  1.3.Inlocuieste filme  1.4.Afiseaza filme  1.5.Filtreaza filme")
        print("Operatii asupra listei de clienti:")
        print("     2.1.Adauga clienti   2.2.Sterge clienti   2.3.Inlocuieste clienti   2.4.Afiseaza clienti   2.5.Filtreaza clienti")
        print("E.Exit")
        print()

    def run(self):
        """
        Functia gestioneaza la modul general fiecare optiune introdusa de utilizator
        """
        ok=True
        while ok:
            self.print_menu()
            option=input("Introduceti optiunea dorita: ")
            match option.strip():
                case "1.1"| "1.2" | "1.3" | "1.4" | "1.5":
                    try:
                        self.film_console.edit_film_list(option)
                    except InvalidCommand as e:
                        print(e)
                case "2.1" | "2.2" | "2.3" | "2.4" | "2.5":
                    try:
                        self.client_console.edit_client_list(option)
                    except InvalidCommand as e:
                        print(e)
                case "E":
                    print("Programul s-a incheiat cu succes!")
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option} nu este valida!")

    def start(self):
        """
        Functia care ruleaza programul
        """
        ok=True
        while ok:
            try:
                ok=self.run()
            except InvalidCommand as e:
                print(e)