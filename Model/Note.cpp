#include <stdio.h>
#include <iostream>
#include "../Header/Core.h"

using namespace std;
using namespace Core::Model;

int Note::lastId = 0;


Note::Note()
{
    this->id = ++Note::lastId;
}

Note::Note(string title, string body)
{
    this->id = ++Note::lastId;

    this->title = title;
    this->body = body;
}

Note::Note(int id, string title, string body)
{
    this->id = id;
    Note::lastId = id + 1;
    this->title = title;
    this->body = body;
}

Note::Note(std::vector<Note>::iterator it)
{
    this->id = it->getId();
    this->title = it->getTitle();
    this->body = it->getBody();
}

int Note::getId()
{
    return this->id;
}

Note& Note::setId(int id)
{
    this->id = id;

    return *this;
}

string Note::getTitle()
{
    return this->title;
}

Note& Note::setTitle(string title)
{
    this->title = title;

    return *this;
}

string Note::getBody()
{
    return this->body;
}

Note& Note::setBody(string body)
{
    this->body = body;

    return *this;
}

