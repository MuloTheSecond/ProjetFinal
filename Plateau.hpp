#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <vector>
#include "Case.hpp"
#include <memory>

class Plateau
{
public:
    Plateau();
    ~Plateau();
    std::shared_ptr<Case> rechercherCaseParNom(std::string nom);

    void ajouterCase(std::string nom, std::string description);

private:
    std::vector<std::shared_ptr<Case>> cases_;
};

Plateau::Plateau()
{
}

Plateau::~Plateau()
{
}

void Plateau::ajouterCase(std::string nom, std::string description)
{
    auto newCase = std::make_shared<Case>(nom, description);

    cases_.push_back(newCase);
}

std::shared_ptr<Case> Plateau::rechercherCaseParNom(std::string nom)
{
    for (const auto& ptrCase : cases_)
    {
        if (ptrCase->nom_ == nom)
        {
            return ptrCase;
        }
    }
    return nullptr; 
}

#endif
