//============================================================================
// Name        : Allegro5SpaceShooter.cpp
// Author      : WiLLStenico
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>
using namespace std;


//GLOBALS==============================

const int FPS = 60;

enum KEYS{ UP, DOWN, LEFT, RIGHT};

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
	ALLEGRO_BITMAP *image = NULL;

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	int WIDTH = 800;//disp_data.width;
	int HEIGHT = 800;//disp_data.height;
	display= al_create_display(WIDTH,HEIGHT);

	if(!display){
		//al_show_native_message_box(NULL,NULL,NULL,"Failed to init Allegro",NULL,NULL);
		return -1;
	}

	//=============================== Fonts ==================================
	ALLEGRO_FONT *font18 = al_load_font("Resources//fonts//arial.ttf", 18, 0);

	al_draw_text(font18, al_map_rgb(15, 240, 18), 620, 350, ALLEGRO_ALIGN_RIGHT, "This is right aligned and 18 point");

	al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, 400, ALLEGRO_ALIGN_CENTRE,
			"TEXT with variable output (textf): Screen width and height = %i / %i" , WIDTH, HEIGHT);

	//========================= Inputs ======================================
	//al_reserve_samples(15);

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();//swap buffers to prevent flicker

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool keys[4] = {false, false, false, false};

	bool done = false;
	bool draw = true;
	//bool redraw = true;

	ALLEGRO_COLOR color = al_map_rgb(255,0,255);

	int pos_x = WIDTH / 2;
	int pos_y = HEIGHT / 2;

	int count = 0;

	int curColFrame = 0;
	int curRowFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;
	int frameWidth = 46;
	int frameHeight = 41;

	image = al_load_bitmap("Resources//images//spaceship_by_arboris.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));

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
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
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
			pos_y -= keys[UP] * 10;
			pos_y += keys[DOWN] * 10;
			pos_x -= keys[LEFT] * 10;
			pos_x += keys[RIGHT] * 10;
			curColFrame = abs(2* keys[LEFT] -  keys[RIGHT]);
			curRowFrame = 1  + keys[DOWN] - keys[UP];

			//redraw = true;
		}

		/*if(draw)
			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
		 */
		//al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, color);


		al_draw_bitmap_region(image, curColFrame * frameWidth, curRowFrame * frameHeight, frameWidth, frameHeight, pos_x, pos_y, 0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));

		count++;

		al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT/ 2, ALLEGRO_ALIGN_CENTRE,
				"Frames: %i", count);

	}



	//========================= Destroys ====================================
	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}
