import string

from numar_complex import *

class InvalidCommand(BaseException):
    """"
    clasa care mosteneste BaseException
    folosita pentru a notifica cand o comanda primita
     de la utilizator nu e valida
    """
    pass

class InvalidPosition(IndexError):
    """
    clasa care mosteneste ValueError
    folosita pentru a notifica utilizatorul cand optiunea sau
    un numar introdus nu este de tipul precizat
    """
    pass

def verifica_prim(x:NUMAR_COMPLEX):
    """
    verifica daca partea reala a unui numar complex este numar prim
    input:x de tip numar complex
    output:True daca are partea reala prima, False in caz contrar
    """
    if x.get_real()<2:
        return False
    elif x.get_real()==2:
        return True
    else:
        for i in range(2,x.get_real()//2+1):
            if x.get_real()%i==0:
                return False
        return True

def compara(nr1: NUMAR_COMPLEX,nr2: NUMAR_COMPLEX,operand: str):
    """
    Functia compara modulele a 2 numere complexe
    input: nr1,nr2 de tip numar complex operandul=string
    output: True sau False
    """
    match operand.strip():
        case '<':
            return NUMAR_COMPLEX.calculeaza_modul(nr1)<NUMAR_COMPLEX.calculeaza_modul(nr2)
        case '=':
            return NUMAR_COMPLEX.calculeaza_modul(nr1)==NUMAR_COMPLEX.calculeaza_modul(nr2)
        case '>':
            return NUMAR_COMPLEX.calculeaza_modul(nr1)>NUMAR_COMPLEX.calculeaza_modul(nr2)
        case _:
            raise InvalidCommand(f"Operandul {operand} nu este valabil!")


def copy_lista(lista:list):
    """
    Functia realizeaza o copie a unei liste date
    """
    lista_noua=[]
    for i in lista:
        lista_noua.append(i)
    return lista_noua

def lista_in_dictionar(lista_de_obiecte):
    """
    Functia converteste o lista in dictionar
    """
    dictionar = {}
    id=0
    for obj in lista_de_obiecte:
        dictionar[id] = obj  # Folosim `id` ca și cheie
        id+=1
    return dictionar

def copy_dict(dictionar: dict) -> dict:
    """
    Functia realizeaza copia unui dictionar
    """
    dict_nou = {}
    for key, value in dictionar.items():
        dict_nou[key] = value
    return dict_nou
