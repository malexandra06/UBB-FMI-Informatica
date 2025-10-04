from exceptions.exceptions import RentAlreadyExistsException, RentDoesNotExistException, RepositoryException,RentReturnedException
from domain_problem.inchiriere import Inchiriere

class RepositoryInchirieri:
    def __init__(self):
        self.__inchirieri = []

    def add(self, inchiriere:Inchiriere):
        """
        Functia adauga o inchiriere in lista
        input: inchiriere= data de tip Inchiriere care trebuie adaugata in lista, obiect de tip InchirieriRepository
        output: lista de inchiriere modificata ce apartine obiectului de tip InchirieriRepository
        """
        if self.find_by_id(inchiriere.get_id_client(),inchiriere.get_id_film())==False:
            inchiriere.inchiriat()
            self.__inchirieri.append(inchiriere)
        else:
            raise RentAlreadyExistsException()

    def remove_inchiriere(self, id_client,id_film):
        if self.find_by_id(id_client,id_film):
            for i in self.get_all():
                if i.get_id_client()==id_client and i.get_id_film()==id_film:
                    self.get_all().remove(i)
        else:
            raise RentDoesNotExistException()

    def get_all(self):
        """
        Functia returneaza lista de inchirieri
        """
        return self.__inchirieri


    def return_film(self,inchiriere):
        """
        Functia gestioneaza returnarea unui film
        """
        ok=0
        returnat=0
        for i in self.get_all():
            if i.get_id_client()==inchiriere.get_id_client() and i.get_id_film()==inchiriere.get_id_film():
                if i.get_inchiriat()==True:
                    i.returnat()
                    ok=1
                else:
                    returnat=1
        if ok==0:
            raise RentDoesNotExistException()
        if returnat==1:
            raise RentReturnedException()

    def find_by_id(self, id_client,id_film):
        """
        Functia cauta in lista o inchiriere dupa id si o returneaza daca o gaseste
        """
        for i in self.__inchirieri:
            if i.get_id_film() == id_film and i.get_id_client() == id_client:
                return True
        return False

class RepoFileInchirieri(RepositoryInchirieri):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        try:
            with open(self.__filename, 'r') as file:
                lines = file.readlines()
                for l in lines:
                    l = l.strip()
                    if l:
                        id_client, id_film,inchiriat = l.split(',')
                        super().add(Inchiriere(int(id_client.strip()), int(id_film.strip()),bool(inchiriat.strip())))
        except IOError:
            raise RepositoryException(f"Nu s-a putut deschide fisierul {self.__filename}")

    def __save_to_file(self):
        try:
            with open(self.__filename, "w") as file:
                for i in super().get_all():
                    # Save with status
                    file.write(f"{i.get_id_client()},{i.get_id_film()},{i.get_inchiriat()}\n")
        except IOError:
            raise RepositoryException(f"Nu s-a putut deschide fisierul {self.__filename}")

    def add(self, inchiriere: Inchiriere):
        super().add(inchiriere)
        self.__save_to_file()

    def remove_inchiriere(self, id_client, id_film):
        super().remove_inchiriere(id_client, id_film)
        self.__save_to_file()

    def return_film(self, inchiriere):
        super().return_film(inchiriere)
        self.__save_to_file()
