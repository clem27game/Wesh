
# 🔥 Langage de programmation WESH 🔥

## Description

**Wesh** est un langage de programmation ésotérique inspiré du vocabulaire de la cité. Il permet d'écrire des programmes avec une syntaxe absurde et amusante tout en gardant les fonctionnalités de base d'un langage de programmation.

## 🚀 Installation et compilation

### Prérequis
- Compilateur C (gcc ou clang)
- Make

### Compilation
```bash
make
```

### Exécution
```bash
./main wsh <fichier.wsh>
```

## 📝 Syntaxe du langage

Tous les fichiers Wesh doivent avoir l'extension `.wsh` et chaque commande doit commencer par `^`.

### 1. **Wsh** - Affichage de messages

Affiche un message dans la console (équivalent de "Hello World").

**Syntaxe :**
```wesh
^ Wsh - hello world
^ Wsh - "Salut mon poto"
```

**Exemples :**
```wesh
^ Wsh - Bonjour tout le monde!
^ Wsh - "Message avec guillemets"
```

### 2. **Capté** - Mathématiques

Effectue des opérations mathématiques de base (addition, soustraction, multiplication, division).

**Syntaxe :**
```wesh
^ Capté : [expression]
```

**Exemples :**
```wesh
^ Capté : 4 + 7          # Affiche 11
^ Capté : 10 - 3         # Affiche 7
^ Capté : 5 * 6          # Affiche 30
^ Capté : 20 / 4         # Affiche 5
^ Capté : age + 5        # Utilise une variable
```

### 3. **quoicoubeh** - Blagues aléatoires

Affiche une blague aléatoire parmi une base de données de blagues.

**Syntaxe (exacte obligatoire) :**
```wesh
^ quoicoubeh × donne moi ma blague poto ou tes mort
```

**Exemple :**
```wesh
^ quoicoubeh × donne moi ma blague poto ou tes mort
# Sortie: 🤣 Voici une blague pour toi:
# 💬 Pourquoi les plongeurs plongent-ils toujours en arrière...
```

### 4. **watt** - Définition de variables

Permet de définir des variables numériques ou textuelles.

**Syntaxe :**
```wesh
^ watt : [nom_variable] = [valeur]
```

**Exemples :**
```wesh
^ watt : age = 16
^ watt : nom = "Kevin"
^ watt : score = 100
```

### 5. **poto** - Conditions

Permet de créer des conditions avec tous les opérateurs de comparaison.

**Syntaxe :**
```wesh
^ poto : si [condition]
alors  [commande]
```

**Opérateurs supportés :**
- `<` (inférieur)
- `>` (supérieur)
- `<=` (inférieur ou égal)
- `>=` (supérieur ou égal)
- `==` (égal)
- `!=` (différent)

**Exemples :**
```wesh
^ watt : age = 16
^ poto : si age < 18
alors  ^ Wsh - "Tu es mineur!"

^ poto : si score >= 100
alors  ^ reuf : couleur vert - "Score parfait!"
```

### 6. **reuf** - Messages colorés

Affiche des messages avec des couleurs.

**Syntaxe :**
```wesh
^ reuf : couleur [couleur] - "[message]"
```

**Couleurs disponibles :**
- rouge
- vert
- bleu
- jaune
- rose (ou pink)
- cyan
- blanc
- violet
- orange

**Exemples :**
```wesh
^ reuf : couleur rouge - "Message en rouge"
^ reuf : couleur bleu - "Message en bleu"
^ reuf : couleur vert - "Message en vert"
```

### 7. **Cité** - Délais

Crée une pause dans l'exécution du programme.

**Syntaxe :**
```wesh
^ Cité - [délai] ms
```

**Exemples :**
```wesh
^ Cité - 500 ms          # Pause de 500 millisecondes
^ Cité - 1500 ms         # Pause de 1.5 seconde
```

### 8. **crampté** - Modification de message

Affiche un message initial, attend un délai, puis le remplace par un message final.

**Syntaxe :**
```wesh
^ crampté - "[message_initial]", [délai] ms , "[message_final]"
```

**Exemples :**
```wesh
^ crampté - "Chargement...", 500 ms , "Chargement terminé"
^ crampté - "Patientez...", 2000 ms , "C'est prêt!"
```

## 💾 Exemple complet

```wesh
# Programme de démonstration Wesh
^ Wsh - Salut mon poto, bienvenue dans le langage Wesh!

# Variables
^ watt : age = 16
^ watt : nom = "Kevin"

# Mathématiques
^ Wsh - Calculs:
^ Capté : 10 + 5
^ Capté : age * 2

# Conditions
^ poto : si age < 18
alors  ^ reuf : couleur rouge - "Tu es mineur!"

# Délai et modification
^ crampté - "Chargement...", 1000 ms , "Terminé!"

# Blague
^ quoicoubeh × donne moi ma blague poto ou tes mort

^ Wsh - À plus dans le bus poto!
```

## 🎯 Fonctionnalités

- ✅ Affichage de messages
- ✅ Opérations mathématiques (+ - * /)
- ✅ Variables numériques et textuelles
- ✅ Conditions avec tous les opérateurs
- ✅ Messages colorés (9 couleurs)
- ✅ Délais temporels
- ✅ Modification de messages avec délai
- ✅ Base de données de blagues aléatoires
- ✅ Commentaires (lignes commençant par #)

## 🐛 Gestion d'erreurs

Le langage Wesh gère les erreurs suivantes :
- Fichier inexistant
- Syntaxe incorrecte
- Variables non définies
- Division par zéro
- Couleurs non supportées

## 🎮 Exemples d'utilisation

### Programme simple
```bash
./main wsh example.wsh
```

### Créer votre propre programme
1. Créez un fichier avec l'extension `.wsh`
2. Écrivez votre code en utilisant la syntaxe Wesh
3. Exécutez avec `./main wsh votre_fichier.wsh`

## 🎨 Style de programmation

Le langage Wesh encourage un style de programmation décontracté avec :
- Vocabulaire de la cité
- Syntaxe absurde mais fonctionnelle
- Messages d'erreur avec émojis
- Blagues intégrées pour détendre l'atmosphère

## 📜 Historique des versions

### Version 1.0
- Implémentation complète de toutes les fonctionnalités
- Base de données de 59 blagues
- Support des couleurs étendues
- Gestion robuste des erreurs
- Documentation complète

---

**Créé avec ❤️ dans l'esprit de la cité** 🏘️

*Wsh mon poto, maintenant tu peux coder comme un chef!* 🔥
