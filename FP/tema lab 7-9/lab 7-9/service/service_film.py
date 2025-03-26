from domain_problem.film_validator import FilmValidator
from domain_problem.films_data import Film

class ServiceFilm:
    """
    Definim layer-ul dintre UI si repository
    """
    def __init__(self,validator:FilmValidator,repository):
        """
        definim principalele atribute ale obiectului
        """
        self.__validator=validator
        self.__repository=repository

    def add(self,title, description,genre):
        """
        Functia se ocupa de adaugarea unui film in repository si de a prinde exceptiile in cazul in care datele nu sunt valide
        input: title,description,genre: informatii necesare pentru crearea unui obicet de tip film
        output: mesaj de eroare sau repository-ul modificat
        """
        film=Film(title,description,genre)
        self.__validator.validate(film)
        self.__repository.add(film)


    def remove_film(self,id_dat):
        """
        Functia sterge un film dupa id daca acesta se afla in lista
        input: id_dat
        output: repository modificat
        """
        self.find_by_id(id_dat)
        self.__repository.remove_film(id_dat)

    def replace(self,id_dat,titlu,descriere,gen):
        """
        Functia inlocuieste un film dupa id daca acesta se afla in lista,altfel afiseaza mesaj de eroare
        input: id_dat,film
        output: repository modificat
        """
        film=Film(titlu,descriere,gen)
        self.__validator.validate(film)
        self.__repository.replace(id_dat,film)

    def get_all(self):
        """
        Functia returneaza toate filmele din repository
        """
        return self.__repository.get_all()

    def get_repo(self):
        """
        Functia returneaza repository-ul
        """
        return self.__repository

    def find_by_id(self,id):
        """
        Functia cauta dupa id un film din repository
        input: id
        output: film
        """
        return self.__repository.find_by_id(id)

    def filtrare(self,gen):
        """
        Functia filtreaza filmele dupa gen
        input: gen
        output: v=o lista de filme cu genul gen, ok care e 0 daca lista e vida, 1 altfel
        """
        v=[]
        for film in self.__repository.get_all():
            if film.get_genre()==gen:
                v.append(film)
        return v

    def filtrare_recursiv(self,gen, lst=None, index=0):
        if lst is None:
            lst = self.__repository.get_all()

        if index >= len(lst):
            return []

        gen_gasit = lst[index].get_genre()
        if gen_gasit == gen:
            return [lst[index]] + self.filtrare_recursiv(gen, lst, index + 1)
        else:
            return self.filtrare_recursiv(gen, lst, index + 1)


