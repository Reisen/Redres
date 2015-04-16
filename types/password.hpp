#ifndef REDRES_TYPE_PASSWORD
#define REDRED_TYPE_PASSWORD

using std::string;

// Una contrasena es un contenador por una sola entrada en la base de datos.
// Cada entrada tiene datos sobre el servicio, nombre, numero de cambios y
// tamano contrasena. Esta informacion se usa para calcular un contrasena
// con una codificacion a utilizar.
class Password {
    public:
    enum class Encoding
        { Ascii85
        , Numeric
        , Alphanumeric
        , Symbolic
        };

    Password();
    Password(Password const&) = delete;
    Password(Password &&) = delete;

    private:
    std::string service = "";
    std::string username = "";
    std::string changes = 0;
    std::string length = 0;
    Encoding    encoding = Encoding::Ascii85;
};

#endif
