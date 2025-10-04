from numar_complex import NUMAR_COMPLEX
from functii_auxiliare import copy_dict, compara, verifica_prim


class NumberRepositoryDict:
    """
    clasa pentru stocarea datelor de tip NUMAR_COMPLEX
    similar ca NumberRepository, doar ca foloseste dictionar in loc de lista ca metoda de stocare interna
    """

    def __init__(self):
        self.__numbers = {}
        self.__undo = []

    def add_number(self, nr:NUMAR_COMPLEX):
        """
        Functia adauga la sfarsit un numar complex in dictionar
        input: self=dictionar in care se va introduce numarul, nr= numarul complex care se va adauga
        output: dictionar modificat
        """
        self.__undo.append(copy_dict(self.__numbers))
        self.__numbers[len(self.__numbers)] = nr

    def add_number_poz(self, nr: NUMAR_COMPLEX, poz: int):
        """
        Functia adauga pe o pozitie data un numar complex in dictionar
        input: self=dictionar in care se va introduce numarul, nr= numarul complex care se va adauga,
                       pozitie=pozitia pe care se va introduce numarul nr in dictionar
        output: dictionarul modificat
        """
        self.__undo.append(copy_dict(self.__numbers))
        new_numbers = {}
        idx=0
        n=len(self.__numbers)
        while idx<n:
            if idx<poz:
                new_numbers[idx]=self.__numbers[idx]
            elif idx==poz:
                new_numbers[idx]=nr
                n+=1
            else:
                new_numbers[idx]=self.__numbers[idx-1]
            idx+=1
        self.__numbers = new_numbers

    def get_all_numbers(self):
        """
        Functia returneaza valorile din dictionar
        input: self=dictionarul de numere complexe
        output: lista cu valorile din dictionar
        """
        return list(self.__numbers.values())

    def remove_p(self, poz: int):
        """
        Functia sterge un numar de pe o pozitie data
        input: self= dictionarul de numere complexe, poz=pozitia elementului care va fi sters
        output: dictionarul modificat
        """
        self.__undo.append(copy_dict(self.__numbers))
        new_numbers = {}
        for idx in range(len(self.__numbers)):
            if idx < poz:
                new_numbers[idx] = self.__numbers[idx]
            elif idx > poz:
                new_numbers[idx - 1] = self.__numbers[idx]  # Deplasează elementele după ștergere
        if poz in self.__numbers:
            del self.__numbers[poz]  # Șterge elementul specific
        self.__numbers = new_numbers

    def remove_secv(self,p1:int,p2:int):
        """
        Functia sterge o secventa de numere din dictionar
        input: self= dictionarul de numere complexe, p1=pozitia de unde incepe stergerea
               p2=pozitia unde se va incheia stergerea
        output: dictionarul modificat
        """
        self.__undo.append(copy_dict(self.__numbers))
        new_numbers = {}
        for i in range(len(self.__numbers)):
            if i < p1 or i > p2:
                new_numbers[len(new_numbers)] = self.__numbers[i]
        self.__numbers = new_numbers

    def replace(self, nr1: NUMAR_COMPLEX, nr2: NUMAR_COMPLEX):
        """
        Functia inlocuieste aparitiile unui numar in lista cu alt numar
        input: self= dictionarul de numere complexe, nr1=numarul care va fi cautat pentru a fi inlocuit
               nr2=numarul cu care se vor inlocui aparitiile numarului nr1
        output: dictionarul modificat
        """
        self.__undo.append(copy_dict(self.__numbers))
        for key in self.__numbers:
            if self.__numbers[key] == nr1:
                self.__numbers[key] = nr2

    def tipareste_imaginar(self, p1: int, p2: int):
        """
        Functia retine partea imaginara a numerelor dintr-o secventa data
        input: self=dictionarul de numere, p1=inceputul secventei, p2=sfarsitul secventei
        output: secv retine doar partea imaginara a numerelor din secventa data (lista)
        """
        if p1 < 0 or p2 >= len(self.__numbers) or p1 > p2:
            raise IndexError("Indecși invalizi pentru secvența dată.")

        secv = []
        for key in range(p1, p2 + 1):
            if key in self.__numbers:
                secv.append(self.__numbers[key].get_imaginar())
        return secv

    def tipareste(self):
        """
        Functia retine numerele din lista care au modulul mai mic decat 10
        input:self=dictionarul de numere
        output: secv=retine doar numerele cu modul mai mic decat 10 (lista)
        """
        secv=[]
        for i in range(len(self.__numbers)):
            if self.__numbers[i].calculeaza_modul()<10:
                secv.append(NUMAR_COMPLEX(self.__numbers[i].get_real(),self.__numbers[i].get_imaginar()))
        return secv

    def tipareste_modul_egal(self):
        """
        Functia retine numerele din lista care au modulul mai mic decat 10
        input:self=dictionar de numere
        output: secv=retine doar numerele cu modul mai mic decat 10 (lista)
        """
        secv=[]
        for i in range(len(self.__numbers)):
            if self.__numbers[i].calculeaza_modul()==10:
                secv.append(NUMAR_COMPLEX(self.__numbers[i].get_real(),self.__numbers[i].get_imaginar()))
        return secv

    def aduna_numere_complexe(self,p1: int,p2: int):
        """
        Adună numerele complexe dintr-o secvență dată.
        input: self= dictionar, p1 si p2 cheile secventei din dictionar
        output: s=suma
        """
        s=NUMAR_COMPLEX(0,0)
        for i in range(p1,p2+1):
            s=s+self.__numbers[i]
        return s

    def produs_numere_complexe(self,p1: int,p2: int):
        """
        Functia determina produsul numerelor complexe dintr-o secventa data
        input:self= dictionarul de numere complexe, p1 si p2=cheile secventei din dictionar
        output: p=variabila de tip NUMAR_COMPLEX care retine produsul numerelor complexe din secventa
        """
        p=self.__numbers[p1]
        for i in range(p1+1,p2+1):
            p=p*self.__numbers[i]
        return p

    def sorteaza_descrescator(self):
        """
        Functia creează și returnează un nou dicționar sortat descrescător
        după partea imaginară a numerelor complexe.
        """
        # Sortează perechile cheie-valoare după partea imaginară a valorii
        dict_nou=copy_dict(self.__numbers)
        dict1={}
        idx=0
        dict_nou = dict(sorted(dict_nou.items(), key=lambda item: item[1].get_imaginar(), reverse=True))
        for value in dict_nou:
            dict1[idx]=dict_nou[value]
            idx+=1
        return dict1

    def filtrare_parte_reala_prim(self):
        """
        Functia elimina din dictionarul de numere complexe acele numere a caror parte reala este un numar prim
        input:self=dictionar de numere complexe
        output: dict_nou=dictionar nou, copie a celui veche insa care retine doar valorile cerute
        """
        dict_nou = {}
        i=0
        idx=0
        while i<len(self.__numbers):
            if verifica_prim(self.__numbers[i])==False:
                dict_nou[idx]=self.__numbers[i]
                idx+=1
            i+=1
        return dict_nou

    def filtrare_modul(self,nr:NUMAR_COMPLEX,operand:str):
        """
        Functia elimina din dictionarul numerele complexe care sunt <,= sau > decat modulul unui numar citit de la tastatura
        input: self=dictionar de numere complexe
        output: un dictionar nou, copie a celui veche insa care retine doar valorile cerute
        """
        dict_nou = {}
        i=0
        idx=0
        while i<len(self.__numbers):
            if compara(self.__numbers[i],nr,operand)==False:
                dict_nou[idx]=self.__numbers[i]
                idx+=1
            i+=1
        return dict_nou

    def set_numbers(self, numbers: dict):
        """
        Functia seteaza un dictionar de numere complexe in functie de altul
        input: self=dictionar de numere complexe, numbers=dictionar de numere complexe ce va fi setat
        output: self modificat
        """
        self.__numbers = copy_dict(numbers)

    def undo(self):
        """Revine la ultima stare salvată dacă există."""
        if self.__undo:
            last_state = self.__undo.pop()
            self.set_numbers(last_state)
        else:
            raise Exception("Nu există nicio operațiune anterioară pentru undo.")