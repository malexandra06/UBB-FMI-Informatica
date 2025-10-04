class ReportFilm:
    """
    Clasa de tip RaportFilm care retine titlul unui film si numarul de inchirieri
    """
    def __init__(self,titlu,nr):
        self.__titlu=titlu
        self.__nr=nr

    def get_nr(self):
        """
        Accesarea numarului de inchirieri unui film
        """
        return self.__nr

    def get_title(self):
        """
        Accesarea titlului unui film
        """
        return self.__titlu

    def set_nr(self,nr):
        """
        Setarea numarului de inchirieri
        """
        self.__nr=nr

    def __str__(self):
        """
        Decidem cum afisam un obiect de tip RaportFilm
        """
        return f"Filmul {self.get_title()} a fost vizionat de {self.get_nr()} ori!"

    def __eq__(self, other):
        """
        Ce inseamna sa fie egale doua obiecte de tip RaportFilm
        """
        return self.get_title()==other.get_title() and self.get_nr()==other.get_nr()


class ReportClient:
    """
    Clasa de obiecte de tip ReportClient
    """
    def __init__(self,nume,nr):
        self.__nume=nume
        self.__nr=nr

    def __str__(self):
        """
        Decidem cum afisam un obiect de tip ReportClient
        """
        return f"Clientul {self.get_name()} a vizionat un numar de {self.get_nr()} filme!"

    def get_nr(self):
        """
        Accesarea numarului de filme vizionate de un client
        """
        return self.__nr

    def get_name(self):
        """
        Accesarea numelui unui client
        """
        return self.__nume

    def set_nr(self,nr):
        """
        Setarea numarului de filme vizionate de un client
        """
        self.__nr=nr

    def __eq__(self, other):
        """
        Decidem ce inseamna sa fie egale doua obiecte de tip ReportClient
        """
        return self.get_name()==other.get_name() and self.get_nr()==other.get_nr()


class ReportGen:
    def __init__(self,gen,nr):
        self.__gen=gen
        self.__nr=nr

    def get_nr(self):
        """
        Accesarea numarului de inchirieri unui gen
        """
        return self.__nr

    def get_gen(self):
        """
        Accesarea genului
        """
        return self.__gen

    def set_nr(self,nr):
        """
        Setarea numarului de inchirieri unui gen
        """
        self.__nr=nr

    def set_gen(self,gen):
        """
        Setarea genului
        """
        self.__gen=gen

    def __str__(self):
        """
        Cum se afiseaza un obiect de tip ReportGen
        """
        return f"Genul {self.get_gen()} a fost inchiriat de {self.get_nr()} ori!"

    def __eq__(self, other):
        if isinstance(other, ReportGen):
            return self.get_gen()==other.get_gen() and self.get_nr()==other.get_nr()
        return False