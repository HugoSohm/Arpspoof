<div align="center"><h1>Arpspoof - Epitech 2019</h1>

L'Arpspoof est un projet de programmation réseau en C de 3 semaines

</div>

## Projet Arpspoof

### Paramètres

L'Arpspoof nécéssite 3 arguments pour fonctionner

- Adresse ipv4 source
- Adresse ipv4 destination
- Interface

## Installation et compilation

### Récupération du projet

Après avoir cloné le [répertoire](https://github.com/HugoSohm/Arpspoof):

```
git clone https://github.com/HugoSohm/Arpspoof
```

- Se rendre à la racine du projet :

```
$ cd Arpspoof
```

- Vérifier que tout est à jour :

```
$ git checkout master
```

### Compilation du programme

- Compilation

```
$ make
```

- Re-compilation

```
$ make re
```

- Nettoyage

```
$ make fclean
```

## Exécution

### Lancement du programme

- Attaque
```
$ sudo ./myARPspoof {source} {cible} {interface}
$ sudo ./myARPspoof 192.168.0.2 198.168.0.3 wlp58s0
```

- Affichage broadcast
```
$ ./myARPspoof {source} {cible} {interface} --printBroadcast
$ ./myARPspoof 192.168.0.2 198.168.0.3 wlp58s0 --printBroadcast
```

- Affichage spoof
```
$ ./myARPspoof {source} {cible} {interface} --printSpoof {adresse mac cible}
$ ./myARPspoof 192.168.0.2 198.168.0.3 wlp58s0 --printSpoof f8:59:71:8e:64:4a
```
