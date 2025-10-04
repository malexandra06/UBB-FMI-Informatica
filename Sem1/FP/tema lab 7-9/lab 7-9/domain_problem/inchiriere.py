class Inchiriere:
    """
    Am definit clasa Inchiriere si metodele necesare
    """
    def __init__(self,id_client,id_film,inchiriat):
        """
        principalele atribute ale unui obiect de tip inchiriere
        """
        self.__id_c=id_client
        self.__id_f=id_film
        self.__inchiriat=inchiriat

    def __str__(self):
        """
        Metoda de imprimare a obiectului de tip Inchiriere
        """
        if self.get_inchiriat():
            return f" Clientul cu id {self.get_id_client()} a inchiriat filmul cu id {self.get_id_film()}"
        else:
            return f" Clientul cu id {self.get_id_client()} a returnat filmul cu id  {self.get_id_film()}"

    def get_id_client(self):
        """
        Accesarea clientului din exteriorul clasei
        """
        return self.__id_c


    def get_id_film(self):
        """
        Accesarea filmului din exteriorul clasei
        """
        return self.__id_f

    def get_inchiriat(self)->bool:
        return self.__inchiriat

    def inchiriat(self):
        self.__inchiriat=True

    def returnat(self):
        """
        Returnarea unui film
        """
        self.__inchiriat=False

    def __eq__(self, other):
        return self.get_id_film()==other.get_id_film() and self.get_id_client()==other.get_id_client()