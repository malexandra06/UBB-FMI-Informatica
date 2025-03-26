from domain.domain import Melodie


class Repository:
    def __init__(self,filename):
        self.__filename=filename

    def __load_from_file(self):
        """
        Functia extrage datele din fisier si le pune intr-o lista
        return: lst: lista cu datele din fisier
        """
        try:
            lst=[]
            with open(self.__filename,'r') as file:
                lines=file.readlines()
                for line in lines:
                    line=line.strip().split(",")
                    data=Melodie(line[0],line[1],line[2],line[3])
                    lst.append(data)
                return lst
        except IOError:
            print("Nu s-a putut deschide fisierul")

    def get_all(self):
        """
        Functia returneaza tot ceea ce s-a extras din fisier
        :return: lista
        """
        return self.__load_from_file()

    def __save_to_file(self,lst):
        """
        Functia salveaza o lista data intr-un fisier
        :param lst: lista care se va salva in fisier
        :return: -
        """
        try:
            with open(self.__filename,'w') as file:
                for el in lst:
                    line=el.get_titlu()+","+el.get_artist()+","+el.get_gen()+","+str(el.get_data())+"\n"
                    file.write(line)
        except IOError:
            print("Nu s-a putut deschide fisierul")

    def modificare_melodie(self,titlu,artist,gen2,data2):
        """
        Functia modifica o melodie din fisier
        :param titlu: titlul melodiei pe care o modificam
        :param artist: artistul melodiei pe care o modificam
        :param gen2: genul cu care se va modifica
        :param data2: data cu care se va modifica
        :return: -
        """
        lst=self.get_all()
        ok=0
        for el in lst:
            if el.get_titlu()==titlu and el.get_artist()==artist:
                el.set_gen(gen2)
                el.set_data(data2)
                self.__save_to_file(lst)
                ok=1
        if ok==0:
            raise Exception("In lista nu exista melodii cu titlul si artistul specificat!")

    def adauga_melodie(self,titlu,artist,gen,durata):
        """
        Functia adauga o melodie in fisier,lista
        :param titlu:
        :param artist:
        :param gen:
        :param durata:
        :return: -
        """
        melodie=Melodie(titlu,artist,gen,durata)
        lst=self.get_all()
        lst.append(melodie)
        self.__save_to_file(lst)