#pragma once
#include <iostream>
#include <string>
#include "interface_communication.h"
using namespace std;

class ClsPerson : public InterfaceCommunication
{

private:
    string _firstName;
    string _lastName;
    string _email;
    string _phone;

public:
    ClsPerson(string FirstName, string LastName, string Email, string Phone)
    {

        _firstName = FirstName;
        _lastName = LastName;
        _email = Email;
        _phone = Phone;
    }

    // Property Set
    void setFirstName(string FirstName)
    {
        _firstName = FirstName;
    }

    // Property Get
    string getFirstName()
    {
        return _firstName;
    }

    // Property Set
    void setLastName(string LastName)
    {
        _lastName = LastName;
    }

    // Property Get
    string getLastName()
    {
        return _lastName;
    }

    // Property Set
    void setEmail(string Email)
    {
        _email = Email;
    }

    // Property Get
    string getEmail()
    {
        return _email;
    }

    // Property Set
    void setPhone(string Phone)
    {
        _phone = Phone;
    }

    // Property Get
    string getPhone()
    {
        return _phone;
    }

    string fullName()
    {
        return _firstName + " " + _lastName;
    }

    // Interface Implementation Methods || Contracts
    void SendEmail(string Title, string Body)
    {
        cout << "Sending Email: " << Title << endl;
        cout << "Email Body: " << Body << endl;
    }

    void SendFax(string Title, string Body)
    {
        cout << "Sending Fax: " << Title << endl;
        cout << "Fax Body: " << Body << endl;
    }

    void SendSMS(string Title, string Body)
    {
        cout << "Sending SMS: " << Title << endl;
        cout << "SMS Body: " << Body << endl;
    }
};

