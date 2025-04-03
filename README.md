# 🛠️ Planification d'Interventions Techniques

Projet console en C++ mettant en œuvre plusieurs **Design Patterns** pour simuler un système de gestion d'interventions techniques.

---

## 🚀 Fonctionnalités principales

- Création d'interventions (`Maintenance`, `Urgence`, etc.)
- Ajout dynamique de fonctionnalités (`Suivi GPS`, `Pièces jointes`)
- Centralisation via une façade
- Notifications automatiques via Observer
- Gestion des droits via Proxy

---

## 📦 Structure du projet

Projet_Design_Patterns/
│
├── include/              
│   ├── interventions/    
│   ├── patterns/         
│   ├── utilisateur/      
│   └── roles/            
│
├── src/                  
├── .dist/                
└── README.md            

---

## 🧠 Design Patterns utilisés

| Pattern        | Description |
|----------------|-------------|
| **Factory Method** | Crée dynamiquement des interventions de type `Maintenance`, `Urgence`, etc. |
| **Decorator**       | Ajoute des options comme le `Suivi GPS` ou les `Pièces jointes` sans modifier la classe de base. |
| **Facade**          | `GestionnaireInterventions` simplifie la manipulation des interventions. |
| **Observer**        | Notifie automatiquement la console à chaque action significative. |
| **Proxy**           | Vérifie les rôles des utilisateurs (`LECTURE` / `ECRITURE`) avant d'autoriser certaines actions. |

---

## 📂 Exemple d'exécution

```bash
=== Bienvenue dans le système de planification d'interventions ===

[Notification] Nouvelle intervention créée : Maintenance
[Notification] Nouvelle intervention créée : Urgence
⛔ Accès refusé à Michel : rôle lecture uniquement.

=== Liste des interventions ===
- Maintenance | Intervention de maintenance préventive
- Urgence | Intervention d'urgence immédiate