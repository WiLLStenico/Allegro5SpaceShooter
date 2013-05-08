//============================================================================
// Name        : Allegro5SpaceShooter.cpp
// Author      : WiLLStenico
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <list>

//TESTE
#include "GameObject.h"
#include "SpaceShip.h"
#include "Background.h"
#include "Bullet.h"
#include "XY.h"
#include "BulletManager.h"

using namespace std;


//GLOBALS==============================

const int FPS = 60;

Direction KEYS;

/*All inits here*/
void inits(){

	if(!al_init()){
		//al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return;
	}

	//==============================================
	//ADDON INSTALL
	//==============================================

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_joystick();
	al_init_image_addon();


}

int main() {

	inits();

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_BITMAP *shipImage = NULL;

	ALLEGRO_BITMAP *background1 = NULL;
	ALLEGRO_BITMAP *background2 = NULL;
	ALLEGRO_BITMAP *background3 = NULL;


	//TODO: SONGS
	ALLEGRO_SAMPLE_INSTANCE *songInstance;
	ALLEGRO_SAMPLE *song = NULL;

	song = al_load_sample("Resources//songs//shot2.wav");
	ALLEGRO_SAMPLE *dangerSong = al_load_sample("Resources//songs//danger.wav");

	al_reserve_samples(2);
	songInstance = al_create_sample_instance(song);
	ALLEGRO_SAMPLE_INSTANCE *songInstance2 = al_create_sample_instance(dangerSong);

	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(songInstance2, ALLEGRO_PLAYMODE_LOOP);



		al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());



	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	int WIDTH = disp_data.width/2;
	int HEIGHT = disp_data.height/2;
	display= al_create_display(WIDTH,HEIGHT);

	if(!display){
		//al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return -1;
	}

	//=============================== Fonts ==================================
	ALLEGRO_FONT *font18 = al_load_font("Resources//fonts//arial.ttf", 18, 0);

	//========================= Inputs ======================================

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();//swap buffers to prevent flicker

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool keys[4] = {false, false, false, false};

	bool done = false;
	bool draw = true;

	ALLEGRO_COLOR color = al_map_rgb(255,0,255);

	int count = 0;

	shipImage = al_load_bitmap("Resources//images//spaceship_by_arboris.png");

	background1 = al_load_bitmap("Resources//images//starBG.png");
	background2 = al_load_bitmap("Resources//images//starMG.png");
	background3 = al_load_bitmap("Resources//images//starFG.png");



	//al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));

	al_convert_mask_to_alpha(background1, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(background2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(background3, al_map_rgb(255, 255, 255));


	//TODO: Background receive backgroung array
	Background *go_Background = new Background(background1,{al_get_bitmap_width(background1),al_get_bitmap_height(background1)},{0,0}, {3,0}, true, {WIDTH, HEIGHT});
	Background *go_Background2 = new Background(background2,{al_get_bitmap_width(background2),al_get_bitmap_height(background2)},{0,0}, {2,0}, true, {WIDTH, HEIGHT});
	Background *go_Background3 = new Background(background3,{al_get_bitmap_width(background3),al_get_bitmap_height(background3)},{0,0}, {1,0}, true, {WIDTH, HEIGHT});

	BulletManager *bulletManager = new BulletManager({WIDTH,HEIGHT});


	//Initialized the Player
	SpaceShip *player1_Ship = new SpaceShip(shipImage,{46,41}, {20,HEIGHT/2}, {10,5});
	SpaceShip *player2_Ship = new SpaceShip(shipImage,{46,41}, {WIDTH - 60,HEIGHT/2}, {0,0});

	//TODO: REMOVE AND INITIALIZE
	//Bullet *bullet = NULL;
	player1_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_RED);
	player2_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_BLUE);



	//==================== Events Register ================
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//Pega os eventos do display, por exemplo o click do botao X do display
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_joystick_event_source());


	//================ Timer ================
	al_register_event_source(event_queue, al_get_mouse_event_source());
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	al_hide_mouse_cursor(display);
	//al_show_mouse_cursor(display);

	ALLEGRO_JOYSTICK *joy =NULL;
	if(al_get_num_joysticks()> 0){
		joy = al_get_joystick(0);
	}
	ALLEGRO_JOYSTICK_STATE joyState;

	//=============== Principal Game Loop ==================================


	int vel = 10;
	bool shotKeyPressed = false;
	while(!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(joy != NULL){
			al_get_joystick_state(joy, &joyState);
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				vel+=2;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				vel-=2;
				break;
			case ALLEGRO_KEY_1:
				//*bullet = bulletManager->GetBullet(bulletManager->NORMAL_RED);
					player1_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_BLUE);
				break;
			case ALLEGRO_KEY_2:
				//*bullet = bulletManager->GetBullet(bulletManager->NORMAL_BLUE);
					player1_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_RED);
				break;
			case ALLEGRO_KEY_SPACE:
				shotKeyPressed = true;//go_Ship->Shoot();

				break;
			}

		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case  ALLEGRO_KEY_ENTER:
				break;
			case ALLEGRO_KEY_SPACE:
				shotKeyPressed = false;//go_Ship->Shoot();
				break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1) //Botão esquerdo
				draw = !draw;
			else if (ev.mouse.button & 2) //Botão direito
				done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			player1_Ship->setPosition({ev.mouse.x, ev.mouse.y});
		}
		else  if (ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
		{
			if (ev.joystick.axis == 0) //x
			{
				//pos_x += ev.joystick.pos* 10;
				keys[LEFT] = ev.joystick.pos < 0;
				keys[RIGHT] = ev.joystick.pos > 0;

			}
			else if (ev.joystick.axis == 1)//y
			{
				keys[UP] = ev.joystick.pos < 0;
				keys[DOWN] = ev.joystick.pos > 0;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
		{
			switch (ev.joystick.button)
			{
			case 1:
				player1_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_RED);

				break;
			case 2:
				player1_Ship->bullet = bulletManager->GetBullet(bulletManager->NORMAL_BLUE);
				break;
			case 3:
				shotKeyPressed = true;

				break;
			case 0:

				break;
			default:

				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
		{
			switch (ev.joystick.button)
			{
			case 3:
				shotKeyPressed = false;
				//color = al_map_rgb(255, 0, 0);
				break;
			default:
					break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{

			player1_Ship->setVelocity({vel*(-keys[LEFT]+keys[RIGHT]) ,vel*(-keys[UP]+keys[DOWN])});

			player2_Ship->setVelocity({-vel*(-keys[LEFT]+keys[RIGHT]) ,vel*(-keys[UP]+keys[DOWN])});

			go_Background->setVelocity({vel*0.1 ,0});
			go_Background2->setVelocity({vel*0.2,0});
			go_Background3->setVelocity({vel*0.35,0});

			draw = true;

		}

		if(shotKeyPressed /*&& count % 20 == 0*/){
			player1_Ship->Shoot();
			al_play_sample(song, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}

		if(draw && al_is_event_queue_empty(event_queue)) {
			draw = false;

			go_Background->Render();
			go_Background2->Render();
			go_Background3->Render();


			player1_Ship->Render();
			player2_Ship->Render();

			player2_Ship->CheckColision(player1_Ship->getBullets());

			//al_draw_bitmap_region(go_Ship->Image, go_Ship->CurrentFrame.X * go_Ship->ObjectDimention.Width, go_Ship->CurrentFrame.Y * go_Ship->ObjectDimention.Height, go_Ship->ObjectDimention.Width, go_Ship->ObjectDimention.Height, go_Ship->Position.X, go_Ship->Position.Y, 0);



			if(!player2_Ship->isAlive()){
				player1_Ship->setScore(player1_Ship->getScore()+1);
				player2_Ship->setAlive(true);
				al_play_sample(dangerSong, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			}

			/*al_draw_filled_rectangle(player2_Ship->getPosition().X,player2_Ship->getPosition().Y,
					player2_Ship->getObjectDimention().Width,player2_Ship->getObjectDimention().Height,
					al_map_rgb(255,255,255));*/

			al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT - font18->height, ALLEGRO_ALIGN_CENTRE,
								"P1: %i    P2: %i", player1_Ship->getScore(), player2_Ship->getScore());

			al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, 2, ALLEGRO_ALIGN_CENTRE,
					"Frames: %i", count);



			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));

		}
		count++;

	}



	//========================= Destroys ====================================
	player1_Ship->~SpaceShip();

	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_bitmap(background1);
	al_destroy_bitmap(background2);
	al_destroy_bitmap(background3);


	return 0;
}
