#ifndef REDRES_TYPE_PASSWORD
#define REDRES_TYPE_PASSWORD

#include <string>
#include <algorithm>

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

    // Constructors.
    Password() = default;
    Password(Password&&);
    Password(Password const&) = delete;
    Password& operator=(Password const&) = delete;
    Password& operator=(Password&&);
    Password(string, string, uint32_t, uint32_t);
    ~Password();

    string const& freeze_service() const;
    string const& freeze_username() const;

    private:
    Encoding encoding = Encoding::Ascii85;
    string service = "";
    string username = "";
    uint32_t changes = 0;
    uint32_t length = 0;
};

#endif
