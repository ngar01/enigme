#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> 
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fonction.h"

//--------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
int choix=0, ligne=1, son=0, continuer=1;
char qcm[150]; char rep1[20]; char rep2[20]; char rep3[20]; char rep4[20];
int i=1, reponse[20], ctn=1;
SDL_Surface *ecran = NULL, *imageDeFond = NULL, *enigme = NULL, *question = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL;
SDL_Event event;
SDL_Surface *youWin=NULL, *gameOver=NULL;
SDL_Rect positionFond , positionEnigme, posQuestion, posR1, posR2, posR3, posR4;
TTF_Font *police = NULL;
SDL_Color couleurNoire = {0, 0, 0};

//INITIALISATION DES POSITIONS
positionFond .x = 0;
positionFond .y = 0;
positionEnigme.x = (800/2)-(500/2);
positionEnigme.y = (600/2)-(300/2);
posQuestion.x=262;
posQuestion.y=192;
posR1.x=295.5;
posR1.y=274.5;
posR2.x=295.5;
posR2.y=317.5;
posR3.x=295.5;
posR3.y=364.5;
posR4.x=295.5;
posR4.y=408.5;


SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);

//INITIALISATION SONS
Mix_Music* backgroundSound = NULL ;
Mix_Chunk* button, *win, *lose;
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

backgroundSound = Mix_LoadMUS("game.mp3");
button=Mix_LoadWAV("bouton.wav");
win=Mix_LoadWAV("ff-bell.wav");
lose=Mix_LoadWAV("fail.wav");

//INIT TEXTE
TTF_Init();
police = TTF_OpenFont("UbuntuMono.ttf", 16);

//SDL_WM_SetIcon(IMG_Load ("sdl_icone.bmp"), NULL);
ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
SDL_WM_SetCaption("OUT OF CONTROL", NULL);
imageDeFond = IMG_Load ("fond.png");
SDL_BlitSurface(imageDeFond , NULL, ecran, &positionFond );

//RECUPERATION DES BONNES REPONSES
 recuperation_tabRep(reponse);

//1ere recuperation des enigmes;
recuperation_texte(qcm, rep1, rep2, rep3, rep4, i);


/* Chargement d'un PNG avec IMG_Load
Celui-ci est automatiquement rendu transparent car les informations
de
transparence sont codées à l'intérieur du fichier PNG */
enigme = IMG_Load ("1.png");
SDL_BlitSurface(enigme, NULL, ecran, &positionEnigme);
SDL_Flip(ecran);

//1er affichage des enigmes
affichage_enigmes(ecran, question, r1, r2, r3, r4, qcm, rep1, rep2, rep3, rep4, police, couleurNoire, posQuestion, posR1, posR2, posR3, posR4);

while (continuer)
{
choix=0;
recuperation_texte(qcm, rep1, rep2, rep3, rep4, i);
deplacement_selection(&choix, &ligne, &son, &continuer, button);
update_affichage(choix, ligne, son, positionEnigme, ecran, imageDeFond, enigme,positionFond);
affichage_enigmes(ecran, question, r1, r2, r3, r4, qcm, rep1, rep2, rep3, rep4, police, couleurNoire, posQuestion, posR1, posR2, posR3, posR4);
validation(choix, ligne, reponse, positionEnigme, ecran, youWin, gameOver, win, lose);
if(choix!=0)
{
ctn=1;
 while(ctn)
 {
    SDL_WaitEvent(&event);
    switch(event.type)
     {
        case SDL_QUIT: /* Si c'est un événement QUITTER*/
                Mix_PlayChannel(-1,button,0);
                continuer=0;
                ctn=0;
           break;
        case SDL_KEYDOWN:
           Mix_PlayChannel(-1,button,0);
           if(event.key.keysym.sym==SDLK_RETURN)
             {
                ctn=0;
             }
         break;
       case SDL_MOUSEBUTTONDOWN:
           Mix_PlayChannel(-1,button,0);
           if(event.button.button==SDL_BUTTON_LEFT)
            {
                ctn=0;
             }
        break; 
     }
 }
} 
 if(choix!=0)
      {
          i++;
      }
}
TTF_CloseFont(police);
TTF_Quit();
void liberation(imageDeFond, enigme, question, r1, r2, r3, r4, youWin, gameOver, backgroundSound, button, win, lose);
SDL_Quit();

return EXIT_SUCCESS;
}

