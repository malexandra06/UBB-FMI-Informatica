class FilmManagementException(Exception):
    pass

class InvalidCommand(Exception):
    pass

class RepositoryException(FilmManagementException):
    def __init__(self, msg):
        self.__msg = msg

    def get_message(self):
        return self.__msg

    def __str__(self):
        return "Repository exception:" + str(self.__msg)


class PersonAlreadyExistsException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Persoana exista deja.")


class PersonDoesNotExistException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Nu exista persoana.")


class FilmAlreadyExistsException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Filmul exista deja.")


class FilmDoesNotExistException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Nu exista filmul.")


class RentAlreadyExistsException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Exista deja o inchiriere pentru filmul si pentru clientul acesta.")

class RentDoesNotExistException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Inchirierea nu exista.")

class RentReturnedException(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Filmul a fost deja returnat.")

class ValidationException(FilmManagementException):
    def __init__(self, msg):
        self.__msg = msg

    def __str__(self):
        return "Validation exception:" + str(self.__msg)
