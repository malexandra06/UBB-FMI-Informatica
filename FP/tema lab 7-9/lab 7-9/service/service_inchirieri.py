from copy import deepcopy
from domain_problem.inchiriere import Inchiriere
from domain_problem.clients import Client
from domain_problem.inchiriere_validator import InchiriereValidator
from domain_problem.raport import ReportFilm, ReportClient, ReportGen
from exceptions.exceptions import PersonDoesNotExistException
from sortari.sortari import insertion_sort, comb_sort


class ServiceInchirieri:
    """
    layer-ul dintre repository si interactiunea cu utilizatorul
    """
    def __init__(self,repoi,repof,repoc,validator:InchiriereValidator):
        self.__repository = repoi
        self.__repof=repof
        self.__repoc=repoc
        self.__validator=validator

    def add(self,id_client,id_film,inchiriat):
        """
        Functia adauga o inchiriere in lista daca este valida, altfel arunca exceptie
        """
        self.__validator.validare(id_client,id_film,inchiriat,self.__repoc,self.__repof,self.__repository)
        inchiriat=bool(inchiriat)
        inchiriere = Inchiriere(id_client,id_film,inchiriat)
        self.__repository.add(inchiriere)

    def remove_inchiriere(self,id_client,id_film):
        self.__repository.remove_inchiriere(id_client,id_film)

    def return_film(self,id_client,id_film):
        """
        Functia gestioneaza returnarea unui film
        """

        self.__repository.return_film(Inchiriere(id_client,id_film,True))

    def get_all(self):
        """
        Functia returneaza lista de inchiriere
        """
        return self.__repository.get_all()

    def delete_client(self,id_dat):
        for i in self.get_all():
            if i.get_id_client()==id_dat:
                i.returnat()

    def find_by_id(self,id_client,id_film):
        """
        Functia cauta in lista o inchiriere dupa id si o returneaza daca o gaseste
        """
        return self.__repository.find_by_id(id_client,id_film)

    def cele_mai_inchiriate_filme(self):
        """
        Functia returneaza o lista de tipul ReportFilme, adica contine toate filmele inchiriate (titlul lor mai exact) si numarul lor de inchirieri
        input: self-lista de inchirieri
        output: lista de tipul ReportFilm sortata descrescator
        """
        lista_filme_inchiriate=[]
        all_inchiriere=self.get_all()
        for i in self.__repof.get_all():
            lista_filme_inchiriate.append(ReportFilm(i.get_title(),0))
        for i in range(len(all_inchiriere)):
            for j in range(len(lista_filme_inchiriate)):
                f=self.__repof.find_by_id(all_inchiriere[i].get_id_film())
                if f.get_title()==lista_filme_inchiriate[j].get_title():
                    lista_filme_inchiriate[j].set_nr(lista_filme_inchiriate[j].get_nr() + 1)
        insertion_sort(lista_filme_inchiriate,key= lambda x: x.get_nr(), reverse=True)
        return lista_filme_inchiriate

    def clienti_inchirieri(self):
        """
        Functia creeaza o lista de clienti si numarul de filme pe care le-a inchiriat fiecare
        input: self-lista de inchirieri
        output: lista de tipul ReportClient care retine fiecare client si numarul de inchirieri
        """
        lista_clienti=[]
        client=Client('ABC','00000000000')
        all_i=self.get_all()
        for i in self.__repoc.get_all():
            lista_clienti.append(ReportClient(i.get_name(),0))
        for i in all_i:
            for j in lista_clienti:
                try:
                    client=self.__repoc.find_by_id(i.get_id_client())
                except PersonDoesNotExistException:
                    pass
                if client:
                    if client.get_name()==j.get_name():
                        j.set_nr(j.get_nr()+1)
        return lista_clienti

    def top_30(self):
        """
        Functia returneaza o lista care contine primii 30% clienti cu cele mai multe inchirieri
        input: self-lista de inchirieri
        output: lista de tipul ReportClient sortata care contine doar primii 30% clienti
        """
        lista=deepcopy(self.clienti_inchirieri())
        insertion_sort(lista, key=lambda x: x.get_nr(), reverse=True)
        if len(lista)>=3:
            return lista[:3*len(lista)//10]
        else:
            return lista[0]

    def top_5_gen(self):
        """
        Functia returneaza o lista care contine primele 5 genuri cu cele mai multe inchirieri
        input: self-lista de inchirieri
        output: lista de tipul ReportGen sortata descrescator (primele 5 genuri)
        """
        genuri=[]
        for i in self.__repof.get_all():
            if i.get_genre() not in genuri:
                genuri.append(i.get_genre())
        genuri_numarate=[]
        for i in genuri:
            genuri_numarate.append(ReportGen(i,0))
        for i in self.get_all():
            for g in genuri_numarate:
                if self.__repof.find_by_id(i.get_id_film()).get_genre().strip()==g.get_gen().strip():
                    g.set_nr(g.get_nr()+1)
        comb_sort(genuri_numarate,key=lambda x: x.get_nr(), reverse=True)
        return genuri_numarate[:5]
