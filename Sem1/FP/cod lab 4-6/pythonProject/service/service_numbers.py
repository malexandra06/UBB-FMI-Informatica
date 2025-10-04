from numar_complex import NUMAR_COMPLEX
from validare_numar import NumberValidator
from functii_auxiliare import copy_dict, copy_lista, InvalidPosition
from number_repository import NumberRepository
from number_repository_dict import NumberRepositoryDict

def copy_data(data):
    """Creează o copie a structurii de date, fie ea listă sau dicționar."""
    if isinstance(data, dict):
        return copy_dict(data)
    elif isinstance(data, list):
        return copy_lista(data)

class Service:
    """
    layer-ul din mijloc dintre interactionarea cu utilizatorul (user interface) si layer-ul de date (repository)
    primeste date de la Controller, le valideaza si aplica diversi algoritmi, logica, pe acestea, si apeleaza functii
        din repository ca sa manipuleze datele. Aici sunt definite functiile din repository
    """

    def __init__(self, repository: NumberRepository, validator: NumberValidator):
        self.__repository = repository
        self.__validator = validator
        self.__undo=[]

    def add_number(self,nr:NUMAR_COMPLEX):
        self.__validator.validate_number(nr)
        self.__repository.add_number(nr)

    def get_numbers(self):
        return self.__repository.get_all_numbers()

    def verifica_pozitie(self,poz:int):
        if 0<=poz<len(self.__repository.get_all_numbers()):
            return True
        return False

    def add_number_poz(self, poz:int, nr:NUMAR_COMPLEX):
        self.__validator.validate_number(nr)
        self.__repository.add_number_poz(nr, poz)

    def remove_number(self, poz:int):
        self.__repository.remove_p(poz)

    def remove_secv(self,p1:int,p2:int):
        self.__repository.remove_secv(p1,p2)

    def replace(self,nr1:NUMAR_COMPLEX,nr2:NUMAR_COMPLEX):
        self.__validator.validate_number(nr1)
        self.__validator.validate_number(nr2)
        self.__repository.replace(nr1,nr2)

    def tipareste_imaginar(self,p1:int,p2: int):
        return self.__repository.tipareste_imaginar(p1,p2)

    def tipareste(self):
        return self.__repository.tipareste()

    def tipareste_modul_egal(self):
        return self.__repository.tipareste_modul_egal()

    def aduna_numere_complexe(self,p1: int,p2: int):
        return self.__repository.aduna_numere_complexe(p1,p2)

    def produs_numere_complexe(self,p1: int,p2: int):
        return self.__repository.produs_numere_complexe(p1,p2)

    def sorteaza_descrescator(self):
        return self.__repository.sorteaza_descrescator()

    def filtrare_parte_reala_prim(self):
        return self.__repository.filtrare_parte_reala_prim()

    def filtrare_modul(self,nr:NUMAR_COMPLEX,operand:str):
        return self.__repository.filtrare_modul(nr,operand)

    def undo(self):
        self.__repository.undo()



