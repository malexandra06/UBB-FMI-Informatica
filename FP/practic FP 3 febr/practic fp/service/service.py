import datetime
import random

from domain.domain import Melodie


class Service:
    def __init__(self, repo,validator):
        self.__repo = repo
        self.__validator = validator

    def adauga_melodie(self,titlu,artist,gen,data):
        """
        Functia adauga o melodie in lista,fisier
        datele pentru a forma o melodie:
        :param titlu:
        :param artist:
        :param gen:
        :param data:
        :return:
        """
        self.__repo.adauga_melodie(titlu,artist,gen,data)

    def get_all(self):
        """
        Functia returneaza o lista cu ceea ce se gaseste in fisier
        :return:
        """
        return self.__repo.get_all()

    def modificare_melodie(self,titlu,artist,gen2,data2):
        """
        Functia modifica o melodie
        :param titlu: titlul melodiei pe care o modifica
        :param artist: artistul melodiei pe care o modifica
        :param gen2: noul gen cu care se va modifica
        :param data2: noua data
        :return:
        """
        try:
            melodie1=Melodie(artist,titlu,gen2,data2)
            self.__validator.valideaza(melodie1)
            self.__repo.modificare_melodie(titlu,artist,gen2,data2)
        except Exception as e:
            print(e)

    def cautare(self,titlu,artist):
        """
        Functia verifica daca exista in lista o melodie cu titlul si artistul dat
        :param titlu:
        :param artist:
        :return:
        """
        for el in self.get_all():
            if el.get_titlu()==titlu and el.get_artist()==artist:
                return True
        return False

    def genereaza_random(self,nr,titluri,artisti):
        """
        Functia genereaza random date de intrare
        :param nr: nr de generari care se doresc a fi facute
        :param titluri: lista de titluri de unde se alege random unul
        :param artisti: lista de artisti de unde se alege random unul
        :return:
        """
        generare = 0
        for el in range(nr):
            titlu = random.choice(titluri)
            artist = random.choice(artisti)
            gen = random.choice(["Rock", "Jazz", "Pop"])
            date='11.10.2020'
            melodie=Melodie(titlu,artist,gen,date)
            if self.cautare(titlu,artist)==False:
                self.__repo.adauga_melodie(titlu,artist,gen,date)
                generare+=1
        return generare

    def statistici(self):
        """
        Functia genereaza statistici precum: cea mai veche melodie,
        cea mai noua melodie,cate melodii sunt din fiecare gen, artistul cu cele mai multe melodii
        :return:
        melodie_veche=string
        melodie_noua=string
        genuri=dict
        artist_max=artistul cu cele mai multe melodii
        maxim
        """
        melodie_veche=Melodie('','','','')
        melodie_noua=Melodie('','','','')
        data_min='31.12.2026'
        data_min=datetime.datetime.strptime(data_min,'%d.%m.%Y')
        data_max='01.01.0001'
        data_max=datetime.datetime.strptime(data_max,'%d.%m.%Y')
        for el in self.get_all():
            aux=el.get_data()
            aux=datetime.datetime.strptime(aux,'%d.%m.%Y')
            if aux<data_min:
                data_min=aux
                melodie_veche=el
            if aux>data_max:
                data_max=aux
                melodie_noua=el
        genuri={'Rock':0,'Jazz':0,'Pop':0}
        for el in self.get_all():
            if el.get_gen() == 'Rock':
                genuri['Rock']+=1
            if el.get_gen() == 'Jazz':
                genuri['Jazz']+=1
            if el.get_gen() == 'Pop':
                genuri['Pop']+=1
        artisti = []
        for el in self.get_all():
            if el.get_artist() not in artisti:
                artisti.append(el.get_artist())
        nr=[0]*len(artisti)
        for el in self.get_all():
            if el.get_artist() in artisti:
                nr[artisti.index(el.get_artist())]+=1
        maxim=max(nr)
        artist_max = ''
        for i in range(len(nr)):
            if nr[i]== maxim:
                artist_max = artisti[i]
        return melodie_veche,melodie_noua,genuri,artist_max,maxim





