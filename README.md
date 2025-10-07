```markdown
# minishell - 42 School Project

## 📋 Description
minishell est un projet avancé du tronc commun à 42 qui consiste à créer un shell UNIX complet en C. Ce projet synthétise toutes les compétences acquises précédemment pour développer un interpréteur de commandes fonctionnel.

## 🎯 Objectifs
- Recréer un shell UNIX compatible avec bash
- Implémenter le parsing et l'exécution de commandes complexes
- Gérer les processus, signaux et redirections
- Comprendre le fonctionnement interne d'un shell

## 🛠️ Technologies Utilisées

### 🔧 Système
- **Processus** - fork(), execve(), waitpid()
- **Signaux** - Gestion de Ctrl-C, Ctrl-D, Ctrl-\
- **Pipes et redirections** - |, <, >, >>
- **Variables d'environnement** - getenv(), setenv()

### 📝 Parsing
- **Lexer** - Tokenisation de l'entrée utilisateur
- **Parser** - Construction de l'arbre syntaxique
- **Expansion** - Variables ($HOME, $PATH) et wildcards (*)

## 🚀 Installation et Utilisation

### 📋 Compilation
```bash
git clone [URL-du-repository]
cd minishell
make
```

### ⚙️ Utilisation
```bash
./minishell
# Lance le shell personnalisé
```

## 📊 Fonctionnalités Implémentées

### 💻 Commandes Built-in
- **echo** - Avec option -n
- **cd** - Changement de répertoire
- **pwd** - Affichage du répertoire courant
- **export** - Définition de variables d'environnement
- **unset** - Suppression de variables
- **env** - Affichage de l'environnement
- **exit** - Sortie du shell

### 🔄 Exécution Avancée
- **Pipes multiples** - cmd1 | cmd2 | cmd3
- **Redirections** - <, >, >>, heredoc (<<)
- **Séparation par ;** - Commandes séquentielles
- **Variables d'environnement** - Expansion des $VAR

### 🛡️ Gestion des Erreurs
- **Syntax error** - Détection des commandes mal formées
- **Command not found** - Gestion des commandes inexistantes
- **Permission denied** - Gestion des droits
- **Signaux** - Ctrl-C, Ctrl-D, Ctrl-\

## 💡 Compétences Développées
- Programmation système avancée
- Gestion complexe de processus
- Parsing et interprétation de langage
- Gestion des entrées/sorties et pipes
- Traitement des signaux UNIX
- Débogage de programmes complexes
- Gestion de la mémoire à grande échelle

## 🎯 Fonctionnalités Principales

### 📝 Exemples Supportés
```bash
# Pipes et redirections
ls -l | grep ".c" > output.txt

# Heredoc
cat << EOF > file.txt
ligne 1
ligne 2
EOF

# Variables et commandes complexes
echo $PATH | tr ':' '\n'
```

### 🔧 Gestion des Signaux
- **Ctrl-C** - Interrompt la commande en cours
- **Ctrl-D** - Sort proprement du shell
- **Ctrl-\** - Ne fait rien (comme bash)
- **Heredoc** - Ctrl-C interrompt l'input

## 📁 Structure du Projet
```
minishell/
├── srcs/
│   ├── exec/        # Pipes, redirections
│   ├── utils/       # Fonctions utilitaires
│   ├── builtins/    
│   ├── command/    
│   ├── init_env/    
│   ├── init_minishell/    
│   ├── tokenizer/    
├── includes/        # Fichiers d'en-tête
├── Makefile         # Système de compilation
└── README.md        # Documentation
```

Ce projet représente l'aboutissement du tronc commun et démontre une maîtrise complète de la programmation système en C.
```
