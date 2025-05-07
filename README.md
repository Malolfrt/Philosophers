# 🧠 Philosophers - Projet 42

## 📌 Description

**Philosophers** est un projet de synchronisation concurrente du cursus **42**.  
L’objectif est de simuler le **problème classique des philosophes** en utilisant **les threads et les mutex** pour gérer l’accès concurrent aux ressources (les fourchettes).  
Ce projet permet d’apprendre à gérer les **problèmes de concurrence**, les **deadlocks**, la **précision du timing**, et l’**ordre d’exécution des threads**.

---

## 🪑 Problème des philosophes

- **N philosophes** sont assis autour d’une table circulaire.
- Entre chaque philosophe se trouve une **fourchette**.
- Chaque philosophe a le même cycle :
  1. **Penser**
  2. **Prendre la fourchette gauche**
  3. **Prendre la fourchette droite**
  4. **Manger**
  5. **Poser les fourchettes**
  6. **Dormir**

Le défi est de s’assurer qu’ils **ne meurent pas de faim** et que **la simulation est fluide et cohérente**, sans conditions de course ou blocages.

---

## ⚙️ Compilation

./philo nombre_de_philosophes temps_pour_mourir temps_pour_manger temps_pour_dormir (nombre_de_repas_pour_chaque_philo)

```bash
$ git clone https://github.com/vmondor/philosophers.git
  cd philosophers && cd philo
  make
  ./philo 5 800 200 200 7