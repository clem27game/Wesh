
# 🔥 Langage de programmation WESH - Version ULTIME 🔥

![Wesh](http://www.image-heberg.fr/files/17512184253964712824.png)

## Description

**Wesh** est un langage de programmation ésotérique inspiré du vocabulaire de la cité. Il permet d'écrire des programmes avec une syntaxe absurde et amusante tout en gardant les fonctionnalités complètes d'un langage de programmation moderne.

## 🚀 Installation et compilation

### Prérequis
- Cloné le repos github 
- Make

### Compilation
```bash
make
```

### Exécution
```bash
./Wesh/main wsh <fichier.wsh>
```

## 📝 Syntaxe du langage

Tous les fichiers Wesh doivent avoir l'extension `.wsh` et chaque commande doit commencer par `^`.

### 1. **Wsh** - Affichage de messages

Affiche un message dans la console.

**Syntaxe :**
```wesh
^ Wsh - hello world
^ Wsh - "Salut mon poto"
```

### 2. **Capté** - Mathématiques

Effectue des opérations mathématiques de base.

**Syntaxe :**
```wesh
^ Capté : [expression]
```

**Exemples :**
```wesh
^ Capté : 4 + 7
^ Capté : age * 2
```

### 3. **quoicoubeh** - Blagues aléatoires

Affiche une blague aléatoire.

**Syntaxe (exacte obligatoire) :**
```wesh
^ quoicoubeh × donne moi ma blague poto ou tes mort
```

### 4. **watt** - Définition de variables

Permet de définir des variables numériques ou textuelles.

**Syntaxe :**
```wesh
^ watt : [nom_variable] = [valeur]
```

### 5. **poto** - Conditions

Permet de créer des conditions.

**Syntaxe :**
```wesh
^ poto : si [condition]
alors [commande]
```

### 6. **reuf** - Messages colorés

Affiche des messages avec des couleurs.

**Syntaxe :**
```wesh
^ reuf : couleur [couleur] - "[message]"
```

**Couleurs disponibles :** rouge, vert, bleu, jaune, rose, cyan, blanc, violet, orange

**Syntaxe :**
```wesh
^ crampté - "[message_initial]", [délai] ms , "[message_final]"
```

## 🔥 NOUVELLES FONCTIONNALITÉS 🔥

### 9. **bogoss** - Boucles WHILE

Crée des boucles tant que (while).

**Syntaxe :**
```wesh
^ bogoss : tant que [condition]
[commandes]
fini
```

**Exemple :**
```wesh
^ watt : x = 1
^ bogoss : tant que x <= 3
^ Wsh - Valeur de x:
^ Capté : x
^ watt : x = x + 1
fini
```

### 10. **gadjo** - Boucles FOR

Crée des boucles for avec compteur.

**Syntaxe :**
```wesh
^ gadjo : [variable] de [début] à [fin]
[commandes]
fini
```

**Exemple :**
```wesh
^ gadjo : i de 1 à 5
^ Wsh - Itération:
^ Capté : i
fini
```

### 12. **sah** - Input utilisateur

Demande une saisie à l'utilisateur.

**Syntaxe :**
```wesh
^ sah : "[question]" dans [variable]
```

**Exemples :**
```wesh
^ sah : "Quel est ton âge ?" dans age
^ sah : "Comment tu t'appelles ?" dans nom
```

### 13. **wAllah** - Assertions/Vérifications

Vérifie si une condition est vraie ou fausse.

**Syntaxe :**
```wesh
^ wAllah : [condition], "[message]"
```

**Exemples :**
```wesh
^ wAllah : age > 18, "Tu es majeur!"
^ wAllah : score == 100, "Score parfait!"
^ wAllah : nom == "Kevin", "Salut Kevin!"
```

### 14. **daronne** - Gestion de fichiers

Écrit et lit des fichiers.

**Syntaxe :**
```wesh
^ daronne : écris "[contenu]" dans "[fichier]"    # Écriture
^ daronne : lis "[fichier]"                       # Lecture
```

**Exemples :**
```wesh
^ daronne : écris "Salut mon poto!" dans "message.txt"
^ daronne : lis "message.txt"
^ daronne : écris "Score: 100" dans "scores.txt"
```

### 15. **zonzon** - Gestion d'erreurs

Zone de sécurité pour capturer les erreurs.

**Syntaxe :**
```wesh
^ zonzon : [message de sécurité]
```

## 💾 Exemple complet avec toutes les fonctionnalités

```wesh
# Programme complet Wesh
^ Wsh - Bienvenue dans le langage Wesh ULTIME!

# Variables
^ watt : age = 20
^ watt : nom = "Kevin"

# Input utilisateur
^ sah : "Quel est ton score ?" dans score

# Conditions
^ poto : si age >= 18
alors ^ reuf : couleur vert - "Tu es majeur!"

# Assertions
^ wAllah : score > 10, "Score acceptable"

# Boucles FOR
^ gadjo : i de 1 à 3
^ Wsh - Tour numéro:
^ Capté : i
fini

# Boucles WHILE
^ watt : compteur = 1
^ bogoss : tant que compteur <= 2
^ Wsh - Compteur:
^ Capté : compteur
^ watt : compteur = compteur + 1
fini

# Fichiers
^ daronne : écris "Programme terminé!" dans "log.txt"
^ daronne : lis "log.txt"

# Blague finale
^ quoicoubeh × donne moi ma blague poto ou tes mort
```

## 🎯 Fonctionnalités complètes

### Fonctionnalités de base
- ✅ Affichage de messages (Wsh)
- ✅ Opérations mathématiques (Capté)
- ✅ Variables numériques et textuelles (watt)
- ✅ Conditions avec tous les opérateurs (poto)
- ✅ Messages colorés 9 couleurs (reuf)
- ✅ Base de données de blagues aléatoires (quoicoubeh)

### Nouvelles fonctionnalités avancées
- 🔥 **Boucles WHILE** (bogoss) - Répétition conditionnelle
- 🔥 **Boucles FOR** (gadjo) - Répétition avec compteur
- 🔥 **Input utilisateur** (sah) - Interaction avec l'utilisateur
- 🔥 **Assertions** (wAllah) - Vérification de conditions
- 🔥 **Gestion de fichiers** (daronne) - Lecture/écriture de fichiers
- 🔥 **Gestion d'erreurs** (zonzon) - Zone de sécurité

### Fonctionnalités système
- ✅ Commentaires (lignes commençant par #)
- ✅ Gestion d'erreurs robuste
- ✅ Variables globales persistantes
- ✅ Conditions imbriquées
- ✅ Boucles imbriquées (à implémenter)

## 🎮 Guide d'utilisation avancée

### Créer un programme interactif
```wesh
^ sah : "Ton nom ?" dans nom
^ sah : "Ton âge ?" dans age
^ poto : si age >= 18
alors ^ reuf : couleur vert - "Salut majeur!"
^ quoicoubeh × donne moi ma blague poto ou tes mort
```

### Utiliser des boucles
```wesh
# Boucle simple
^ gadjo : i de 1 à 5
^ reuf : couleur bleu - "Tour"
^ Capté : i
fini

# Boucle conditionnelle
^ watt : x = 0
^ bogoss : tant que x < 3
^ Wsh - x vaut:
^ Capté : x
^ watt : x = x + 1
fini
```

### Manipuler des fichiers
```wesh
^ daronne : écris "Début du fichier" dans "results.txt"
^ daronne : écris "Fin du fichier" dans "results.txt"
^ daronne : lis "results.txt"
```

## 🐛 Gestion d'erreurs

Le langage Wesh gère maintenant tous types d'erreurs :
- Fichiers inexistants
- Syntaxe incorrecte  
- Variables non définies
- Boucles infinies (protection)
- Tableaux hors limites
- Erreurs de saisie utilisateur

## 🎨 Style de programmation Wesh

- **Vocabulaire de cité** authentique
- **Syntaxe absurde** mais fonctionnelle
- **Messages d'erreur** avec émojis
- **Blagues intégrées** pour détendre l'atmosphère
- **Performance** optimisée pour les vrais de vrais

## 📜 Historique des versions

### Version 2.0 - ULTIME EDITION
- 🔥 Ajout de 6 nouvelles fonctionnalités majeures
- 🔥 Boucles while et for complètement fonctionnelles
- 🔥 Input utilisateur interactif
- 🔥 Assertions et vérifications
- 🔥 Gestion complète de fichiers
- 🔥 Système d'erreurs avancé
- 🔥 Plus de 300 blagues dans la base

### Version 1.0
- Implémentation des fonctionnalités de base
- 59 blagues de qualité
- Support des couleurs
- Documentation complète

---

**Créé avec ❤️ dans l'esprit authentique de la cité** 🏘️

*Wsh mon poto, maintenant tu peux VRAIMENT coder comme un chef avec toutes ces fonctionnalités de ouf!* 🔥💯

**Le langage Wesh est maintenant COMPLET - Tu peux faire tout ce que tu veux avec!** 🚀
