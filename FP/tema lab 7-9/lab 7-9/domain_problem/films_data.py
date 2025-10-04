class Film:
    """
    Am definit clasa Film si metodele necesare
    """
    def __init__(self,title: str,description: str, genre: str):
        """
        Definim atributele obiectului de tip Film
        """
        self.__id=None
        self.__title=title
        self.__description=description
        self.__genre=genre

    def __str__(self):
        """
        Definim metoda de imprimare a obiectului de tip Film
        """
        return f" id: {self.get_id()}, titlul: {self.get_title()}, descrierea: {self.get_description()}, genul: {self.get_genre()}"

    def get_id(self):
        """
        Accesarea id-ului din exteriorul clasei
        input: self
        output: self.__id
        """
        return self.__id

    def set_id(self,new_id):
        """
        Setarea id-ului din exteriorul clasei
        input: self, new_id
        output: id modificat
        """
        self.__id=new_id

    def get_title(self):
        """
        Accesarea titlului din exteriorul clasei
        input: self
        output: self.__title
        """
        return self.__title

    def set_title(self,new_title):
        """
        Setarea titlului din exteriorul clasei
        input: self, new_title
        output: titlu modificat
        """
        self.__title=new_title

    def get_description(self):
        """
        Accesarea descrierei din exteriorul clasei
        input: self
        output: self.__description
        """
        return self.__description

    def set_description(self,new_description):
        """
        Setarea descrierei din exteriorul clasei
        input: self, new_description
        output: descriere modificata
        """
        self.__description=new_description

    def get_genre(self):
        """
        Accesarea tipului din exteriorul clasei
        input: self
        output: self.__genre
        """
        return self.__genre

    def set_type(self,new_genre):
        """
        Setarea tipului din exteriorul clasei
        input: self, new_type
        output: tip modificat
        """
        self.__genre=new_genre


    def __eq__(self, other):
        """
        Metoda de comparare pentru obiecte de tip Film
        """
        if isinstance(other, Film):
            return (self.get_title() == other.get_title() and
                    self.get_description() == other.get_description() and self.get_genre()==other.get_genre())
        return False