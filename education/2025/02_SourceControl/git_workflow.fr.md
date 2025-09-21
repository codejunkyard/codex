# Guide du flux de travail Git

Git est un système de contrôle de version distribué qui aide les équipes à suivre les modifications apportées à leurs projets. Ce guide présente le flux de travail Git que les étudiantes et étudiants doivent maîtriser, depuis la création de nouveaux fichiers jusqu'à la collaboration avec d'autres personnes à l'aide de branches et de dépôts distants.

## 1. Comprendre les états d'un dépôt

Chaque fichier d'un dépôt Git passe par trois états principaux :

- **Non suivi** – Fichiers présents dans votre répertoire de travail mais inconnus de Git. Utilisez `git status` pour les lister.
- **Suivi (non modifié ou modifié)** – Fichiers que Git connaît déjà. Ils peuvent être inchangés ou contenir de nouvelles modifications.
- **Indexé** – Fichiers prêts à être inclus dans le prochain commit. L'indexation capture un instantané du fichier à cet instant.

Utilisez souvent `git status` pour vérifier où se trouvent vos fichiers dans ce cycle de vie.

## 2. Enregistrer des modifications

### 2.1 Créer ou modifier des fichiers
Lorsque vous ajoutez un nouveau fichier ou modifiez un fichier existant, Git le marque comme non suivi ou modifié. Exemple :
```bash
echo "Hello Git" > hello.txt
```

### 2.2 Inspecter l'arborescence de travail
Avant d'indexer, confirmez ce qui a changé :
```bash
git status
git diff            # Affiche les modifications non indexées
git diff --staged   # Affiche les modifications indexées
```

### 2.3 Indexer des modifications
Déplacez les modifications sélectionnées vers la zone d'index afin qu'elles soient prêtes à être commit :
```bash
git add hello.txt        # Indexer un fichier spécifique
git add .                # Indexer tout le contenu du répertoire courant
```
L'indexation vous permet de contrôler exactement ce qui sera enregistré dans le prochain commit.

### 2.4 Valider les modifications
Un commit enregistre de manière permanente un instantané des modifications indexées. Rédigez des messages clairs expliquant *pourquoi* vous avez effectué le changement.
```bash
git commit -m "Add greeting file"
```
Chaque commit fait partie de l'historique du projet et peut être revisité ou annulé plus tard.

## 3. Travailler avec l'historique

- `git log` – Affiche l'historique des commits.
- `git show <commit>` – Inspecte un commit spécifique.
- `git restore --staged <file>` – Retire un fichier de l'index si vous changez d'avis.
- `git restore <file>` – Abandonne les modifications non indexées (à utiliser avec prudence).

## 4. Collaborer avec des dépôts distants

Les dépôts distants (comme GitHub) vous permettent de partager votre travail.

### 4.1 Configurer le dépôt distant
Les dépôts distants sont généralement configurés une fois par dépôt :
```bash
git remote add origin https://github.com/username/project.git
```
Vérifiez les dépôts distants avec `git remote -v`.

### 4.2 Récupérer et fusionner
Maintenez votre dépôt local à jour avec les modifications distantes :
```bash
git fetch             # Télécharge les nouveaux commits sans fusionner
git pull              # Récupère et fusionne dans la branche courante
```

### 4.3 Pousser les commits locaux
Après avoir validé localement, partagez votre travail :
```bash
git push origin main
```
Remplacez `main` par la branche sur laquelle vous travaillez.

Si c'est la première fois que vous poussez une nouvelle branche, ajoutez `-u` pour définir la branche de suivi :
```bash
git push -u origin feature/login-form
```

## 5. Branches et fusion

Les branches permettent de développer des fonctionnalités indépendamment de la ligne principale de travail.

### 5.1 Créer et changer de branche
```bash
git branch            # Lister les branches
git switch -c feature/login-form   # Créer et passer à une nouvelle branche
git switch main                     # Revenir sur main
```

### 5.2 Garder les branches à jour
Sur votre branche de fonctionnalité, fusionnez ou rebasez régulièrement les modifications de `main` pour éviter les conflits plus tard :
```bash
git switch feature/login-form
git fetch origin
git merge origin/main              # ou : git rebase origin/main
```

### 5.3 Fusionner les branches
Lorsque la fonctionnalité est prête, fusionnez-la dans la branche cible (souvent `main`) :
```bash
git switch main
git merge feature/login-form
```
Résolvez les conflits de fusion, testez, puis poussez la branche main mise à jour.

### 5.4 Supprimer des branches
Après la fusion, nettoyez les anciennes branches :
```bash
git branch -d feature/login-form      # Supprimer la branche locale
git push origin --delete feature/login-form   # Supprimer la branche distante
```

## 6. Liste de contrôle quotidienne

1. **Récupérez** les dernières modifications depuis le dépôt distant.
2. **Créez ou changez** de branche pour votre travail.
3. **Modifiez les fichiers** pour implémenter vos changements.
4. **Passez en revue les modifications** avec `git status` et `git diff`.
5. **Indexez** précisément les changements à conserver avec `git add`.
6. **Validez** avec un message descriptif.
7. **Poussez** votre branche pour partager votre travail ou ouvrir une pull request.
8. **Fusionnez** une fois le travail relu et testé.

## 7. Conseils supplémentaires

- Commitez tôt et souvent pour capturer des unités de travail cohérentes.
- Rédigez des messages de commit informatifs qui expliquent l'intention du changement.
- Utilisez `.gitignore` pour exclure les fichiers qui ne doivent pas être suivis (artefacts de build, secrets, etc.).
- Passez en revue votre historique avant de pousser afin de vérifier qu'il reflète fidèlement votre travail.

Maîtriser ces étapes vous aidera à collaborer efficacement et à maintenir un historique de projet clair et compréhensible.
