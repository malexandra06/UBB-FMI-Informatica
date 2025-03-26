class NUMAR_COMPLEX:
    # Un numar complex are partea reala si partea imaginara
    def __init__(self, real: int, imaginar: int):
        self.__real = int(real)
        self.__imaginar = int(imaginar)

    def __str__(self):
        # Am optat pentru o afisare de tipul a+bi a acestor numere
        if self.__real == 0:
            return f"{self.__imaginar}i"
        elif self.__imaginar == 0:
            return f"{self.__real}"
        elif self.__imaginar == 1:
            return f"{self.__real}+i"
        elif self.__imaginar == -1:
            return f"{self.__real}-i"
        elif self.__imaginar > 0:
            return f"{self.__real}+{self.__imaginar}i"
        else:  # self.__imaginar < 0
            return f"{self.__real}{self.__imaginar}i"

    def get_real(self):
        """
        Functia acceseaza partea reala unui numar complex
        input: self=numar complex
        output: partea sa reala
        """
        return self.__real

    def get_imaginar(self):
        """
        Functia acceseaza partea imaginara unui numar complex
        input: self=numar complex
        output: partea sa imaginara
        """
        return self.__imaginar

    def __eq__(self, other):
        """
        Functia determina daca 2 numere complexe sunt egale
        input: self, other doua numere complexe
        output: true daca numerele sunt egale sau false
        """
        if not isinstance(other, NUMAR_COMPLEX):
            return False
        return self.__real == other.__real and self.__imaginar == other.__imaginar

    def __add__(self, other):
        """
        Functia determina adunarea 2 numere complexe
        input: self, other doua numere complexe
        output: rezultatul adunarii lor de tip NUMAR_COMPLEX
        """
        rezultat = NUMAR_COMPLEX(0, 0)
        rezultat.__real = self.__real + other.__real
        rezultat.__imaginar = self.__imaginar + other.__imaginar
        return rezultat

    def __mul__(self, other):
        """
        Functia determina produsul 2 numere complexe
        input: self, other doua numere complexe
        output: rezultatul produsului lor de tip NUMAR_COMPLEX
        """
        rezultat = NUMAR_COMPLEX(0, 0)
        rezultat.__real = self.__real * other.__real - self.__imaginar * other.__imaginar
        rezultat.__imaginar = self.__imaginar * other.__real + self.__real * other.__imaginar
        return rezultat

    def calculeaza_modul(self):
        """
        Se calculeaza modulul numarului complex
        input: numarul complex
        output: modul de tip float
        """
        modul = self.__real * self.__real + self.__imaginar * self.__imaginar
        modul = modul ** 0.5
        return modul


def citire_complex():
    """
    Functia citeste partea intreaga si partea imaginara a unui numar complex
    input: -
    output: un numar complex de tipul a+bi
    """
    try:
        a = int(input("a="))
        b = int(input("b="))
    except ValueError:
        print("Introduceti numere intregi pentru a si b!")
        return None

    return NUMAR_COMPLEX(a, b)
