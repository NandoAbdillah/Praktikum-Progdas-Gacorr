#include <string>
#include "user.h"

User loggedUser;

void setLoggedUser (const User &user) {
    loggedUser = user;
}

User getLoggedUser() {
    return loggedUser;
}

User* getLoggedUserPtr() {
    return &loggedUser;
}
