#include "password.hpp"

using std::string;
using std::transform;

void
scrub(string& s) {
    for(int n = 0; n < 5; ++n) {
        transform
            ( s.begin()
            , s.end()
            , s.begin()
            , [](char s) { return '\0'; }
            );
    }
}

Password::Password(Password&& o) {
    using std::swap;
    swap(this->service, o.service);
    swap(this->username, o.username);
    swap(this->changes, o.changes);
    swap(this->length, o.length);
}

Password::Password(string service, string username, uint32_t changes, uint32_t length)
    : service{service}
    , username{username}
    , changes{changes}
    , length{length}
{
}

Password::~Password() {
    scrub(this->service);
    scrub(this->username);
}

string const&
Password::freeze_service() const {
    return this->service;
}

string const&
Password::freeze_username() const {
    return this->username;
}
