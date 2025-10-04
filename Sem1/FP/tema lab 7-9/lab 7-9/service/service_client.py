from domain_problem.client_validator import ClientValidator
from domain_problem.clients import Client

class ServiceClient:
    """
    layer-ul dintre repository si interactiunea cu utilizatorul
    """
    def __init__(self,validator:ClientValidator,repository):
        """
        Am definit atributele necesare: repository: cum retinem datele si validator care valideaza datele introduse
        """
        self.__validator=validator
        self.__repository=repository

    def add(self,name,cnp):
        """
        Adauga un client nou in repository altfel arunca exceptie(daca aceste se afla deja)
        input: self, id,name,cnp=date pentru a crea obiect de tip Client
        output: repository modificat
        """
        client=Client(name,cnp)
        self.__validator.validate(client)
        self.__repository.add(client)


    def remove_client(self,id_dat):
        """
        Sterge un client din lista cu id-ul introdus, iar in cazul in care nu se afla in lista arunca eroare
        input: self, id_dat
        output: repository modificat
        """
        self.find_by_id(id_dat)
        self.__repository.remove_client(id_dat)

    def get_all(self):
        """
        returneaza toate obiectele din repository
        """
        return self.__repository.get_all()

    def get_repo(self):
        """
        returneaza repository-ul
        """
        return self.__repository


    def find_by_id(self,id):
        """
        returneaza obiectul de tip Client care are id-ul introdus,altfel afiseaza eroare
        """
        return self.__repository.find_by_id(id)

    def replace(self,id_dat,name,cnp):
        """
        Inlocuieste un client care are un anumit id cu altul introdus de utilizator
        input: self, id_dat=id-ul clientului pe care dorim sa-l inlocuim ; name,cnp=date pentru a crea obiect nou de tip Client
        output: repository modificat
        """
        client=Client(name,cnp)
        self.__validator.validate(client)
        self.__repository.replace(id_dat,client)

    def filtrare(self,nume):
        """
        Functia returneaza toti clientii din lista de clienti care au numele la fel
        input: nume: parametru dupa care se face filtrarea
        output: o lista de clienti, v care contine lista de clienti care au acelasi nume
        """
        v=[]
        for client in self.__repository.get_all():
            nume_c=client.get_name()
            nume_c=nume_c.split(' ')
            if nume_c[0]==nume:
                v.append(client)
        return v

    def filtrare_recursiv(self, nume, lst=None, index=0):
        """
        Funcție recursivă care filtrează clienții după nume.
        Input:
            - nume: șir de caractere (nume după care se face filtrarea)
            - lst: lista de clienți (implicit întreaga listă de clienți)
            - index: poziția curentă în listă pentru recursivitate
        Output:
            - lista cu clienți care au același nume
        """
        # Inițializează lista la primul apel
        if lst is None:
            lst = self.__repository.get_all()

        # Condiția de oprire: am parcurs toți clienții
        if index >= len(lst):
            return []

        # Verificăm dacă numele clientului de la poziția curentă corespunde
        nume_c = lst[index].get_name().split(' ')
        if nume_c[0] == nume:
            # Adaugă clientul în rezultat și continuă recursiv
            return [lst[index]] + self.filtrare_recursiv(nume, lst, index + 1)
        else:
            # Continuă recursiv fără a adăuga clientul
            return self.filtrare_recursiv(nume, lst, index + 1)


