from numar_complex import NUMAR_COMPLEX

class NumberValidator:
    """
    clasa care valideaza un numar complex
    """
    def validate_number(self, nr):
        errors = []
        if nr.get_real() is None:
            errors.append("Partea reala este invalida!")
        if nr.get_imaginar() is None:
            errors.append("Partea imaginara este invalida!")
        if isinstance(nr, NUMAR_COMPLEX) is False:
            errors.append("Introduceti valori intregi pentru a si b!")
        if len(errors):
            raise ValueError(str(errors))
        else:
            return True