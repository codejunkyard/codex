# Environnements de développement pour ce cours

L'ensemble des outils de ce cours s'articule autour de **Visual Studio Code (VS Code)**. Que vous travailliez entièrement dans le cloud ou sur votre propre matériel, nous comptons sur l'interface cohérente de VS Code, ses extensions et son terminal intégré pour maintenir des habitudes de travail familières.

## Codespaces (point de départ principal)
- **Ce que c'est :** GitHub Codespaces fournit un environnement de développement hébergé dans le cloud qui se lance directement depuis votre dépôt.
- **Pourquoi nous l'utilisons en premier :**
  - Mise à disposition instantanée avec VS Code dans le navigateur ou l'application de bureau.
  - Configuration identique pour chaque étudiant, ce qui minimise les problèmes d'installation.
  - Ressources de calcul intégrées et outils préconfigurés adaptés à ce programme.
- **Rôle dans le cours :** Tous les exercices et exemples initiaux partent du principe que vous travaillez dans un Codespace afin que nous puissions entrer rapidement dans le contenu sans perdre de temps sur la configuration locale.

## Windows 11 avec VS Code Desktop
- **Ce que c'est :** Développer directement sur une installation Windows 11 en utilisant l'application VS Code native.
- **Points d'attention :**
  - Certains outils en ligne de commande se comportent différemment par rapport aux environnements de type Unix.
  - Nécessite l'installation manuelle des langages et des outils.
  - Convient bien pour les outils graphiques ou les flux de travail spécifiques à Windows.
- **Contexte du cours :** Bien que Windows 11 puisse héberger VS Code confortablement, nous recommandons de l'associer à Windows Subsystem for Linux (WSL) pour se rapprocher des instructions basées sur Linux utilisées tout au long du cours.

## Windows Subsystem for Linux (WSL) sur Windows 11
- **Ce que c'est :** Un environnement Linux virtualisé léger qui s'exécute parallèlement à Windows et reste accessible directement depuis VS Code.
- **Avantages :**
  - Offre une véritable expérience de ligne de commande Linux sans quitter Windows.
  - S'intègre étroitement à VS Code via les extensions Remote Development.
  - Prend en charge les mêmes outils et scripts que nous utilisons dans Codespaces, ce qui rend la transition transparente.
- **Feuille de route du cours :** Après vous être familiarisé avec Codespaces, nous vous guiderons dans la configuration de WSL afin que vous puissiez reproduire les mêmes flux de travail en local tout en profitant de Windows pour les tâches quotidiennes.

## Distribution Linux native
- **Ce que c'est :** Installer VS Code sur une distribution Linux dédiée telle qu'Ubuntu, Fedora ou Debian.
- **Points forts :**
  - Contrôle maximal de l'environnement système avec un accès direct aux outils Linux.
  - Souvent privilégié par les utilisateurs avancés qui souhaitent une personnalisation complète et une utilisation efficace des ressources.
- **Point de vue du cours :** Cette option reflète les environnements utilisés dans l'industrie et dans Codespaces. Vous êtes libre d'utiliser un système Linux natif si vous en disposez déjà, mais les instructions d'intégration se concentreront sur Codespaces et WSL.

## macOS avec VS Code
- **Ce que c'est :** Exécuter VS Code sur macOS avec le terminal de type Unix intégré et sa chaîne d'outils.
- **Points clés :**
  - Excellente prise en charge de la ligne de commande via zsh et Homebrew pour la gestion des paquets.
  - Performances fluides sur Apple Silicon et forte intégration avec les fonctionnalités de macOS.
- **Point de vue du cours :** macOS peut suivre la plupart des instructions orientées Linux avec des ajustements mineurs. Vous pouvez utiliser macOS s'il s'agit de votre machine principale, même si les démonstrations officielles continueront de se concentrer sur Codespaces et WSL afin de conserver une cohérence au sein de la cohorte.

## Résumé de la progression
1. **Commencez dans Codespaces** afin que chacun dispose du même environnement de base et des mêmes outils dans VS Code.
2. **Passez à WSL sur Windows 11** dès que vous êtes prêt à reproduire localement le flux de travail basé sur Linux.
3. **Explorez les configurations Linux natives ou macOS** si vous avez besoin de flexibilité supplémentaire ou si vous maîtrisez déjà la gestion de ces systèmes.

En standardisant notre travail sur VS Code et en définissant clairement nos environnements cibles, nous pouvons consacrer plus de temps à maîtriser le contenu du cours et moins de temps à résoudre des problèmes de configuration locale.
