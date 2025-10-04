from domain_problem.clients import Client
from exceptions.exceptions import PersonAlreadyExistsException, PersonDoesNotExistException, RepositoryException
import random

class RepositoryClient:
    """
    Am definit clasa ClientManager si metodele necesare pentru a gestiona o lista de clienti
    """
    def __init__(self):
        """
        Definim principalele atribute
        """
        self.__clients = []
        self.id_counter = 1

    def get_all(self):
        """
        Functia returneaza lista de clienti
        input: self: obiect de tip ClientManager
        output: lista de clienti
        """
        return self.__clients

    def add(self, client: Client):
        """
        Functia adauga un client in lista daca este valid, altfel afiseaza erori
        input: client= data de tip Client care trebuie adaugata in lista, obiect de tip ClientManager
        output: lista de clienti modificata ce apartine obiectului de tip ClientManager
        """
        if self.cnp_exist(client.get_cnp()) is None:
            client.set_id(self.id_counter)
            self.__clients.append(client)
            self.id_counter += 1
        else:
            raise PersonAlreadyExistsException()

    def remove_client(self, id_dat):
        """
        Functia sterge un client din lista daca este valid, altfel afiseaza erori
        input: client= data de tip Client care trebuie stersa din lista, obiect de tip ClientManager
        output: lista de clienti modificata ce apartine obiectului de tip ClientManager
        """
        try:
            self.find_by_id(id_dat)
        except PersonDoesNotExistException:
            raise PersonDoesNotExistException()
        self.__clients.remove(self.find_by_id(id_dat))

    def cnp_exist(self,cnp):
        for client in self.get_all():
            if client.get_cnp()==cnp:
                return client
        return None

    def find_by_id(self, id_dat):
        """
        Functia cauta in lista un element dupa id si il returneaza daca il gaseste
        input: self-lista de clienti, id_dat=id-ul clientului pe care dorim sa-l gasim in lista
        output: clientul cu id-ul introdus sau eroare altfel
        """
        """
        Analiza complexitatii: best case: BC=cand primul element din lista de clienti are id-ul pe care il cautam => θ(1)
                               worst case: WC=cand id-ul introdus nu este in lista de clienti => T(n)= n pasi ∈ θ(n)
                               average case: AC=1*1/n+2*1/n+...+n*1/n=(1+2+..+n)/n=n(n+1)/(2n)=(n+1)/2 ∈ θ(n)
        """
        for i in self.__clients:
            if i.get_id() == id_dat:
                return i
        raise PersonDoesNotExistException()

    def replace(self, id_dat, client_nou: Client):
        """
        Functia inlocuieste un client cu un anumit id introdus cu un client nou
        input: self-lista de clienti, id_dat=id-ul celui pe care dorim sa-l inlocuim, client_nou=datele cu care dorim sa inlocuim clientul cu id-ul dat
        output: self-lista modificata
        """
        el=self.find_by_id(id_dat)
        if self.cnp_exist(client_nou.get_cnp()) is None:
            el.set_name(client_nou.get_name())
            el.set_cnp(client_nou.get_cnp())
        else:
            raise PersonAlreadyExistsException()

class RepoFileClient(RepositoryClient):
    def __init__(self,filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        """
        Incarca datele din fisier
        :return: -; datele din fisier sunt incarcate si in memorie
        :raises: RepositoryException daca exista probleme la citirea datelor din fisier
        """
        try:
            with open(self.__filename, 'r') as file:
                lines=file.readlines()
                for l in lines:
                    data=l.split(';')
                    if data:
                        client=Client(data[0].strip(),data[1].strip())
                        super().add(client)
        except IOError:
                 raise RepositoryException(f"Nu s-au putut citi datele din fisierul {self.__filename}")

    def add(self, client: Client):
        #if self.probabilitate() == 0:
            #raise BaseException('Eroare necunoscuta!')
        super().add(client)
        self.__save_to_file()

    def remove_client(self,id_dat):
        #if self.probabilitate() == 0:
            #raise BaseException('Eroare necunoscuta!')
        super().remove_client(id_dat)
        self.__save_to_file()

    def replace(self,id_dat,client_nou: Client):
        #if self.probabilitate() == 0:
            #raise BaseException('Eroare necunoscuta!')
        super().replace(id_dat,client_nou)
        self.__save_to_file()

    def probabilitate(self):
        """
        Probabilitate de a crapa programul de 50%
        :return:
        """
        x=[0,1]
        return random.choice(x)

    def __save_to_file(self):
        """
        Salvam in fisier
        :return:
        """
        try:
            with open(self.__filename, "w") as file:
                filme=super().get_all()
                for f in filme:
                    f_str=f.get_name()+"; "+f.get_cnp()+"\n"
                    file.write(f_str)
        except IOError:
            raise RepositoryException(f"Nu s-au putut salva datele din fisierul {self.__filename}")
