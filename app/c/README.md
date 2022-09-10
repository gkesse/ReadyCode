# Auteur

Je suis **Gérard KESSE**,  
Ingénieur en Développement Informatique **C/C++/Qt**, Avec à la fois des compétences en **Système Embarqué** et en **Robotique**. Formé à **Polytech'Montpellier**, Je suis un professionnel de conception de projets logiciel applicatif ou embarqué dans les secteurs de l'**Aéronautique**, de la **Robotique**, des **Drones** et de la **Vision par Ordinateur**. Aussi, Je reste ouvert à d'autres types de secteurs tels que l'**Energie** et les **Finances**.

Pour prendre contact avec moi :

* Site Web : [ReadyDev](http://readydev.ovh "Accéder à mon site web (ReadyDev)")
* Email : [tiakagerard@hotmail.com](mailto:tiakagerard@hotmail.com?subject=Contact&body=Bonjour "Me contacter par email")
* LinkedIn : [https://www.linkedin.com/in/tia-gerard-kesse/](https://www.linkedin.com/in/tia-gerard-kesse/ "Me contacter par LinkedIn (Gerard KESSE)")
* Localité : **Strasbourg - France**

Sommaire :

* [Apprendre la programmation en C](#apprendre-la-programmation-en-c)

# Apprendre la programmation en C

Le langage **C** permet de créer des programmes informatiques procéduraux.

Pour démarrer la programmation en C sous Windows avec WinLib :

* Télécharger et Décompresser **WinLibs** dans un répertoire (**WINLIBS_ROOT**)  
[https://winlibs.com/#download-release](https://winlibs.com/#download-release)  

* Télécharger et Installer **Notepad++**  
[https://notepad-plus-plus.org/downloads/](https://notepad-plus-plus.org/downloads/)  

* Ecrire un programme C (**main.c**)  
```
//===============================================
# include <stdio.h>
//===============================================
int main(int argc, char** _argv)
{
    printf("Bonjour tout le monde\n");
    return 0;
}
//===============================================
```

* Ecrire un script compilation (**compile.bat**)
```
@echo off
::===============================================
set "PATH="
set "PATH=WINLIBS_ROOT\bin;%PATH%"
::===============================================
gcc -c main.c -o main.o
gcc -o main.exe main.o
::===============================================
main.exe
::===============================================  
```  
