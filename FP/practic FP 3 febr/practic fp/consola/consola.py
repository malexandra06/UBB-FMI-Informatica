class Consola:
    def __init__(self,service):
        self.__service=service

    @staticmethod
    def print_menu():
        print("1.Afiseaza melodiile din fisier")
        print("2.Modificare melodie")
        print("3.Genereaza un numar de melodii")
        print("4.Statistici")
        print("5.Iesire")

    def case_1(self):
        for el in self.__service.get_all():
            print(el)

    def case_2(self):
        try:
            titlu=input("Introduceti titlul melodiei pe care doriti sa o modificati ")
            artist=input("Introduceti artistul melodiei pe care doriti sa o modificati ")
            gen=input("Introduceti noul gen ")
            data=input("Introduceti noua data de aparitie avand formatul 'dd.mm.yyyy' ")
            self.__service.modificare_melodie(titlu,artist,gen,data)
        except ValueError as e:
            print(e)

    def case_3(self):
        try:
            nr=int(input("Introduceti numarul de melodii pe care doriti sa le generati "))
            string1=input("Introduceti un string care contine titlurile separate prin , : ")
            string2=input("Introduceti un string care contine artistii separati prin , : ")
            titluri=string1.split(',')
            artisti=string2.split(',')
            generare=self.__service.genereaza_random(nr,titluri,artisti)
            print(generare)
        except ValueError:
            print("Introduceti valori intregi pentru nr!")

    def case_4(self):
        melodie_v,melodie_n,genuri,art_max,max=self.__service.statistici()
        print(f"Cea mai veche melodie este: {melodie_v}")
        print(f"Cea mai noua melodie este: {melodie_n}")
        for el in genuri.keys():
            print (el,genuri[el])
        print(f"Artistul cu cele mai multe melodii este: {art_max} si are un numar de {max} melodii")

    def start(self):
        while True:
            self.print_menu()
            option=input("Introduceti optiunea dorita: ")
            match option:
                case "1":
                    self.case_1()
                case "2":
                    self.case_2()
                case "3":
                    self.case_3()
                case "4":
                    self.case_4()
                case "5":
                    return False
                case _:
                    print("Optiune invalida!")

