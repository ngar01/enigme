#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
void deplacement_selection(int* choix, int* ligne, int* son, int* continuer, Mix_Chunk* button);
void update_affichage(int choix, int ligne, int son, SDL_Rect positionEnigme, SDL_Surface* ecran, SDL_Surface* imageDeFond, SDL_Surface*enigme);
void recuperation_enigme(char qcm[],int i);
void recuperation_reponses(char rep1[], char rep2[], char rep3[], char rep4[], int i);
void recuperation_tabRep(int reponse[]);
void recuperation_texte(char qcm[], char rep1[], char rep2[], char rep3[], char rep4[], int i);
void validation(int choix, int ligne, int reponse[], SDL_Rect positionEnigme, SDL_Surface *ecran,SDL_Surface* youWin, SDL_Surface* gameOver, Mix_Chunk* win, Mix_Chunk* lose);
void affichage_enigmes(SDL_Surface *ecran, SDL_Surface *question, SDL_Surface *r1, SDL_Surface *r2,SDL_Surface *r3,SDL_Surface *r4, char qcm[], char rep1[], char rep2[], char rep3[], char rep4[], TTF_Font *police, SDL_Color couleurNoire, SDL_Rect posQuestion,SDL_Rect posR1,SDL_Rect posR2,SDL_Rect posR3,SDL_Rect posR4);
void liberation(SDL_Surface *imageDeFond,SDL_Surface *enigme,SDL_Surface *question,SDL_Surface *r1,SDL_Surface *r2,SDL_Surface *r3,SDL_Surface *r4,SDL_Surface *youWin,SDL_Surface *gameOver,Mix_Music* backgroundSound,Mix_Chunk* button,Mix_Chunk *win,Mix_Chunk *lose);
#endif // FONCTION_H_INCLUDED
