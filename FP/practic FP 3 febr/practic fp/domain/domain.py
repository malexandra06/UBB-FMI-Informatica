class Melodie:
    def __init__(self,titlu,artist,gen,data):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__data = data

    def __str__(self):
        return f"{self.get_titlu()} - {self.get_artist()} - {self.get_gen()}"

    def get_titlu(self):
        return self.__titlu

    def get_artist(self):
        return self.__artist

    def get_gen(self):
        return self.__gen

    def get_data(self):
        return self.__data

    def set_titlu(self,titlu):
        self.__titlu = titlu

    def set_artist(self,artist):
        self.__artist = artist

    def set_gen(self,gen):
        self.__gen = gen

    def set_data(self,data):
        self.__data = data

    def __eq__(self, other):
        if isinstance(other,Melodie):
            return self.get_titlu()==other.get_titlu() and self.get_artist()==other.get_artist() and self.get_gen()==other.get_gen() and self.get_data()==other.get_data()
        return False
