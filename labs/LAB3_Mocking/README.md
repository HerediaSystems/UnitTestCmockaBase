# LAB3 MOCKING

Le module DRV_LED fourni fonctionne comme suit :
- Il utilise le module SYS_Timestamp comme base de temps.
- Il prend en compte 4 modes :
    - OFF (GPIO niveau bas)
    - ON  (GPIO niveau haut)
    - BLINK_FAST (GPIO toggle avec une periode rapide)
    - BLINK_SLOW (GPIO toggle avec une periode lente)
---
- les fonctions :
    - DRV_LED_task est prévu pour être appelé périodiquement (polling).
        - elle verifie que la date du prochaine évenement est expiré. (pas d'evenement dans les modes ON et OFF)
            - si oui, la GPIO est toggle
            - si non, rien ne se passe
    - DRV_LED_set permet de changer de mode.
        - lors du passage au mode OFF, la GPIO est passé au niveau bas
        - lors du passage au mode ON, la GPIO est passé au niveau haut
        - lors du passage au mode BLINK_FAST, la GPIO est passé au niveau bas, et la date du prochaine événement est défini
        - lors du passage au mode BLINK_FAST, la GPIO est passé au niveau bas, et la date du prochaine événement est défini
---

Le but du lab est:
- d'écrire les tests pour valider le fonctionnement de la fonction task (il est possible de se limiter à tester uniquement le mode BLINK_FAST)
- d'ecrire les tests pour valider la fonction DRV_LED_set

Pour cela, il faudra "mocker" les appels aux modules externes (SYS_timestamp et HAL_GPIO).

Une fois les tests écris et valide. Vous pouvez essayer d'injecter des erreur dans le code du DRV_LED pour voir si les test les détectent.

la documentation de l'API Cmocka peux etre utile :
https://api.cmocka.org/group__cmocka__mock.html
https://api.cmocka.org/group__cmocka__param.html

---

Observez dans CMakeLists.txt comment linker flags sont configuré pour utiliser les mocks
