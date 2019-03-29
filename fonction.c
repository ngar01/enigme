#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> 
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonction.h"
//--------------------------------------------------------------------------------------------------------------------------------
void deplacement_selection(int* choix, int* ligne, int* son, int* continuer, Mix_Chunk* button)
{
 SDL_Event event;
 SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event*/ 

        switch(event.type) /* On teste le type d'événement*/

        {

         case SDL_QUIT: /* Si c'est un événement QUITTER*/
                Mix_PlayChannel(-1,button,0);
                (*continuer) = 0; /* On met le booléen à 0, donc la boucle va s'arrêter*/ 

              break;
         case SDL_KEYDOWN:
               Mix_PlayChannel(-1,button,0);
              switch(event.key.keysym.sym)

              {

                  case SDLK_UP:
                      if ((*ligne)==1)
                         (*ligne)=4;
                      else
                         (*ligne)--;
                    break;

                  case SDLK_DOWN:
                      if ((*ligne)==4)
                         (*ligne)=1;
                      else
                         (*ligne)++;
                    break;

                  case  SDLK_RIGHT:
                      if ((*ligne)==4)
                         (*ligne)=1 ;
                      else
                         (*ligne)++;
                    break;

                  case SDLK_LEFT:
                      if ((*ligne)==1)
                         (*ligne)=4;
                      else
                         (*ligne)--;
                    break;

                  case SDLK_RETURN:
                      Mix_PlayChannel(-1,button,0); 
                     switch((*ligne))
                      {
                        case 1:
                         (*choix)=1;
                         break;
                        case 2:
                         (*choix)=2;
                         break;
                        case 3:
                         (*choix)=3;
                         break;
                        case 4:
                         (*choix)=4;
                         break;
                      }
                    break;

              }
              break;
         case SDL_MOUSEMOTION:
            if (event.motion.x>280 && event.motion.x<525 && event.motion.y>255 && event.motion.y<290)
            {
               (*ligne)=1;
                break;
            }

            else if (event.motion.x>280 && event.motion.x<525 && event.motion.y>300 && event.motion.y<335)
            {
                (*ligne)=2;
                break;
            }
            else if (event.motion.x>280 && event.motion.x<525 && event.motion.y>350 && event.motion.y<380)
            {
                (*ligne)=3;
                break;
            }
            else if (event.motion.x>280 && event.motion.x<525 && event.motion.y>395 && event.motion.y<425)
            {
                (*ligne)=4;
                break;
            }
           break;

         case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1,button,0);
           switch(event.button.button)
            {

             case SDL_BUTTON_LEFT :

                if ((*ligne)==1)
                {
                   (*choix)=1;
                  break;
                }
                if ((*ligne)==2)
                {
                   (*choix)=2;
                  break;
                }
                if ((*ligne)==3)
                {
                   (*choix)=3;
                  break;
                }
                if ((*ligne)==4)
                {
                   (*choix)=4;
                  break;
                }

              break;
            }
          break;
        }
(*son)=1;
}
//--------------------------------------------------------------------------------------------------------------------------------
void update_affichage(int choix, int ligne, int son, SDL_Rect positionEnigme, SDL_Surface* ecran, SDL_Surface* imageDeFond, SDL_Surface* enigme)
{

        if(ligne==1)
        {
            SDL_FreeSurface(enigme);
            enigme = IMG_Load("1.png");
            SDL_BlitSurface(enigme, NULL, ecran, &positionEnigme);
                  SDL_Flip(ecran);
        }

        if(ligne==2)
        {
            SDL_FreeSurface(enigme);
            enigme = IMG_Load("2.png");
            SDL_BlitSurface(enigme, NULL, ecran, &positionEnigme);
                  SDL_Flip(ecran);
        }
        if(ligne==3)
        {
            SDL_FreeSurface(enigme);
            enigme = IMG_Load("3.png");
            SDL_BlitSurface(enigme, NULL, ecran, &positionEnigme);
                  SDL_Flip(ecran);

        }
        if(ligne==4)
         {
            SDL_FreeSurface(enigme);
            enigme = IMG_Load("4.png");
            SDL_BlitSurface(enigme, NULL, ecran, &positionEnigme);
                  SDL_Flip(ecran);
         }
}
//--------------------------------------------------------------------------------------------------------------------------------
void recuperation_enigme(char qcm[],int i)
{
    int n=1;

    FILE *fichier;
    fichier=fopen("enigme.txt", "r");
    if(fichier!=NULL)
    {
        while(fgets((qcm),150,fichier)!=NULL && n!=(i))
        {

            n++;
        }
    }
    fclose(fichier);
}
//--------------------------------------------------------------------------------------------------------------------------------
void recuperation_reponses(char rep1[], char rep2[], char rep3[], char rep4[], int i)
{
 int n=1;

    FILE *fichier;
    fichier=fopen("reponses.txt", "r");
    if(fichier!=NULL)
    {
        while(fscanf(fichier,"%s %s %s %s", rep1, rep2, rep3, rep4)!=EOF && n!=(i))
        {

            n++;
        }
    }
    fclose(fichier);
}
//--------------------------------------------------------------------------------------------------------------------------------
void recuperation_tabRep(int reponse[])
{
int n=0;
    FILE *fichier;
    fichier=fopen("intRep.txt", "r");
    if(fichier!=NULL)
    {
        while(fscanf(fichier,"%d", &reponse[n] )!=EOF)
        {
            n++;
        }
    }
    fclose(fichier);

} 
//--------------------------------------------------------------------------------------------------------------------------------
void recuperation_texte(char qcm[], char rep1[], char rep2[], char rep3[], char rep4[], int i)
{
    recuperation_enigme(qcm, i);
    recuperation_reponses(rep1, rep2, rep3, rep4, i);
}
//--------------------------------------------------------------------------------------------------------------------------------
void validation(int choix, int ligne, int reponse[], SDL_Rect positionEnigme, SDL_Surface *ecran,SDL_Surface* youWin, SDL_Surface* gameOver, Mix_Chunk* win, Mix_Chunk* lose)
{
 int i=0, n;
for(i=0;i<ligne;i++)
{
  n=reponse[i];
}
switch(choix)
{
         case 1:
          if(n==1)
             {
               Mix_PlayChannel(-1,win,0);
               youWin = IMG_Load("youWin.png");
               SDL_BlitSurface(youWin, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
          else
             {
               Mix_PlayChannel(-1,lose,0);
               gameOver = IMG_Load("gameOver.png");
               SDL_BlitSurface(gameOver, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
         case 2:
          if(n==2)
             {
               Mix_PlayChannel(-1,win,0);
               youWin = IMG_Load("youWin.png");
               SDL_BlitSurface(youWin, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
          else
             {
               Mix_PlayChannel(-1,lose,0);
               gameOver = IMG_Load("gameOver.png");
               SDL_BlitSurface(gameOver, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
         case 3:
          if(n==3)
             {
               Mix_PlayChannel(-1,win,0);
               youWin = IMG_Load("youWin.png");
               SDL_BlitSurface(youWin, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
          else
             {
               Mix_PlayChannel(-1,lose,0);
               gameOver = IMG_Load("gameOver.png");
               SDL_BlitSurface(gameOver, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
         case 4:
          if(n==4)
             {
               Mix_PlayChannel(-1,win,0);
               youWin = IMG_Load("youWin.png");
               SDL_BlitSurface(youWin, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }
          else
             {
               Mix_PlayChannel(-1,lose,0);
               gameOver = IMG_Load("gameOver.png");
               SDL_BlitSurface(gameOver, NULL, ecran, &positionEnigme);
               SDL_Flip(ecran);
             }

}
}
//--------------------------------------------------------------------------------------------------------------------------------
void affichage_enigmes(SDL_Surface *ecran, SDL_Surface *question, SDL_Surface *r1, SDL_Surface *r2,SDL_Surface *r3,SDL_Surface *r4, char qcm[], char rep1[], char rep2[], char rep3[], char rep4[], TTF_Font *police, SDL_Color couleurNoire, SDL_Rect posQuestion,SDL_Rect posR1,SDL_Rect posR2,SDL_Rect posR3,SDL_Rect posR4)
{
   question = TTF_RenderText_Blended (police,qcm ,couleurNoire);
   SDL_BlitSurface(question, NULL, ecran, &posQuestion);
   r1 = TTF_RenderText_Blended (police,rep1 ,couleurNoire);
   SDL_BlitSurface(r1, NULL, ecran, &posR1);
   r2 = TTF_RenderText_Blended (police,rep2 ,couleurNoire);
   SDL_BlitSurface(r2, NULL, ecran, &posR2);
   r3 = TTF_RenderText_Blended (police,rep3 ,couleurNoire);
   SDL_BlitSurface(r2, NULL, ecran, &posR3);
   r4 = TTF_RenderText_Blended (police,rep4 ,couleurNoire);
   SDL_BlitSurface(r4, NULL, ecran, &posR4);
SDL_Flip(ecran);
}
//------------------------------------------------------------------------------------------------------------------------------
void liberation(SDL_Surface *imageDeFond,SDL_Surface *enigme,SDL_Surface *question,SDL_Surface *r1,SDL_Surface *r2,SDL_Surface *r3,SDL_Surface *r4,SDL_Surface *youWin,SDL_Surface *gameOver,Mix_Music* backgroundSound,Mix_Chunk* button,Mix_Chunk *win,Mix_Chunk *lose)
{
Mix_FreeMusic(backgroundSound);
Mix_FreeChunk(button);
Mix_FreeChunk(win);
Mix_FreeChunk(lose);
Mix_CloseAudio();
SDL_FreeSurface(imageDeFond );
SDL_FreeSurface(enigme);
SDL_FreeSurface(question);
SDL_FreeSurface(r1);
SDL_FreeSurface(r2);
SDL_FreeSurface(r3);
SDL_FreeSurface(r4);
SDL_FreeSurface(youWin);
SDL_FreeSurface(gameOver);
}
