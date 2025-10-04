#from films_data import Film
from exceptions.exceptions import InvalidCommand,ValidationException, FilmDoesNotExistException, PersonAlreadyExistsException, \
    PersonDoesNotExistException, RentReturnedException, RentDoesNotExistException
from service.service_client import ServiceClient
from service.service_film import ServiceFilm
from service.service_inchirieri import ServiceInchirieri

class ConsoleFilm:
    """
    Clasa care gestioneaza interactiunea cu utilizatorul a operatiilor privind filmele din repository
    """
    def __init__(self,service_film:ServiceFilm):
        self.service_film=service_film

    @staticmethod
    def print_submenu1():
        """
        Afiseaza operatiile posibile asupra listei de filme
        """
        print("1.1.Adauga")
        print("1.2.Sterge")
        print("1.3.Inlocuieste")
        print("1.4.Afiseaza")
        print("1.5.Filtreaza")
        print("B.Back to main menu")
        print()

    @staticmethod
    def citeste_info_film():
        """
        Functia cere introducerea unor parametri pentru a forma un obiect de tipul Film
        """
        title = input("Introduceti titlu:")
        description = input("Introduceti descrierea filmului:")
        genre = input("Introduceti genul filmului:")
        return title, description, genre


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
        try:
            info = self.citeste_info_film()
            if info is not None:
                title, description, genre = info
                self.service_film.add(title, description, genre)
        except ValueError as ve:
            print(ve)
        except ValidationException as e:
            print(e)

    def remove_film_ui(self):
        """
        Functia sterge un film din repository pe baza id-ului daca este valid
        """
        try:
            id_dat = int(input("Introduceti id-ul filmului pe care doriti sa il stergeti: "))
            self.service_film.remove_film(id_dat)
        except ValueError:
            print("ID invalid!")
        except FilmDoesNotExistException as e:
            print(e)

    def replace_film_ui(self):
        """
        Functia inlocuieste un anumit film cu id dat cu alt obiect de tip film introdus de utilizator
        """
        try:
            id_dat=int(input("Introduceti id-ul filmului pe care doriti sa il inlocuiti: "))
            info = self.citeste_info_film()
            if info is not None:
                title, description, genre = info
                self.service_film.replace(id_dat,title,description,genre)
        except ValueError:
            print("ID invalid!")
        except FilmDoesNotExistException as e:
            print(e)

    def filtrare_ui(self):
        gen=input("Introduceti genul dupa care doriti sa filtrati filmele:")
        lst=None
        v=self.service_film.filtrare_recursiv(gen,lst,0)
        if len(v)>0:
            for i in v:
                print(i)
        else:
            print("Nu exista filme cu genul dat in lista!")

    def edit_film_list(self):
        """
        Functia gestioneaza operatiile asupra repository-ului de filme
        """
        ok = True
        while ok:
            self.print_submenu1()
            option = input("Introduceti numarul operatiei dorite: ")
            print()
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
                case "B":
                    ok = False
                case _:
                    raise InvalidCommand(f"Comanda {option} nu este valida!")

class ConsoleClient:
    """
    Clasa care gestioneaza operatiile asupra repository-ului de clienti
    """
    def __init__(self,service_client:ServiceClient):
        self.service_client=service_client

    @staticmethod
    def print_submenu1():
        """
        Afiseaza operatiile posibile asupra listei de clienti
        """
        print("1.1.Adauga")
        print("1.2.Sterge")
        print("1.3.Inlocuieste")
        print("1.4.Afiseaza")
        print("1.5.Filtreaza")
        print("B.Back to main menu")

    @staticmethod
    def citeste_info_client():
        """
        Functia cere introducerea unor parametri pentru crearea unui obiect de tip client
        """
            #id = int(input("Introduceti id-ul clientului: "))
        name = input("Introduceti numele clientului: ")
        cnp = input("Introduceti CNP-ul clientului:")
        return name, cnp
        #except ValueError:
            #print("ID invalid!")


    def afiseaza_clienti(self):
        """
        Functia afiseaza toti clientii
        """
        print("Lista de clienti:")
        lista = self.service_client.get_all()
        for i in range(len(lista)):
            print(lista[i])

    def adauga_client_ui(self):
        """
        Functia adauga un client in repository daca este valid
        """
        try:
            info=self.citeste_info_client()
            if info is not None:
                name,cnp=info
                self.service_client.add(name,cnp)
        except BaseException as exce:
            print(exce)
        except ValueError as ve:
            print(ve)
        except ValidationException as e:
            print(e)
        except PersonAlreadyExistsException as ex:
            print(ex)

    def remove_client_ui(self,s_inchirieri:ServiceInchirieri):
        """
        Functia sterge un client din repository daca id-ul este valid
        """
        try:
            id_dat = int(input("Introduceti id-ul clientului pe care doriti sa il stergeti: "))
            self.service_client.remove_client(id_dat)
            s_inchirieri.delete_client(id_dat)
        except BaseException as exce:
            print(exce)
        except ValueError:
            print("ID invalid!")
        except PersonDoesNotExistException as e:
            print(e)

    def replace_client_ui(self):
        """
        Functia inlocuieste un client din repository daca este valid
        """
        try:
            id_dat=int(input("Introduceti id-ul clientului pe care doriti sa il inlocuiti: "))
            info = self.citeste_info_client()
            if info is not None:
                name, cnp = info
                self.service_client.replace(id_dat,name,cnp)
        except BaseException as exce:
            print(exce)
        except ValueError:
            print("ID invalid!")
        except ValidationException as ve:
            print(ve)
        except PersonDoesNotExistException as e:
            print(e)
        except PersonAlreadyExistsException as ex:
            print(ex)

    def filtrare_ui(self):
        """
        Functia are rolul de a afisa toti clientii care au acelasi nume cu cel introdus de la tastatura de utilizator
        """
        nume_dat=input("Introduceti numele clientului dupa care doriti sa filtrati lista: ")
        lst=None
        v=self.service_client.filtrare_recursiv(nume_dat,lst,0)
        if len(v)>0:
            for i in v:
                print(i)
        else:
            print("In lista de clienti nu se afla persoane cu numele acesta.")

    def edit_client_list(self,s_inchirieri:ServiceInchirieri):
        """
        Functia gestioneaza operatiile asupra repository-ului de clienti
        """
        ok = True
        while ok:
            self.print_submenu1()
            option = input("Introduceti numarul operatiei dorite: ")
            print()
            match option.strip():
                case "1.1":
                    self.adauga_client_ui()
                case "1.2":
                    self.remove_client_ui(s_inchirieri)
                case "1.3":
                    self.replace_client_ui()
                case "1.4":
                    self.afiseaza_clienti()
                case "1.5":
                    self.filtrare_ui()
                case "B":
                    ok = False
                case _:
                    raise InvalidCommand(f"Comanda {option} nu este valida!")

class Console:
    """
    Clasa care gestioneaza operatiile generale, precum si relatia dintre Clienti si Filme
    """
    def __init__(self, service_film,client_manager,s_inchirieri:ServiceInchirieri):
        self.film_console = ConsoleFilm(service_film)
        self.client_console=ConsoleClient(client_manager)
        self.s_inchirieri=s_inchirieri

    @staticmethod
    def print_menu():
        """
        Afiseaza meniul principal
        """
        print("1.Operatii pe listele de filme/clienti")
        print("2.Inchirieri/Returnari filme")
        print("3.Rapoarte")
        print("E.Exit")
        print()

    @staticmethod
    def print_submenu2():
        """
        Alegerea listei pe care dorim sa o modificam
        """
        print("F.Lista de filme")
        print("C.Lista de clienti")
        print("B.Back")
        print()

    def case_1(self):
        """
        Functia gestioneaza operatiile introduse asupra listei de filme si de clienti
        """
        ok = True
        while ok:
            self.print_submenu2()
            option_1 = input("Introduceti optiunea dorita: ")
            if option_1.strip() == "F":
                ok1=True
                while ok1:
                    try:
                        ok1=self.film_console.edit_film_list()
                    except InvalidCommand as e:
                        print(e)
            elif option_1.strip() == "C":
                ok1 = True
                while ok1:
                    try:
                        ok1=self.client_console.edit_client_list(self.s_inchirieri)
                    except InvalidCommand as e:
                        print(e)
            elif option_1.strip() == "B":
                ok = False
            else:
                raise InvalidCommand(f"Comanda {option_1} nu este valida!")

    def case_2(self):
        """
        Functia gestioneaza operatiile legate de inchirieri si returnari
        """
        ok = True
        while ok:
            print("I.Inchiriere")
            print("R.Returnare")
            print("D.Sterge inchiriere")
            print("A.Afisare inchirieri")
            print("B.Back")
            option_1 = input("Introduceti optiunea dorita: ")
            if option_1.strip() == "I":
                try:
                    id_c=int(input("Introduceti id-ul clientului: "))
                    id_f=int(input("Introduceti id-ul filmului: "))
                    inchiriat=input("Introduceti starea filmului: (Inchiriat=True sau Neinchiriat=False) :")
                    self.s_inchirieri.add(id_c, id_f,inchiriat)
                except ValueError:
                    print("ID invalid!")
                except ValidationException as ve:
                    print(ve)

            elif option_1.strip() == "R":
                try:
                    id_c=int(input("Introduceti id-ul clientului care returneaza filmul: "))
                    id_f=int(input("Introduceti id-ul filmului pe care il returneaza: "))
                    self.s_inchirieri.return_film(id_c,id_f)
                except ValueError:
                    print("ID invalid!")
                except RentReturnedException as ve:
                    print(ve)
                except RentDoesNotExistException as v:
                    print(v)

            elif option_1.strip() == "A":
                for i in self.s_inchirieri.get_all():
                    print(i)
            elif option_1.strip() == "D":
                try:
                    print("Introduceti datele inchirieii pe care doriti sa o stergeti:")
                    id_client=int(input("Introduceti id-ul clientului: "))
                    id_film=int(input("Introduceti id-ul filmului: "))
                    self.s_inchirieri.remove_inchiriere(id_client, id_film)
                except ValueError:
                    print("ID invalid!")
                except RentDoesNotExistException as v:
                    print(v)
            elif option_1.strip() == "B":
                ok = False
            else:
                raise InvalidCommand(f"Comanda {option_1} nu este valida!")

    def raport_film_ui(self):
        """
        Functia va afisa titlurile filmelor si numarul de vizionari de la cele mai vizionate la cele mai putin vizionate
        """
        lista=self.s_inchirieri.cele_mai_inchiriate_filme()
        for i in lista:
            print(i)


    def raport_client_by_nr_ui(self):
        """
        Functia va afisa o lista de clienti care au inchiriat filme ordonata dupa numarul de filme inchiriate
        """
        lista=self.s_inchirieri.clienti_inchirieri()
        lista.sort(key=lambda x:x.get_nr(),reverse=True)
        for i in lista:
            print(i)

    def top_30(self):
        """
        Functia va afisa primii 30% clienti cu cele mai multe inchirieri
        """
        lista=self.s_inchirieri.top_30()
        for i in lista:
            print(i)

    def top5(self):
        """
        Functia va afisa primele 5 genuri cele mai inchiriate
        """
        lista=self.s_inchirieri.top_5_gen()
        for i in lista:
            print(i)

    def run(self):
        """
        Functia gestioneaza la modul general fiecare optiune introdusa de utilizator
        """
        ok=True
        while ok:
            self.print_menu()
            option=input("Introduceti optiunea dorita: ")
            match option.strip():
                case "1":
                    ok1=True
                    while ok1:
                        try:
                            ok1=self.case_1()
                        except InvalidCommand as e:
                            print(e)
                case "2":
                    ok1 = True
                    while ok1:
                        try:
                            ok1=self.case_2()
                        except InvalidCommand as e:
                            print(e)
                case "3":
                    ok2=True
                    while ok2:
                        print("1.Raport clienti cu filme închiriate ordonat dupa numarul de filme inchiriate")
                        print("2.Raport filme inchiriate")
                        print("3.Raport top 30% clienti cu cele mai multe filme")
                        print("4.Raport top 5 cele mai inchiriate genuri de filme")
                        print("B.Back")
                        option_2=input("Introduceti optiunea dorita: ")
                        match option_2.strip():
                            case "1":
                                self.raport_client_by_nr_ui()
                            case "2":
                                self.raport_film_ui()
                            case "3":
                                self.top_30()
                            case '4':
                                self.top5()
                            case "B":
                                ok2=False
                            case _:
                                raise InvalidCommand(f"Comanda {option_2} nu este valida!")
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