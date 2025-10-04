from numar_complex import*
from functii_auxiliare import copy_lista, verifica_prim, compara

class NumberRepository:
    """
    Clasa pentru stocarea datelor de tip NUMAR_COMPLEX.
    Permite folosirea unei 'baze de date' cu numere complexe la cel mai de jos nivel și implementează operațiile de
    tip CRUD (Create, Read, Update, Delete).
    """

    def __init__(self):
        self.__numbers = []
        self.__undo = []

    def add_number(self, nr):
        self.__undo.append(copy_lista(self.__numbers))
        self.__numbers.append(nr)

    def add_number_poz(self, nr, poz: int):
        """
        Adaugă un număr complex pe o poziție dată în listă.
        """
        self.__undo.append(copy_lista(self.__numbers))
        self.__numbers.insert(poz, nr)

    def get_all_numbers(self):
        return self.__numbers

    def remove_p(self, poz):
        """
        Functia sterge un numar de pe o pozitie data
        input: lista= self de numere complexe, poz=pozitia elementului care va fi sters
        output: lista modificata
        """
        self.__undo.append(copy_lista(self.__numbers))
        self.__numbers.pop(poz)

    def remove_secv(self, p1: int, p2: int):
        """
        Functia sterge o secventa de numere din lista
        input: self= lista de numere complexe, p1=pozitia de unde incepe stergerea
               p2=pozitia unde se va incheia stergerea
        output: lista modificata
        """
        self.__undo.append(copy_lista(self.__numbers))
        del self.__numbers[p1:p2 + 1]

    def replace(self, nr1: NUMAR_COMPLEX, nr2: NUMAR_COMPLEX):
        """
        Functia inlocuieste aparitiile unui numar in lista cu alt numar
        input: self= lista de numere complexe, nr1=numarul care va fi cautat pentru a fi inlocuit
               nr2=numarul cu care se vor inlocui aparitiile numarului nr1
        output: lista modificata
        """
        self.__undo.append(copy_lista(self.__numbers))
        for i in range(len(self.__numbers)):
            if self.__numbers[i] == nr1:
                self.__numbers[i] = nr2

    def tipareste_imaginar(self, p1: int, p2: int):
        """
        Functia retine partea imaginara a numerelor dintr-o secventa data
        input: self=lista de numere, p1=inceputul secventei, p2=sfarsitul secventei
        output: secv retine doar partea imaginara a numerelor din secventa data (lista)
        """
        secv = [self.__numbers[i].get_imaginar() for i in range(p1, p2 + 1)]
        return secv

    def tipareste(self):
        """
        Functia retine numerele din lista care au modulul mai mic decat 10
        input:self=lista de numere complexe
        output: secv=retine doar numerele cu modul mai mic decat 10 (lista)
        """
        return [num for num in self.__numbers if num.calculeaza_modul() < 10]

    def tipareste_modul_egal(self):
        """
        Functia retine numerele din lista care au modulul mai mic decat 10
        input:self=lista de numere
        output: secv=retine doar numerele cu modul mai mic decat 10 (lista)
        """
        return [num for num in self.__numbers if num.calculeaza_modul() == 10]

    def aduna_numere_complexe(self, p1: int, p2: int):
        """
        Adună numerele complexe dintr-o secvență dată.
        input: self= lista, p1 si p2 indecsii secventei din lista
        output: s=suma
        """
        s = NUMAR_COMPLEX(0, 0)
        for i in range(p1, p2 + 1):
            s = s + self.__numbers[i]
        return s

    def produs_numere_complexe(self, p1: int, p2: int):
        """
        Determină produsul numerelor complexe dintr-o secvență dată.
        input:self= lista de numere complexe, p1 si p2 indecsii secventei din lista
        output: p=produsul numerelor complexe din secventa
        """
        p = NUMAR_COMPLEX(self.__numbers[p1].get_real(), self.__numbers[p1].get_imaginar())
        for i in range(p1 + 1, p2 + 1):
            p = p * self.__numbers[i]
        return p

    def sorteaza_descrescator(self):
        """
        Sortează lista descrescător după partea imaginară a numerelor.
        input: self=lista de numere complexe
        output: lista_noua= lista sortata insa cea initiala ramane nemodificata
        """
        lista_noua = copy_lista(self.__numbers)
        return sorted(lista_noua, key=lambda x: x.get_imaginar(), reverse=True)

    def filtrare_parte_reala_prim(self):
        """
        Elimină numerele complexe a căror parte reală este un număr prim.
        input: self=lista de numere complexe
        output: lista_noua= lista filtrata insa cea initiala ramane nemodificata
        """
        lista_noua = copy_lista(self.__numbers)
        return [num for num in lista_noua if not verifica_prim(num)]

    def filtrare_modul(self, nr: NUMAR_COMPLEX, operand: str):
        """
        Elimină numerele complexe care sunt <, = sau > decât modulul unui număr citit de la tastatură.
        input: self=lista de numere complexe
        output: lista_noua= lista filtrata insa cea initiala ramane nemodificata
        """
        lista_noua = copy_lista(self.__numbers)
        return [num for num in lista_noua if not compara(num, nr, operand)]

    def set_numbers(self, numbers: list):
        """
        Functia seteaza lista de numere complexe la una data
        input: self, numbers=lista de numere complexe cu care se va initializa self
        output: se modifica self.__numbers
        """
        self.__numbers = copy_lista(numbers)

    def undo(self):
        """Revine la ultima stare salvată dacă există."""
        if self.__undo:
            last_state = self.__undo.pop()
            self.set_numbers(last_state)
        else:
            raise Exception("Nu există nicio operațiune anterioară pentru undo.")
