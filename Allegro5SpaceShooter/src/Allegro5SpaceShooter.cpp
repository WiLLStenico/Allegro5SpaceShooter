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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>


#include "GameObject.h"
#include "SpaceShip.h"
#include "Background.h"
#include "XY.h"

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


	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(background1, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(background2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(background3, al_map_rgb(255, 255, 255));


	Background *go_Background = new Background(background1,{al_get_bitmap_width(background1),al_get_bitmap_height(background1)},{0,0}, {3,0}, true, {WIDTH, HEIGHT});
	Background *go_Background2 = new Background(background2,{al_get_bitmap_width(background2),al_get_bitmap_height(background2)},{0,0}, {2,0}, true, {WIDTH, HEIGHT});
	Background *go_Background3 = new Background(background3,{al_get_bitmap_width(background3),al_get_bitmap_height(background3)},{0,0}, {1,0}, true, {WIDTH, HEIGHT});


	//Initialized the Player
	SpaceShip *go_Ship = new SpaceShip(shipImage,{46,41}, {20,HEIGHT/2}, {10,5});
	SpaceShip *player2_Ship = new SpaceShip(shipImage,{46,41}, {WIDTH - 60,HEIGHT/2}, {0,0});



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
			go_Ship->setPosition(ev.mouse.x, ev.mouse.y);
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
				color = al_map_rgb(255, 0, 0);
				break;
			case 2:
				color = al_map_rgb(0, 0, 255);
				break;
			case 3:
				color = al_map_rgb(0, 255, 0);
				break;
			case 0:
				color = al_map_rgb(255, 0, 255);
				break;
			default:
				color = al_map_rgb(255, 255, 255);
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{

			go_Ship->setVelocity(vel*(-keys[LEFT]+keys[RIGHT]) ,vel*(-keys[UP]+keys[DOWN]));

			go_Background->setVelocity(vel*0.1 ,0);
			go_Background2->setVelocity(vel*0.2,0);
			go_Background3->setVelocity(vel*0.35,0);

			/*go_Ship->Position.Y -= keys[UP] * go_Ship->Velocity.Y;
			go_Ship->Position.Y += keys[DOWN] * go_Ship->Velocity.Y;
			go_Ship->Position.X -= keys[LEFT] * go_Ship->Velocity.X;
			go_Ship->Position.X += keys[RIGHT] * go_Ship->Velocity.X;

			XY position;

			position.X = go_Ship->getPosition().X

			go_Ship->setPosition()


			go_Ship->CurrentFrame.X = abs(2* keys[LEFT] -  keys[RIGHT]);
			go_Ship->CurrentFrame.Y = 1  + keys[DOWN] - keys[UP];*/

			draw = true;

		}


		if(draw && al_is_event_queue_empty(event_queue)) {
			draw = false;



			//TODO: Criar rotina para loop de background e avaliar melhor...(TESTE)
			//TODO: ARRUMAR Tirar isso URGENTE daqui...

			//al_draw_scaled_bitmap(background1,0,0,al_get_bitmap_width(background1),al_get_bitmap_height(background1),-count*0.1,0,WIDTH,HEIGHT,0);
			//al_draw_scaled_bitmap(background2,0,0,al_get_bitmap_width(background2),al_get_bitmap_height(background2),-count*0.2,100,al_get_bitmap_width(background2)*1.2,al_get_bitmap_height(background2)*1.2,0);
			//al_draw_scaled_bitmap(background3,0,0,al_get_bitmap_width(background3),al_get_bitmap_height(background3),-count*0.5,0,WIDTH,HEIGHT,0);

			//double velFactor1 = 2;//0.1;
			/*for (int i = 0; (i* (WIDTH-count*velFactor1)) < WIDTH; i+=al_get_bitmap_width(background1)) {
				cout << "DX: " <<-count*velFactor1 + WIDTH * i<< endl;
				cout << "WIDHT: " <<WIDTH <<"CONDIÇÃO:: "<< (i* (WIDTH-count*velFactor1))<< endl;

				al_draw_scaled_bitmap(background1,0,0,al_get_bitmap_width(background1),al_get_bitmap_height(background1),-count*velFactor1 + WIDTH * i,0,WIDTH,HEIGHT,0);

			}*/

			/*	double velFactor2 = velFactor1 * 2;
			for (int i = 0; (i* (WIDTH-count*velFactor2)) < WIDTH; ++i) {
				al_draw_scaled_bitmap(background2,0,0,al_get_bitmap_width(background2),al_get_bitmap_height(background2),-count*velFactor2 + WIDTH * i,100,al_get_bitmap_width(background2)*1.3,al_get_bitmap_height(background2)*1.3,0);
			}

			double velFactor3 = velFactor1 * 3;
			for (int i = 0; (i* (WIDTH-count*velFactor3)) < WIDTH; ++i) {
				al_draw_scaled_bitmap(background3,0,0,al_get_bitmap_width(background3),al_get_bitmap_height(background3),-count*velFactor3 + WIDTH * i,0,WIDTH,HEIGHT,0);
			}*/



			go_Background->Render();
			go_Background2->Render();
			go_Background3->Render();

			go_Ship->Render();
			player2_Ship->Render();
			//al_draw_bitmap_region(go_Ship->Image, go_Ship->CurrentFrame.X * go_Ship->ObjectDimention.Width, go_Ship->CurrentFrame.Y * go_Ship->ObjectDimention.Height, go_Ship->ObjectDimention.Width, go_Ship->ObjectDimention.Height, go_Ship->Position.X, go_Ship->Position.Y, 0);

			al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, 2, ALLEGRO_ALIGN_CENTRE,
					"Frames: %i", count);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));

		}
		count++;

	}



	//========================= Destroys ====================================
	go_Ship->~SpaceShip();

	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_bitmap(background1);
	al_destroy_bitmap(background2);
	al_destroy_bitmap(background3);


	return 0;
}
