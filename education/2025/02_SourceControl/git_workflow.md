# Git Workflow Guide

Git is a distributed version control system that helps teams track changes to their projects. This guide walks through the core Git workflow students should master, from creating new files to collaborating with others using branches and remote repositories.

## 1. Understanding Repository States

Every file in a Git repository moves through three main states:

- **Untracked** – Files that exist in your working directory but are unknown to Git. Use `git status` to list them.
- **Tracked (Unmodified or Modified)** – Files that Git already knows about. They may be unchanged, or they may contain new edits.
- **Staged** – Files that are ready to be included in the next commit. Staging creates a snapshot of the file at that moment.

Use `git status` often to see where your files are in this lifecycle.

## 2. Recording Changes

### 2.1 Create or Edit Files
When you add a new file or modify an existing one, Git marks it as untracked or modified. Example:
```bash
echo "Hello Git" > hello.txt
```

### 2.2 Inspect the Working Tree
Before staging, confirm what has changed:
```bash
git status
git diff            # Shows unstaged changes
git diff --staged   # Shows staged changes
```

### 2.3 Stage Changes
Move selected changes into the staging area so they are ready to commit:
```bash
git add hello.txt        # Stage a specific file
git add .                # Stage everything in the current directory
```
Staging lets you control exactly what will be saved in the next commit.

### 2.4 Commit Changes
A commit permanently records a snapshot of the staged changes. Write clear messages explaining *why* you made the change.
```bash
git commit -m "Add greeting file"
```
Each commit forms part of the project history and can be revisited or reverted later.

## 3. Working with History

- `git log` – View the commit history.
- `git show <commit>` – Inspect a specific commit.
- `git restore --staged <file>` – Unstage a file if you change your mind.
- `git restore <file>` – Discard unstaged changes (use with caution).

## 4. Collaborating with Remotes

Remote repositories (like GitHub) allow you to share work.

### 4.1 Configure the Remote
Remotes are usually set up once per repository:
```bash
git remote add origin https://github.com/username/project.git
```
Check remotes with `git remote -v`.

### 4.2 Fetch and Pull
Keep your local repository up to date with remote changes:
```bash
git fetch             # Downloads new commits without merging
git pull              # Fetches and merges into the current branch
```

### 4.3 Push Local Commits
After committing locally, share your work:
```bash
git push origin main
```
Replace `main` with the branch you are working on.

If this is the first push of a new branch, include `-u` to set the upstream relationship:
```bash
git push -u origin feature/login-form
```

## 5. Branching and Merging

Branches let you develop features independently from the main line of work.

### 5.1 Create and Switch Branches
```bash
git branch            # List branches
git switch -c feature/login-form   # Create and switch to a new branch
git switch main                     # Switch back to main
```

### 5.2 Keep Branches Updated
While on your feature branch, regularly merge or rebase changes from `main` to avoid conflicts later:
```bash
git switch feature/login-form
git fetch origin
git merge origin/main              # or: git rebase origin/main
```

### 5.3 Merge Branches
When the feature is ready, merge it into the target branch (often `main`):
```bash
git switch main
git merge feature/login-form
```
Resolve any merge conflicts, test, then push the updated main branch.

### 5.4 Delete Branches
After merging, clean up old branches:
```bash
git branch -d feature/login-form      # Delete local branch
git push origin --delete feature/login-form   # Delete remote branch
```

## 6. Daily Workflow Checklist

1. **Pull** the latest changes from the remote repository.
2. **Create or switch** to a branch for your work.
3. **Edit files** to implement your changes.
4. **Review changes** with `git status` and `git diff`.
5. **Stage** the exact changes you want to save with `git add`.
6. **Commit** with a descriptive message.
7. **Push** your branch to share your work or open a pull request.
8. **Merge** once the work is reviewed and tested.

## 7. Additional Tips

- Commit early and often to capture logical units of work.
- Write informative commit messages that explain the intent of the change.
- Use `.gitignore` to exclude files that should not be version-controlled (build artifacts, secrets, etc.).
- Review your history before pushing to ensure it accurately represents your work.

Mastering these steps will help you collaborate effectively and maintain a clean, understandable project history.
