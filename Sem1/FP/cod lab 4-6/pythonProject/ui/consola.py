from functii_auxiliare import InvalidCommand
from service_numbers import Service
from numar_complex import citire_complex
from validare_numar import *

#from validare_numar import NumberValidator


def print_menu():
    """"
    Functia afiseaza optiunile disponibile utilizatorului
    input:-
    output:-
    """
    print("1.Adauga numar in lista")
    print("2.Modifica elemente din lista")
    print("3.Cautare numere")
    print("4.Operatii cu numerele din lista")
    print("5.Filtrare")
    print("6.Undo")
    print("7.Afisare lista")
    print("8.Iesire din program")


class ConsoleUI:
    """
    clasa pentru interfata cu utilizatorul de tip consola
    citeste de la tastatura, apeleaza functii din service si afiseaza rezultatul acestora
    mai poarta denumirea si de Controller
    """

    def __init__(self, service: Service):
        self.__service = service

    def add_number(self):
        try:
            print("Citeste un numar complex de forma a+bi, a si b intregi: ")
            nr=citire_complex()
            if nr is not None:
                self.__service.add_number(nr)
                print(f"Numarul {nr} a fost adaugat cu succes!")
        except ValueError:
            print("Introduceti numere intregi pentru a si b!")

    def add_number_poz(self):
        try:
            print("Introduceti pozitia pe care doriti sa fie inserat numarul: ")
            poz = int(input("p="))
            print("Citeste un numar complex de forma a+bi, a si b intregi: ")
            nr=citire_complex()
            if self.__service.verifica_pozitie(poz)==True and nr is not None:
                self.__service.add_number_poz(poz, nr)
                print(f"Numarul {nr} a fost adaugat la pozitia {poz} cu succes!")
            elif self.__service.verifica_pozitie(poz)==False:
                print("Pozitia introdusa nu este valida!")
        except ValueError:
            print("Introduceti numere intregi pentru a si b!")

    def remove_number(self):
        print("Introduceti pozitia de unde doriti sa stergeti numarul: ")
        poz = int(input("p="))
        if self.__service.verifica_pozitie(poz)==True:
            self.__service.remove_number(poz)
            print(f"Numarul de pe pozitia {poz} a fost sters cu succes!")
        elif self.__service.verifica_pozitie(poz)==False:
            print("Pozitia introdusa nu este valida!")

    def remove_secv(self):
        print("Introduceti intervalul de pozitii unde doriti sa stergeti elemente:")
        p1 = int(input("p1="))
        p2 = int(input("p2="))
        if self.__service.verifica_pozitie(p1) == False or self.__service.verifica_pozitie(p2) == False or p1 > p2:
            print("Pozitiile introduse nu sunt valide!")
        else:
            self.__service.remove_secv(p1, p2)
            print("Secventa a fost stearsa cu succes!")

    def replace(self):
        try:
            print("Citeste 2 numere complexe de forma a+bi, cu a si b intregi: ")
            print("Citeste numarul pe care vrei sa il inlocuiesti:")
            nr1=citire_complex()
            print("Citeste numarul cu care vrei sa se inlocuiasca precedentul:")
            nr2 = citire_complex()
            if nr1 is None or nr2 is None:
                print("Numerele complexe sunt invalide!")
            if nr1 not in self.__service.get_numbers():
                print("Numarul de inlocuit nu exista in lista!")
            else:
                self.__service.replace(nr1, nr2)
                print("Secventa a fost stearsa cu succes!")
        except ValueError as e:
            print(e)

    def tipareste_imaginar(self):
        secv=[]
        print("Introduceti intervalul de pozitii unde doriti sa afisati partea imaginara a elementelor:")
        p1 = int(input("p1="))
        p2 = int(input("p2="))
        if self.__service.verifica_pozitie(p1) == False or self.__service.verifica_pozitie(p2) == False or p1 > p2:
            print("Pozitiile introduse nu sunt valide!")
        else:
            secv=self.__service.tipareste_imaginar(p1, p2)
            for i in range(len(secv)):
                print(secv[i])

    def tipareste(self):
        secv=[]
        secv=self.__service.tipareste()
        for i in range(len(secv)):
            print(NUMAR_COMPLEX.__str__(secv[i]))

    def tipareste_modul_egal(self):
        secv=[]
        secv=self.__service.tipareste_modul_egal()
        for i in range(len(secv)):
            print(NUMAR_COMPLEX.__str__(secv[i]))

    def aduna_numere_complexe(self):
        print("Introduceti intervalul de pozitii unde doriti sa stergeti elemente:")
        p1 = int(input("p1="))
        p2 = int(input("p2="))
        if self.__service.verifica_pozitie(p1) == False or self.__service.verifica_pozitie(p2) == False or p1 > p2:
            print("Pozitiile introduse nu sunt valide!")
        else:
            s=self.__service.aduna_numere_complexe(p1,p2)
            print("Suma numerelor din secventa data este: ",s)

    def produs_numere_complexe(self):
        print("Introduceti intervalul de pozitii unde doriti sa stergeti elemente:")
        p1 = int(input("p1="))
        p2 = int(input("p2="))
        if self.__service.verifica_pozitie(p1) == False or self.__service.verifica_pozitie(p2) == False or p1 > p2:
            print("Pozitiile introduse nu sunt valide!")
        else:
            s=self.__service.produs_numere_complexe(p1,p2)
            print("Produsul numerelor din secventa data este: ",s)

    def sorteaza_descrescator(self):
        numbers=self.__service.sorteaza_descrescator()
        print("Numerele au fost sortate descrescator dupa partea imaginara!")
        for key, value in numbers.items():
            print(NUMAR_COMPLEX.__str__(value))

    def filtrare_parte_reala_prim(self):
        numbers=self.__service.filtrare_parte_reala_prim()
        print("Numerele au fost filtrate prin eliminarea numerelor cu partea reala prima!")
        for key, value in numbers.items():
            print(NUMAR_COMPLEX.__str__(value))

    def filtrare_modul(self):
        try:
            print("Introduceti numarul in functie de care doriti sa filtrati numerele:")
            nr=citire_complex()
            if nr is not None:
                    print("Introduceti operatia in functie de care doriti sa filtrati numerele:")
                    operand=input("operand:")
                    if operand=='=' or operand=='<' or operand=='>':
                        numbers=self.__service.filtrare_modul(nr,operand)
                        print("Numerele au fost filtrate dupa modulul unui numar citit de la tastatura!")
                        for key, value in numbers.items():
                            print(NUMAR_COMPLEX.__str__(value))
                    else: print("Operand invalid!")
        except ValueError as e:
            print(e)

    def view_numbers(self):
        """
        Afiseaza lista de numere complexe
        """
        for nr in self.__service.get_numbers():
            print(NUMAR_COMPLEX.__str__(nr))

    def undo(self):
        self.__service.undo()

    def case_1(self):
        ok=True
        while ok==True:
            print(" 1.1.Adauga numar complex la sfarsitul listei")
            print(" 1.2.Insereaza numar complex pe o pozitie data")
            print("   B.Back to main menu")
            print()
            option_2 = (input("Introduceti optiunea din submeniu dorita:"))
            match option_2:
                case "1.1":
                    self.add_number()
                case "1.2":
                    self.add_number_poz()
                case "B":
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option_2} nu este valabila!")

    def case_2(self):
        ok=True
        while ok==True:
            print(" 2.1.Șterge element de pe o poziție dată")
            print(" 2.2.Șterge elementele de pe un interval de poziții")
            print(" 2.3.Înlocuiește toate aparițiile unui număr complex cu un alt număr complex")
            print("   B.Back to main menu")
            print()
            option_2 = (input("Introduceti optiunea din submeniu dorita:"))
            match option_2:
                case "2.1":
                    self.remove_number()
                case "2.2":
                    self.remove_secv()
                case "2.3":
                    self.replace()
                case "B":
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option_2} nu este valabila!")

    def case_3(self):
        ok=True
        while ok==True:
            print(" 3.1.Tipareste partea imaginara pentru numerele din lista. Se da subsecventa")
            print(" 3.2.Tipareste toate numerele care au modulul mai mic decat 10")
            print(" 3.3.Tipareste toate numerele care au modulul egal cu 10")
            print("   B.Back to main menu")
            print()
            option_2 = (input("Introduceti optiunea din submeniu dorita:"))
            match option_2:
                case "3.1":
                    self.tipareste_imaginar()
                case "3.2":
                    self.tipareste()
                case "3.3":
                    self.tipareste_modul_egal()
                case "B":
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option_2} nu este valabila!")

    def case_4(self):
        ok=True
        while ok==True:
            print(" 4.1.Suma numerelor dintr-o subsecventa data ")
            print(" 4.2.Produsul numerelor dintr-o subsecventa data")
            print(" 4.3.Tipareste lista sortata descrescator dupa partea imaginara")
            print("   B.Back to main menu")
            print()
            option_2 = (input("Introduceti optiunea din submeniu dorita:"))
            match option_2:
                case "4.1":
                    self.aduna_numere_complexe()
                case "4.2":
                    self.produs_numere_complexe()
                case "4.3":
                    self.sorteaza_descrescator()
                case "B":
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option_2} nu este valabila!")

    def case_5(self):
        ok=True
        while ok==True:
            print(" 5.1.Filtrare parte reala prim – elimină din listă numerele complexe la care partea reala este prim")
            print(" 5.2.Filtrare modul – elimina din lista numerele complexe la care modulul este <,= sau > decât un număr dat")
            print("   B.Back to main menu")
            print()
            option_2 = (input("Introduceti optiunea din submeniu dorita:"))
            match option_2:
                case "5.1":
                    self.filtrare_parte_reala_prim()
                case "5.2":
                    self.filtrare_modul()
                case "B":
                    ok=False
                case _:
                    raise InvalidCommand(f"Comanda {option_2} nu este valabila!")

    def handle_command(self,option):
        """
        Functia directioneaza optiunea utilizatorului din meniul principal
        input: option=optiunea din meniul pricipal introdusa de utilizator, list=lista de numere complexe
        output:lista modificata, true daca a fost introdusa optiunea 7 sau false altfel
        """
        match option:
            case 1:
                try:
                    self.case_1()
                except InvalidCommand as e:
                    print(e)
            case 2:
                try:
                    self.case_2()
                except InvalidCommand as e:
                    print(e)
            case 3:
                try:
                    self.case_3()
                except InvalidCommand as e:
                    print(e)
            case 4:
                try:
                    self.case_4()
                except InvalidCommand as e:
                    print(e)
            case 5:
                try:
                    self.case_5()
                except InvalidCommand as e:
                    print(e)
            case 6:
                    self.undo()
            case 7:
                self.view_numbers()
            case 8:
                print("Programul s-a incheiat cu succes!")
                return True
            case _:
                raise InvalidCommand(f"Comanda {option} nu este valabila! Incercati o comanda dintre cele prezente.")

    def run(self):
        """
        Functia ruleaza programul si prinde exceptiile necesare
        """
        while True:
            print_menu()
            print()
            try:
                option = int(input("Introduceti optiunea: "))
                ok = self.handle_command(option)
                if ok:
                    break
            except ValueError:  # Prinde exceptia in care s-a introdus un string in loc de un numar
                print("Introduceti un numar intreg!")
                print()
            except InvalidCommand as ex:  # Prinde exceptia in care utilizatorul a introdus o optiune care nu este disponibila
                print(ex)
                print()