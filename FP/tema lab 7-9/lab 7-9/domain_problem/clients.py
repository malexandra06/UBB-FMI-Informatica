class Client:
    """
    Am definit clasa Client si metodele necesare pentru a lucra cu obiecte de acest tip
    """
    def __init__(self, name, cnp):
        """
        Definim atributele obiectului de tip Client
        """
        self.__id = None
        self.__name = name
        self.__cnp = cnp
        #self.__data={
            #"id":id,
            #"name":name,
            #"cnp":cnp
                    #}

    def __str__(self):
        """
        Definim metoda de imprimare a obiectului de tip Client
        """
        return f"Clientul are id-ul: {self.get_id()},numele: {self.get_name()} si cnp: {self.get_cnp()}"

    def __lt__(self, other):
        # Comparare dupa nume
        if isinstance(other, Client):
            return self.get_name() < other.get_name()
        return False

    def get_id(self):
        """
        Accesarea id-ului din exteriorul clasei
        input: self
        output: self.__id
        """
        return self.__id
        #return self.__data["id"]

    def set_id(self, new_id):
        """
        Setarea id-ului din exteriorul clasei
        input: self, new_id
        output: id modificat
        """
        self.__id = new_id
        #self.__data["id"]=new_id

    def get_name(self):
        """
        Accesarea numelui din exteriorul clasei
        input: self
        output: self.__name
        """
        return self.__name
        #return self.__data["name"]

    def set_name(self, new_name):
        """
        Setarea numelui din exteriorul clasei
        input: self, new_name
        output: nume modificat
        """
        self.__name = new_name
        #self.__data["name"]=new_name

    def get_cnp(self):
        """
        Accesarea CNP-ului din exteriorul clasei
        input: self
        output: self.__cnp
        """
        return self.__cnp
        #return self.__data["cnp"]

    def set_cnp(self, new_cnp):
        """
        Setarea CNP-ului din exteriorul clasei
        input: self, new_cnp
        output: CNP modificat
        """
        self.__cnp = new_cnp
        #self.__data["cnp"]=new_cnp

    def __eq__(self, other):
        """
        Metoda de comparare pentru obiecte de tip Client
        input: self, other
        output: True/False
        """
        if isinstance(other, Client):
            return self.get_name() == other.get_name() and self.get_cnp() == other.get_cnp()
        return False