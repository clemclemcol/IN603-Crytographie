# IN6038-Crytographie

Compilation et exécution du code:

  > **make chiff** 
   *permet la compilation et l'exécution du chiffrement avec pour message et clé : 000000 000000*
  
  >**make dechiff**
  *permet la compilation et l'exécution du déchiffrement avec pour message et clé : bb57e6 000000*
  
  >**make att**
  *permet la compilation et l'exécution de l'attaque par le milieu avec pour couple de clair-chiffré : 8c8a4f a780e8*
 
 *Pour modifier les valeurs des messages et des clés, il faut les modifier dans le makefile, où faire :
  **make chiffrement** suivit de **./chiff <message> <clé>***
  **make dechiffrement** suivit de **./dechiff <message> <clé>***
  **make attaque** suivit de **./att <clair> <chiffré>***

