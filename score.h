
int recupScore(FILE *fichierScore, int recordActuel){
  
  
  
  //recuperation du record actuel
    fichierScore = fopen("score.txt", "r");
    if (fichierScore == NULL){
      
      perror("Error opening file");
    }
    else{
       
       fscanf(fichierScore, "%d", &recordActuel);
        if (ferror (fichierScore)){     
            
            printf("erreur ecriture score.txt\n");
        }
        fclose(fichierScore);
    }
    
    return recordActuel;
  
}


void newScore(int nbEnnemisTues, FILE *fichierScore, int recordActuel){
  
  
  //score
    
    fichierScore = fopen("score.txt", "w+");
    
    if (fichierScore == NULL){
     
        perror("Error opening file");
    }

    else{
       
        fscanf(fichierScore, "%d", &recordActuel);
        if (nbEnnemisTues >= recordActuel){
        
            fprintf (fichierScore , "%d" ,nbEnnemisTues);
        }
        else{
	  
            fprintf (fichierScore, "%d", recordActuel);
        }
        if (ferror (fichierScore)){
        
            printf("erreur ecriture score.txt\n");
        }

        fclose(fichierScore);
    }
  
  
  
  
}