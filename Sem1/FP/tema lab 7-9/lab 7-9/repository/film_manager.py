from exceptions.exceptions import FilmDoesNotExistException,RepositoryException
from domain_problem.films_data import Film

class RepositoryFilm:
    """
    Am definit clasa FilmManager si metodele necesare pentru a gestiona o lista de filme:
    add, get_all, remove,find,replace
    """
    def __init__(self):
        self.__films = []
        self.id_counter = 1

    def add(self,film:Film):
        """
        Functia adauga un film in lista daca este valid, altfel afiseaza erori
        input: film= data de tip Film care trebuie adaugata in lista, obiect de tip FilmManager
        output: lista de filme modificata ce apartine obiectului de tip FilmManager si are la final inserat filmul nou
        """
        film.set_id(self.id_counter)
        self.__films.append(film)
        self.id_counter += 1

    def get_all(self):
        """
        Functia returneaza lista de filme a obiectului de tip FilmManager
        input: self: obiect de tip FilmManager
        output: lista de filme
        """
        return self.__films

    def remove_film(self,id_dat):
        """
        Functia sterge un film din lista in functie de id
        input:id_dat-id-ul celui pe care dorim sa-l stergem
        output: self-lista modificata
        """
        if self.find_by_id(id_dat):
            self.__films.remove(self.find_by_id(id_dat))
        else:
            raise FilmDoesNotExistException()

    def find_by_id(self,id_dat):
        """
        Functia cauta un film in lista de filme in functie de id
        input:self,id_dat=id citit de la tastatura
        output: filmul daca se afla in lista, None altfel
        """
        for i in self.__films:
            if i.get_id()==id_dat:
                return i
        raise FilmDoesNotExistException()

    def replace(self,id_dat,film_nou:Film):
        """
        Functia inlocuieste filmul cu un anumit id din lista cu altul
        input:self,id_dat=id citit de la tastatura, film_nou=film de tip Film cu care inlocuim
        output: lista de filme modificata
        """
        el=self.find_by_id(id_dat)
        el.set_title(film_nou.get_title())
        el.set_type(film_nou.get_genre())
        el.set_description(film_nou.get_description())

class RepoFileFilm(RepositoryFilm):
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
                for line in lines:
                    data=line.split(';')
                    if data:
                        film=Film(data[0].strip(),data[1].strip(),data[2].strip())
                        super().add(film)
        except IOError:
            raise RepositoryException("Nu s-au putut citi datele din fisierul:" + self.__filename)

    def add(self, film:Film):
        super().add(film)
        self.__save_to_file()

    def remove_film(self,id_dat):
        super().remove_film(id_dat)
        self.__save_to_file()

    def replace(self,id_dat,film_nou:Film):
        super().replace(id_dat,film_nou)
        self.__save_to_file()

    def __save_to_file(self):
        """
        Salveaza datele in fisier
        :return: -; fisierul cu numele self.__filename va contine datele in formatul specificat
        :raises: RepositoryException daca exista probleme la scrierea in fisier
        """
        try:
            with open(self.__filename, "w") as file:
                filme = super().get_all()
                for f in filme:
                    f_str = f.get_title() + ";" + f.get_description() + ";" + f.get_genre()
                    f_str += '\n'
                    file.write(f_str)
        except IOError:
            raise RepositoryException("Nu s-au putut salva datele in fisierul " + self.__filename)